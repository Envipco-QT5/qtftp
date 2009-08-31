/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Assistant of the Qt Toolkit.
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

#ifndef QASSISTANTCLIENT_H
#define QASSISTANTCLIENT_H

#include <QtCore/QObject>
#include <QtCore/QStringList>
#include <QtCore/QProcess>
#include <QtCore/qglobal.h>
#include <QtAssistant/qassistantclient_global.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

class QTcpSocket;

class QT_ASSISTANT_CLIENT_EXPORT QAssistantClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY( bool open READ isOpen )

public:
    QAssistantClient( const QString &path, QObject *parent = 0);
    ~QAssistantClient();

    bool isOpen() const;

    void setArguments( const QStringList &args );

public Q_SLOTS:
    virtual void openAssistant();
    virtual void closeAssistant();
    virtual void showPage( const QString &page );

Q_SIGNALS:
    void assistantOpened();
    void assistantClosed();
    void error( const QString &msg );

private Q_SLOTS:
    void socketConnected();
    void socketConnectionClosed();
    void readPort();
    void procError(QProcess::ProcessError err);
    void socketError();
    void readStdError();

private:
    QTcpSocket *socket;
    QProcess *proc;
    quint16 port;
    QString host, assistantCommand, pageBuffer;
    bool opened;
};

QT_END_NAMESPACE

QT_END_HEADER

#endif
