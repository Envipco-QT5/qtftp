/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
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

#include "layoutitem.h"

//! [0]
LayoutItem::LayoutItem(QGraphicsItem *parent/* = 0*/)
    : QGraphicsWidget(parent)
{
    pix = new QPixmap(QLatin1String(":/images/block.png"));
    // Do not allow a size smaller than the pixmap with two frames around it.
    setMinimumSize(pix->size() + QSize(12, 12));
}
//! [0]

LayoutItem::~LayoutItem()
{
    delete pix;
}
 
//! [1]
void LayoutItem::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget /*= 0*/)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    QRectF frame(QPointF(0,0), geometry().size());
    qreal w = pix->width();
    qreal h = pix->height();
    QGradientStops stops;
//! [1]

//! [2]
    // paint a background rect (with gradient)
    QLinearGradient gradient(frame.topLeft(), frame.topLeft() + QPointF(200,200));
    stops << QGradientStop(0.0, QColor(60, 60,  60));
    stops << QGradientStop(frame.height()/2/frame.height(), QColor(102, 176, 54));

    //stops << QGradientStop(((frame.height() + h)/2 )/frame.height(), QColor(157, 195,  55));
    stops << QGradientStop(1.0, QColor(215, 215, 215));
    gradient.setStops(stops);
    painter->setBrush(QBrush(gradient));
    painter->drawRoundedRect(frame, 10.0, 10.0);

    // paint a rect around the pixmap (with gradient)
    QPointF pixpos = frame.center() - (QPointF(w, h)/2);
    QRectF innerFrame(pixpos, QSizeF(w, h));
    innerFrame.adjust(-4, -4, +4, +4);
    gradient.setStart(innerFrame.topLeft());
    gradient.setFinalStop(innerFrame.bottomRight());
    stops.clear();
    stops << QGradientStop(0.0, QColor(215, 255, 200));
    stops << QGradientStop(0.5, QColor(102, 176, 54));
    stops << QGradientStop(1.0, QColor(0, 0,  0));
    gradient.setStops(stops);
    painter->setBrush(QBrush(gradient));
    painter->drawRoundedRect(innerFrame, 10.0, 10.0);
    painter->drawPixmap(pixpos, *pix);
}
//! [2]
