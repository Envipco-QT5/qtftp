/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
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
** contact the sales department at http://qt.nokia.com/contact.
** $QT_END_LICENSE$
**
**
** This file was generated by dbusxml2cpp version 0.6
** Command line was: dbusxml2cpp -p chat_interface.h: com.trolltech.chat.xml
**
** dbusxml2cpp is Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
**
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
**
****************************************************************************/

#ifndef CHAT_INTERFACE_H_143021156243606
#define CHAT_INTERFACE_H_143021156243606

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface com.trolltech.chat
 */
class ComTrolltechChatInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "com.trolltech.chat"; }

public:
    ComTrolltechChatInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~ComTrolltechChatInterface();

public Q_SLOTS: // METHODS
Q_SIGNALS: // SIGNALS
    void action(const QString &nickname, const QString &text);
    void message(const QString &nickname, const QString &text);
};

namespace com {
  namespace trolltech {
    typedef ::ComTrolltechChatInterface chat;
  }
}
#endif
