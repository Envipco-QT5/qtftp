/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtGui module of the Qt Toolkit.
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

#ifndef QGRAPHICSPROXYWIDGET_P_H
#define QGRAPHICSPROXYWIDGET_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of qapplication_*.cpp, qwidget*.cpp and qfiledialog.cpp.  This header
// file may change from version to version without notice, or even be removed.
//
// We mean it.
//

#include "qgraphicsproxywidget.h"
#include "private/qgraphicswidget_p.h"

#if !defined(QT_NO_GRAPHICSVIEW) || (QT_EDITION & QT_MODULE_GRAPHICSVIEW) != QT_MODULE_GRAPHICSVIEW

QT_BEGIN_NAMESPACE

class QGraphicsProxyWidgetPrivate : public QGraphicsWidgetPrivate
{
    Q_DECLARE_PUBLIC(QGraphicsProxyWidget)
public:
    QGraphicsProxyWidgetPrivate()
        : dragDropWidget(0),
          posChangeMode(NoMode),
          sizeChangeMode(NoMode),
          visibleChangeMode(NoMode),
          enabledChangeMode(NoMode),
          styleChangeMode(NoMode),
          paletteChangeMode(NoMode),
          focusFromWidgetToProxy(0)
    { }
    void init();
    void sendWidgetMouseEvent(QGraphicsSceneMouseEvent *event);
    void sendWidgetMouseEvent(QGraphicsSceneHoverEvent *event);
    void sendWidgetKeyEvent(QKeyEvent *event);
    void setWidget_helper(QWidget *widget, bool autoShow);

    QWidget *findFocusChild(QWidget *child, bool next) const;
    void removeSubFocusHelper(QWidget *widget, Qt::FocusReason reason);

    // ### Qt 5: Remove. Workaround for reimplementation added after Qt 4.4.
    QVariant inputMethodQueryHelper(Qt::InputMethodQuery query) const;

    void _q_removeWidgetSlot();

    void embedSubWindow(QWidget *);
    void unembedSubWindow(QWidget *);

    bool isProxyWidget() const;

    QPointer<QWidget> widget;
    QPointer<QWidget> lastWidgetUnderMouse;
    QPointer<QWidget> embeddedMouseGrabber;
    QWidget *dragDropWidget;
    Qt::DropAction lastDropAction;

    void updateWidgetGeometryFromProxy();
    void updateProxyGeometryFromWidget();

    QPointF mapToReceiver(const QPointF &pos, const QWidget *receiver) const;

    enum ChangeMode {
        NoMode,
        ProxyToWidgetMode,
        WidgetToProxyMode
    };
    quint32 posChangeMode : 2;
    quint32 sizeChangeMode : 2;
    quint32 visibleChangeMode : 2;
    quint32 enabledChangeMode : 2;
    quint32 styleChangeMode : 2;
    quint32 paletteChangeMode : 2;
    quint32 focusFromWidgetToProxy : 1;
};

QT_END_NAMESPACE

#endif

#endif
