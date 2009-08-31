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

#ifndef QWSEMBEDWIDGET_H
#define QWSEMBEDWIDGET_H

#include <QtGui/qwidget.h>

#ifndef QT_NO_QWSEMBEDWIDGET

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Gui)

class QWSEmbedWidgetPrivate;

class Q_GUI_EXPORT QWSEmbedWidget : public QWidget
{
    Q_OBJECT

public:
    QWSEmbedWidget(WId winId, QWidget *parent = 0);
    ~QWSEmbedWidget();

protected:
    bool eventFilter(QObject *object, QEvent *event);
    void changeEvent(QEvent *event);
    void resizeEvent(QResizeEvent *event);
    void moveEvent(QMoveEvent *event);
    void hideEvent(QHideEvent *event);
    void showEvent(QShowEvent *event);

private:
    Q_DECLARE_PRIVATE(QWSEmbedWidget)
};

QT_END_NAMESPACE

QT_END_HEADER

#endif // QT_NO_QWSEMBEDWIDGET
#endif // QWSEMBEDWIDGET_H
