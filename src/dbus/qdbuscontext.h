/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtDBus module of the Qt Toolkit.
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

#ifndef QDBUSCONTEXT_H
#define QDBUSCONTEXT_H

#include <QtCore/qstring.h>
#include <QtDBus/qdbuserror.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(DBus)

class QDBusConnection;
class QDBusMessage;

class QDBusContextPrivate;
class QDBUS_EXPORT QDBusContext
{
public:
    QDBusContext();
    ~QDBusContext();

    bool calledFromDBus() const;
    QDBusConnection connection() const;
    const QDBusMessage &message() const;

    // convenience methods
    bool isDelayedReply() const;
    // yes, they are const, so that you can use them even from const methods
    void setDelayedReply(bool enable) const;
    void sendErrorReply(const QString &name, const QString &msg = QString()) const;
    void sendErrorReply(QDBusError::ErrorType type, const QString &msg = QString()) const;

private:
    QDBusContextPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QDBusContext)
};

QT_END_NAMESPACE

QT_END_HEADER

#endif
