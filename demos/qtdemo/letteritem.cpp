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

#include <cmath>
#include "letteritem.h"
#include "colors.h"

LetterItem::LetterItem(char letter, QGraphicsScene *scene, QGraphicsItem *parent) : DemoItem(scene, parent), letter(letter)
{
    useSharedImage(QString(__FILE__) + letter);
}

LetterItem::~LetterItem()
{
}

QImage *LetterItem::createImage(const QMatrix &matrix) const
{
    QRect scaledRect = matrix.mapRect(QRect(0, 0, 25, 25));
    QImage *image = new QImage(scaledRect.width(), scaledRect.height(), QImage::Format_ARGB32_Premultiplied);
    image->fill(0);
    QPainter painter(image);
    painter.scale(matrix.m11(), matrix.m22());
    painter.setRenderHints(QPainter::TextAntialiasing | QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.setPen(Qt::NoPen);
    if (Colors::useEightBitPalette){
        painter.setBrush(QColor(102, 175, 54));
        painter.drawEllipse(0, 0, 25, 25);
        painter.setFont(Colors::tickerFont());
        painter.setPen(QColor(255, 255, 255));
        painter.drawText(10, 15, QString(this->letter));
    }
    else {
        QLinearGradient brush(0, 0, 0, 25);
        brush.setSpread(QLinearGradient::PadSpread);
        brush.setColorAt(0.0, QColor(102, 175, 54, 200));
        brush.setColorAt(1.0, QColor(102, 175, 54, 60));
        painter.setBrush(brush);
        painter.drawEllipse(0, 0, 25, 25);
        painter.setFont(Colors::tickerFont());
        painter.setPen(QColor(255, 255, 255, 255));
        painter.drawText(10, 15, QString(this->letter));
    }
    return image;
}


