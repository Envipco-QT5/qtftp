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
****************************************************************************/

#include "connectionmanager.h"
#include "peerwireclient.h"
#include "ratecontroller.h"
#include "torrentclient.h"
#include "torrentserver.h"

Q_GLOBAL_STATIC(TorrentServer, torrentServer)

TorrentServer *TorrentServer::instance()
{
    return torrentServer();
}

void TorrentServer::addClient(TorrentClient *client)
{
    clients << client;
}

void TorrentServer::removeClient(TorrentClient *client)
{
    clients.removeAll(client);
}

void TorrentServer::incomingConnection(int socketDescriptor)
{
    PeerWireClient *client =
  	new PeerWireClient(ConnectionManager::instance()->clientId(), this);

    if (client->setSocketDescriptor(socketDescriptor)) {
        if (ConnectionManager::instance()->canAddConnection() && !clients.isEmpty()) {
            connect(client, SIGNAL(infoHashReceived(const QByteArray &)),
                    this, SLOT(processInfoHash(const QByteArray &)));
            connect(client, SIGNAL(error(QAbstractSocket::SocketError)),
                    this, SLOT(removeClient()));
            RateController::instance()->addSocket(client);
            ConnectionManager::instance()->addConnection(client);
            return;
        }
    }
    client->abort();
    delete client;
}

void TorrentServer::removeClient()
{
    PeerWireClient *peer = qobject_cast<PeerWireClient *>(sender());
    RateController::instance()->removeSocket(peer);
    ConnectionManager::instance()->removeConnection(peer);
    peer->deleteLater();
}

void TorrentServer::processInfoHash(const QByteArray &infoHash)
{
    PeerWireClient *peer = qobject_cast<PeerWireClient *>(sender());
    foreach (TorrentClient *client, clients) {
        if (client->state() >= TorrentClient::Searching && client->infoHash() == infoHash) {
            peer->disconnect(peer, 0, this, 0);
            client->setupIncomingConnection(peer);
            return;
        }
    }
    removeClient();
}
