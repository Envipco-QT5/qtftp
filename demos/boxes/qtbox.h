/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the either Technology Preview License Agreement or the
** Beta Release License Agreement.
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
** additional rights. These rights are described in the Nokia Qt LGPL
** Exception version 1.0, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QTBOX_H
#define QTBOX_H

#include <QtGui>

#include "vector.h"
#include "glbuffers.h"

class ItemBase : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    ItemBase(int size, int x, int y);
    virtual ~ItemBase();
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
protected:
    virtual ItemBase *createNew(int size, int x, int y) = 0;
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void wheelEvent(QGraphicsSceneWheelEvent *event);
    bool isInResizeArea(const QPointF &pos);

    static void duplicateSelectedItems(QGraphicsScene *scene);
    static void deleteSelectedItems(QGraphicsScene *scene);
    static void growSelectedItems(QGraphicsScene *scene);
    static void shrinkSelectedItems(QGraphicsScene *scene);

    int m_size;
    QTime m_startTime;
    bool m_isResizing;
};

class QtBox : public ItemBase
{
public:
    QtBox(int size, int x, int y);
    virtual ~QtBox();
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
protected:
    virtual ItemBase *createNew(int size, int x, int y);
private:
    gfx::Vector3f m_vertices[8];
    gfx::Vector2f m_texCoords[4];
    gfx::Vector3f m_normals[6];
    GLTexture *m_texture;
};

class CircleItem : public ItemBase
{
public:
    CircleItem(int size, int x, int y);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
protected:
    virtual ItemBase *createNew(int size, int x, int y);

    QColor m_color;
};

class SquareItem : public ItemBase
{
public:
    SquareItem(int size, int x, int y);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
protected:
    virtual ItemBase *createNew(int size, int x, int y);

    QPixmap m_image;
};

#endif
