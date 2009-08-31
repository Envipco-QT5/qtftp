/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain
** additional rights.  These rights are described in the Nokia Qt LGPL
** Exception version 1.1, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef GLBUFFERS_H
#define GLBUFFERS_H

//#include <GL/glew.h>
#include "glextensions.h"

#include <QtGui>
#include <QtOpenGL>

#include "vector.h"

#define BUFFER_OFFSET(i) ((char*)0 + (i))
#define SIZE_OF_MEMBER(cls, member) sizeof(static_cast<cls *>(0)->member)

#define GLBUFFERS_ASSERT_OPENGL(prefix, assertion, returnStatement)                         \
if (m_failed || !(assertion)) {                                                             \
    if (!m_failed) qCritical(prefix ": The necessary OpenGL functions are not available."); \
    m_failed = true;                                                                        \
    returnStatement;                                                                        \
}

class GLTexture
{
public:
    GLTexture();
    virtual ~GLTexture();
    virtual void bind() = 0;
    virtual void unbind() = 0;
    virtual bool failed() const {return m_failed;}
protected:
    GLuint m_texture;
    bool m_failed;
};

class GLFrameBufferObject
{
public:
    friend class GLRenderTargetCube;
    // friend class GLRenderTarget2D;

    GLFrameBufferObject(int width, int height);
    virtual ~GLFrameBufferObject();
    bool isComplete();
    virtual bool failed() const {return m_failed;}
protected:
    void setAsRenderTarget(bool state = true);
    GLuint m_fbo;
    GLuint m_depthBuffer;
    int m_width, m_height;
    bool m_failed;
};

class GLTexture2D : public GLTexture
{
public:
    GLTexture2D(int width, int height);
    GLTexture2D(const QString& fileName, int width = 0, int height = 0);
    void load(int width, int height, QRgb *data);
    virtual void bind();
    virtual void unbind();
};

class GLTexture3D : public GLTexture
{
public:
    GLTexture3D(int width, int height, int depth);
    // TODO: Implement function below
    //GLTexture3D(const QString& fileName, int width = 0, int height = 0);
    void load(int width, int height, int depth, QRgb *data);
    virtual void bind();
    virtual void unbind();
};

class GLTextureCube : public GLTexture
{
public:
    GLTextureCube(int size);
    GLTextureCube(const QStringList& fileNames, int size = 0);
    void load(int size, int face, QRgb *data);
    virtual void bind();
    virtual void unbind();
};

// TODO: Define and implement class below
//class GLRenderTarget2D : public GLTexture2D

class GLRenderTargetCube : public GLTextureCube
{
public:
    GLRenderTargetCube(int size);
    // begin rendering to one of the cube's faces. 0 <= face < 6
    void begin(int face);
    // end rendering
    void end();
    virtual bool failed() {return m_failed || m_fbo.failed();}

    static void getViewMatrix(gfx::Matrix4x4f& mat, int face);
    static void getProjectionMatrix(gfx::Matrix4x4f& mat, float nearZ, float farZ);
private:
    GLFrameBufferObject m_fbo;
};

struct VertexDescription
{
    enum
    {
        Null = 0, // Terminates a VertexDescription array
        Position,
        TexCoord,
        Normal,
        Color,
    };
    int field; // Position, TexCoord, Normal, Color
    int type; // GL_FLOAT, GL_UNSIGNED_BYTE
    int count; // number of elements
    int offset; // field's offset into vertex struct
    int index; // 0 (unused at the moment)
};

