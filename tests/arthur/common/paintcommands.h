/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the test suite of the Qt Toolkit.
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
** contact the sales department at http://qt.nokia.com/contact.
** $QT_END_LICENSE$
**
****************************************************************************/
#ifndef PAINTCOMMANDS_H
#define PAINTCOMMANDS_H

#include <qcolor.h>
#include <qmap.h>
#include <qpainterpath.h>
#include <qregion.h>
#include <qstringlist.h>
#include <qpixmap.h>
#include <qbrush.h>

QT_FORWARD_DECLARE_CLASS(QPainter)
QT_FORWARD_DECLARE_CLASS(QRegExp)
#ifndef QT_NO_OPENGL
QT_FORWARD_DECLARE_CLASS(QGLPixelBuffer)
#endif

enum DeviceType {
        WidgetType,
        BitmapType,
        PixmapType,
        ImageType,
        ImageMonoType,
        OpenGLType,
        OpenGLPBufferType,
        PictureType,
        PrinterType,
        PdfType,
        PsType,
        GrabType,
        CustomDeviceType,
        CustomWidgetType,
        ImageWidgetType
};

/************************************************************************/
class PaintCommands
{
public:
    // construction / initialization
    PaintCommands(const QStringList &cmds, int w, int h)
        : m_painter(0)
        , m_surface_painter(0)
        , m_commands(cmds)
        , m_gradientSpread(QGradient::PadSpread)
        , m_gradientCoordinate(QGradient::LogicalMode)
        , m_width(w)
        , m_height(h)
        , m_verboseMode(false)
        , m_type(WidgetType)
        , m_checkers_background(true)
    { staticInit(); }

public:
    void setCheckersBackground(bool b) { staticInit(); m_checkers_background = b; }
    void setContents(const QStringList &cmds) {
        staticInit();
        m_blockMap.clear();
        m_pathMap.clear();
        m_pixmapMap.clear();
        m_imageMap.clear();
        m_regionMap.clear();
        m_gradientStops.clear();
        m_controlPoints.clear();
        m_gradientSpread = QGradient::PadSpread;
        m_gradientCoordinate = QGradient::LogicalMode;
        m_commands = cmds;


    }
    void setPainter(QPainter *pt) { staticInit(); m_painter = pt; }
    void setType(DeviceType t) { staticInit(); m_type = t; }
    void setFilePath(const QString &path) { staticInit(); m_filepath = path; }
    void setControlPoints(const QVector<QPointF> &points) { staticInit(); m_controlPoints = points; }
    void setVerboseMode(bool v) { staticInit(); m_verboseMode = v; }
    void insertAt(int commandIndex, const QStringList &newCommands);

    // run
    void runCommands();

private:
    // run
    void runCommand(const QString &scriptLine);

    // conversion methods
    int convertToInt(const QString &str);
    double convertToDouble(const QString &str);
    float convertToFloat(const QString &str);
    QColor convertToColor(const QString &str);

    // commands: comments
    void command_comment(QRegExp re);

    // commands: importer
    void command_import(QRegExp re);

    // commands: blocks
    void command_begin_block(QRegExp re);
    void command_end_block(QRegExp re);
    void command_repeat_block(QRegExp re);

    // commands: misc
    void command_textlayout_draw(QRegExp re);
    void command_abort(QRegExp re);

    // commands: noops
    void command_noop(QRegExp re);

    // commands: setters
    void command_setBgMode(QRegExp re);
    void command_setBackground(QRegExp re);
    void command_setOpacity(QRegExp re);
    void command_path_setFillRule(QRegExp re);
    void command_setBrush(QRegExp re);
    void command_setBrushOrigin(QRegExp re);
    void command_brushTranslate(QRegExp re);
    void command_brushRotate(QRegExp re);
    void command_brushScale(QRegExp re);
    void command_brushShear(QRegExp re);
    void command_setClipPath(QRegExp re);
    void command_setClipRect(QRegExp re);
    void command_setClipRectangle(QRegExp re);
    void command_setClipRegion(QRegExp re);
    void command_setClipping(QRegExp re);
    void command_setCompositionMode(QRegExp re);
    void command_setFont(QRegExp re);
    void command_setPen(QRegExp re);
    void command_setPen2(QRegExp re);
    void command_pen_setDashOffset(QRegExp re);
    void command_pen_setDashPattern(QRegExp re);
    void command_pen_setCosmetic(QRegExp re);
    void command_setRenderHint(QRegExp re);
    void command_clearRenderHint(QRegExp re);
    void command_gradient_appendStop(QRegExp re);
    void command_gradient_clearStops(QRegExp re);
    void command_gradient_setConical(QRegExp re);
    void command_gradient_setLinear(QRegExp re);
    void command_gradient_setRadial(QRegExp re);
    void command_gradient_setLinearPen(QRegExp re);
    void command_gradient_setSpread(QRegExp re);
    void command_gradient_setCoordinateMode(QRegExp re);

