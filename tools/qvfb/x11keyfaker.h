/****************************************************************************
**
** Copyright (C) 1992-2006 TROLLTECH ASA. All rights reserved.
**
** This file is part of the Phone Edition of the Qt Toolkit.
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
** contact the sales department at http://www.qtsoftware.com/contact.
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef X11KEYFAKER_H
#define X11KEYFAKER_H

#include <QObject>
#include <QX11Info>
#include <qnamespace.h>

QT_BEGIN_NAMESPACE

class X11KeyFaker : public QObject
{
    Q_OBJECT
public:
    X11KeyFaker(const QString& displayName, QObject *parent = 0);
    ~X11KeyFaker();

    bool isConnected() const { return dpy != 0; }

    void sendKeyEvent(int qtCode, bool isPress);

private slots:
    void connect();
    void readyRead();

signals:
    void connected();
    void couldNotConnect();

private:
    QString displayName;
    Display *dpy;
    int retryCount;
    int shiftKeycode;
    int modeSwitchKeycode;
    int modifiers;
};

QT_END_NAMESPACE

#endif