// Implementation of interleaved buffers.
// 'T' is a struct which must include a null-terminated static array
// 'VertexDescription* description'.
// Example:
/*
struct Vertex
{
    GLfloat position[3];
    GLfloat texCoord[2];
    GLfloat normal[3];
    GLbyte color[4];
    static VertexDescription description[];
};

VertexDescription Vertex::description[] = {
    {VertexDescription::Position, GL_FLOAT, SIZE_OF_MEMBER(Vertex, position) / sizeof(GLfloat), offsetof(Vertex, position), 0},
    {VertexDescription::TexCoord, GL_FLOAT, SIZE_OF_MEMBER(Vertex, texCoord) / sizeof(GLfloat), offsetof(Vertex, texCoord), 0},
    {VertexDescription::Normal, GL_FLOAT, SIZE_OF_MEMBER(Vertex, normal) / sizeof(GLfloat), offsetof(Vertex, normal), 0},
    {VertexDescription::Color, GL_BYTE, SIZE_OF_MEMBER(Vertex, color) / sizeof(GLbyte), offsetof(Vertex, color), 0},
    {VertexDescription::Null, 0, 0, 0, 0},
};
*/
template<class T>
class GLVertexBuffer
{
public:
    GLVertexBuffer(int length, const T *data = 0, int mode = GL_STATIC_DRAW)
        : m_length(0)
        , m_mode(mode)
        , m_buffer(0)
        , m_failed(false)
    {
        GLBUFFERS_ASSERT_OPENGL("GLVertexBuffer::GLVertexBuffer", glGenBuffers && glBindBuffer && glBufferData, return)

		glGenBuffers(1, &m_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
		glBufferData(GL_ARRAY_BUFFER, (m_length = length) * sizeof(T), data, mode);
    }

    ~GLVertexBuffer()
    {
        GLBUFFERS_ASSERT_OPENGL("GLVertexBuffer::~GLVertexBuffer", glDeleteBuffers, return)

        glDeleteBuffers(1, &m_buffer);
    }

    void bind()
    {
        GLBUFFERS_ASSERT_OPENGL("GLVertexBuffer::bind", glBindBuffer, return)

        glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
        for (VertexDescription *desc = T::description; desc->field != VertexDescription::Null; ++desc) {
            switch (desc->field) {
            case VertexDescription::Position:
                glVertexPointer(desc->count, desc->type, sizeof(T), BUFFER_OFFSET(desc->offset));
                glEnableClientState(GL_VERTEX_ARRAY);
                break;
            case VertexDescription::TexCoord:
                glTexCoordPointer(desc->count, desc->type, sizeof(T), BUFFER_OFFSET(desc->offset));
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                break;
            case VertexDescription::Normal:
                glNormalPointer(desc->type, sizeof(T), BUFFER_OFFSET(desc->offset));
                glEnableClientState(GL_NORMAL_ARRAY);
                break;
            case VertexDescription::Color:
                glColorPointer(desc->count, desc->type, sizeof(T), BUFFER_OFFSET(desc->offset));
                glEnableClientState(GL_COLOR_ARRAY);
                break;
            default:
                break;
            }
        }
    }

    void unbind()
    {
        GLBUFFERS_ASSERT_OPENGL("GLVertexBuffer::unbind", glBindBuffer, return)

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        for (VertexDescription *desc = T::description; desc->field != VertexDescription::Null; ++desc) {
            switch (desc->field) {
            case VertexDescription::Position:
                glDisableClientState(GL_VERTEX_ARRAY);
                break;
            case VertexDescription::TexCoord:
                glDisableClientState(GL_TEXTURE_COORD_ARRAY);
                break;
            case VertexDescription::Normal:
                glDisableClientState(GL_NORMAL_ARRAY);
                break;
            case VertexDescription::Color:
                glDisableClientState(GL_COLOR_ARRAY);
                break;
            default:
                break;
            }
        }
    }

    int length() const {return m_length;}

    T *lock()
    {
        GLBUFFERS_ASSERT_OPENGL("GLVertexBuffer::lock", glBindBuffer && glMapBuffer, return 0)

        glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
        //glBufferData(GL_ARRAY_BUFFER, m_length, NULL, m_mode);
        GLvoid* buffer = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
        m_failed = (buffer == 0);
        return reinterpret_cast<T *>(buffer);
    }

    void unlock()
    {
        GLBUFFERS_ASSERT_OPENGL("GLVertexBuffer::unlock", glBindBuffer && glUnmapBuffer, return)

        glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }

    bool failed()
    {
        return m_failed;
    }

private:
    int m_length, m_mode;
    GLuint m_buffer;
    bool m_failed;
};

template<class T>
class GLIndexBuffer
{
public:
    GLIndexBuffer(int length, const T *data = 0, int mode = GL_STATIC_DRAW)
        : m_length(0)
        , m_mode(mode)
        , m_buffer(0)
        , m_failed(false)
    {
        GLBUFFERS_ASSERT_OPENGL("GLIndexBuffer::GLIndexBuffer", glGenBuffers && glBindBuffer && glBufferData, return)

        glGenBuffers(1, &m_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (m_length = length) * sizeof(T), data, mode);
    }

    ~GLIndexBuffer()
    {
        GLBUFFERS_ASSERT_OPENGL("GLIndexBuffer::~GLIndexBuffer", glDeleteBuffers, return)

        glDeleteBuffers(1, &m_buffer);
    }

    void bind()
    {
        GLBUFFERS_ASSERT_OPENGL("GLIndexBuffer::bind", glBindBuffer, return)

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
    }

    void unbind()
    {
        GLBUFFERS_ASSERT_OPENGL("GLIndexBuffer::unbind", glBindBuffer, return)

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    int length() const {return m_length;}

    T *lock()
    {
        GLBUFFERS_ASSERT_OPENGL("GLIndexBuffer::lock", glBindBuffer && glMapBuffer, return 0)

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
        GLvoid* buffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_WRITE);
        m_failed = (buffer == 0);
        return reinterpret_cast<T *>(buffer);
    }

    void unlock()
    {
        GLBUFFERS_ASSERT_OPENGL("GLIndexBuffer::unlock", glBindBuffer && glUnmapBuffer, return)

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
        glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
    }

    bool failed()
    {
        return m_failed;
    }

private:
    int m_length, m_mode;
    GLuint m_buffer;
    bool m_failed;
};

#endif
