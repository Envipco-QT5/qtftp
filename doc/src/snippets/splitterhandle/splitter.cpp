/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the documentation of the Qt Toolkit.
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

#include <QtGui>

#include "splitter.h"

SplitterHandle::SplitterHandle(Qt::Orientation orientation, QSplitter *parent)
    : QSplitterHandle(orientation, parent)
{
    gradient.setColorAt(0.0, Qt::darkGreen);
    gradient.setColorAt(0.25, Qt::white);
    gradient.setColorAt(1.0, Qt::darkGreen);
}

//! [0]
void SplitterHandle::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if (orientation() == Qt::Horizontal) {
        gradient.setStart(rect().left(), rect().height()/2);
        gradient.setFinalStop(rect().right(), rect().height()/2);
    } else {
        gradient.setStart(rect().width()/2, rect().top());
        gradient.setFinalStop(rect().width()/2, rect().bottom());
    }
    painter.fillRect(event->rect(), QBrush(gradient));
}
//! [0]

Splitter::Splitter(Qt::Orientation orientation, QWidget *parent)
    : QSplitter(orientation, parent)
{
}

//! [1]
QSplitterHandle *Splitter::createHandle()
{
    return new SplitterHandle(orientation(), this);
}
//! [1]