    // commands: drawing ops
    void command_qt3_drawArc(QRegExp re);
    void command_qt3_drawChord(QRegExp re);
    void command_qt3_drawEllipse(QRegExp re);
    void command_qt3_drawPie(QRegExp re);
    void command_qt3_drawRect(QRegExp re);
    void command_qt3_drawRoundRect(QRegExp re);
    void command_drawArc(QRegExp re);
    void command_drawChord(QRegExp re);
    void command_drawConvexPolygon(QRegExp re);
    void command_drawEllipse(QRegExp re);
    void command_drawImage(QRegExp re);
    void command_drawLine(QRegExp re);
    void command_drawPath(QRegExp re);
    void command_drawPie(QRegExp re);
    void command_drawPixmap(QRegExp re);
    void command_drawPoint(QRegExp re);
    void command_drawPolygon(QRegExp re);
    void command_drawPolyline(QRegExp re);
    void command_drawRect(QRegExp re);
    void command_drawRoundedRect(QRegExp re);
    void command_drawRoundRect(QRegExp re);
    void command_drawText(QRegExp re);
    void command_drawTiledPixmap(QRegExp re);
    void command_path_addEllipse(QRegExp re);
    void command_path_addPolygon(QRegExp re);
    void command_path_addRect(QRegExp re);
    void command_path_addText(QRegExp re);
    void command_path_arcTo(QRegExp re);
    void command_path_closeSubpath(QRegExp re);
    void command_path_createOutline(QRegExp re);
    void command_path_cubicTo(QRegExp re);
    void command_path_debugPrint(QRegExp re);
    void command_path_lineTo(QRegExp re);
    void command_path_moveTo(QRegExp re);
    void command_region_addEllipse(QRegExp re);
    void command_region_addRect(QRegExp re);

    // getters
    void command_region_getClipRegion(QRegExp re);
    void command_path_getClipPath(QRegExp re);

    // commands: surface begin/end
    void command_surface_begin(QRegExp re);
    void command_surface_end(QRegExp re);

    // commands: save/restore painter state
    void command_restore(QRegExp re);
    void command_save(QRegExp re);

    // commands: pixmap/image
    void command_pixmap_load(QRegExp re);
    void command_pixmap_setMask(QRegExp re);
    void command_bitmap_load(QRegExp re);
    void command_image_convertToFormat(QRegExp re);
    void command_image_load(QRegExp re);
    void command_image_setColor(QRegExp re);
    void command_image_setNumColors(QRegExp re);

    // commands: transformation
    void command_resetMatrix(QRegExp re);
    void command_translate(QRegExp re);
    void command_rotate(QRegExp re);
    void command_rotate_x(QRegExp re);
    void command_rotate_y(QRegExp re);
    void command_scale(QRegExp re);
    void command_mapQuadToQuad(QRegExp re);
    void command_setMatrix(QRegExp re);

    // attributes
    QPainter *m_painter;
    QPainter *m_surface_painter;
    QImage m_surface_image;
    QPixmap m_surface_pixmap;
#ifndef QT_NO_OPENGL
    QGLPixelBuffer *m_surface_pbuffer;
#endif
    QRectF m_surface_rect;
    QStringList m_commands;
    QString m_currentCommand;
    int m_currentCommandIndex;
    QString m_filepath;
    QMap<QString, QStringList> m_blockMap;
    QMap<QString, QPainterPath> m_pathMap;
    QMap<QString, QPixmap> m_pixmapMap;
    QMap<QString, QImage> m_imageMap;
    QMap<QString, QRegion> m_regionMap;
    QGradientStops m_gradientStops;
    QGradient::Spread m_gradientSpread;
    QGradient::CoordinateMode m_gradientCoordinate;
    bool m_abort;
    int m_width;
    int m_height;

    bool m_verboseMode;
    DeviceType m_type;
    bool m_checkers_background;

    QVector<QPointF> m_controlPoints;

    // painter functionalities string tables
    static const char *brushStyleTable[];
    static const char *penStyleTable[];
    static const char *fontWeightTable[];
    static const char *clipOperationTable[];
    static const char *spreadMethodTable[];
    static const char *coordinateMethodTable[];
    static const char *compositionModeTable[];
    static const char *imageFormatTable[];
    static const char *sizeModeTable[];
    static int translateEnum(const char *table[], const QString &pattern, int limit);

    // utility
    template <typename T> T image_load(const QString &filepath);

    // commands dictionary management
    static void staticInit();

public:
    struct PaintCommandInfos
    {
        PaintCommandInfos(QString id, void (PaintCommands::*p)(QRegExp), QRegExp r, QString sy, QString sa)
            : identifier(id)
            , regExp(r)
            , syntax(sy)
            , sample(sa)
            , paintMethod(p)
            {}
        PaintCommandInfos(QString title)
            : identifier(title), paintMethod(0) {}
        bool isSectionHeader() const { return paintMethod == 0; }
        QString identifier;
        QRegExp regExp;
        QString syntax;
        QString sample;
        void (PaintCommands::*paintMethod)(QRegExp);
    };

    static PaintCommandInfos *findCommandById(const QString &identifier) {
        for (int i=0; i<s_commandInfoTable.size(); i++)
            if (s_commandInfoTable[i].identifier == identifier)
                return &s_commandInfoTable[i];
        return 0;
    }

    static QList<PaintCommandInfos> s_commandInfoTable;
    static QList<QPair<QString,QStringList> > s_enumsTable;
};

#endif // PAINTCOMMANDS_H
