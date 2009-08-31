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

//! [0]
DEFINES += QT_NO_CAST_FROM_ASCII \
           QT_NO_CAST_TO_ASCII
//! [0]


//! [1]
QString url = QLatin1String("http://www.unicode.org/");
//! [1]


//! [2]
double d = 12.34;
QString str = QString("delta: %1").arg(d, 0, 'E', 3);
// str == "delta: 1.234E+01"
//! [2]


//! [3]
if (str == "auto" || str == "extern"
        || str == "static" || str == "register") {
    ...
}
//! [3]


//! [4]
if (str == QString("auto") || str == QString("extern")
        || str == QString("static") || str == QString("register")) {
    ...
}
//! [4]


//! [5]
if (str == QLatin1String("auto")
        || str == QLatin1String("extern")
        || str == QLatin1String("static")
        || str == QLatin1String("register") {
    ...
}
//! [5]


//! [6]
QLabel *label = new QLabel(QLatin1String("MOD"), this);
//! [6]
