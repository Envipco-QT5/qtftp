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

#ifndef TRACKBALL_H
#define TRACKBALL_H

#include <QtGui>

#include "vector.h"

class TrackBall
{
public:
    enum TrackMode
    {
        Plane,
        Sphere,
    };
    TrackBall(TrackMode mode = Sphere);
    TrackBall(float angularVelocity, const gfx::Vector3f& axis, TrackMode mode = Sphere);
    // coordinates in [-1,1]x[-1,1]
    void push(const QPointF& p, const gfx::Quaternionf &transformation);
    void move(const QPointF& p, const gfx::Quaternionf &transformation);
    void release(const QPointF& p, const gfx::Quaternionf &transformation);
    void start(); // starts clock
    void stop(); // stops clock
    gfx::Quaternionf rotation() const;
private:
    gfx::Quaternionf m_rotation;
    gfx::Vector3f m_axis;
    float m_angularVelocity;

    QPointF m_lastPos;
    QTime m_lastTime;
    bool m_paused;
    bool m_pressed;
    TrackMode m_mode;
};

#endif
