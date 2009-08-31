/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the test suite of the Qt Toolkit.
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
** Command line was: dbusxml2cpp -a chat_adaptor.h: com.trolltech.chat.xml
**
** dbusxml2cpp is Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
**
** This is an auto-generated file.
** This file may have been hand-edited. Look for HAND-EDIT comments
** before re-generating it.
**
****************************************************************************/

#ifndef CHAT_ADAPTOR_H_142741156243605
#define CHAT_ADAPTOR_H_142741156243605

#include <QtCore/QObject>
#include <QtDBus/QtDBus>

QT_BEGIN_NAMESPACE
class QByteArray;
template<class T> class QList;
template<class Key, class Value> class QMap;
class QString;
class QStringList;
class QVariant;
QT_END_NAMESPACE

/*
 * Adaptor class for interface com.trolltech.chat
 */
class ChatAdaptor: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.trolltech.chat")
    Q_CLASSINFO("D-Bus Introspection", ""
"  <interface name=\"com.trolltech.chat\" >\n"
"    <signal name=\"message\" >\n"
"      <arg direction=\"out\" type=\"s\" name=\"nickname\" />\n"
"      <arg direction=\"out\" type=\"s\" name=\"text\" />\n"
"    </signal>\n"
"    <signal name=\"action\" >\n"
"      <arg direction=\"out\" type=\"s\" name=\"nickname\" />\n"
"      <arg direction=\"out\" type=\"s\" name=\"text\" />\n"
"    </signal>\n"
"  </interface>\n"
        "")
public:
    ChatAdaptor(QObject *parent);
    virtual ~ChatAdaptor();

public: // PROPERTIES
public Q_SLOTS: // METHODS
Q_SIGNALS: // SIGNALS
    void action(const QString &nickname, const QString &text);
    void message(const QString &nickname, const QString &text);
};

#endif
