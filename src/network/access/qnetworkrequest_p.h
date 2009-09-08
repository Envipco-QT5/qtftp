/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtNetwork module of the Qt Toolkit.
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
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
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

#ifndef QNETWORKREQUEST_P_H
#define QNETWORKREQUEST_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of the Network Access API.  This header file may change from
// version to version without notice, or even be removed.
//
// We mean it.
//

#include "qnetworkrequest.h"
#include "QtCore/qbytearray.h"
#include "QtCore/qlist.h"
#include "QtCore/qhash.h"
#include "QtCore/qshareddata.h"

QT_BEGIN_NAMESPACE

// this is the common part between QNetworkRequestPrivate and QNetworkReplyPrivate
class QNetworkHeadersPrivate
{
public:
    typedef QPair<QByteArray, QByteArray> RawHeaderPair;
    typedef QList<RawHeaderPair> RawHeadersList;
    typedef QHash<QNetworkRequest::KnownHeaders, QVariant> CookedHeadersMap;
    typedef QHash<QNetworkRequest::Attribute, QVariant> AttributesMap;

    RawHeadersList rawHeaders;
    CookedHeadersMap cookedHeaders;
    AttributesMap attributes;

    RawHeadersList::ConstIterator findRawHeader(const QByteArray &key) const;
    QList<QByteArray> rawHeadersKeys() const;
    void setRawHeader(const QByteArray &key, const QByteArray &value);
    void setAllRawHeaders(const RawHeadersList &list);
    void setCookedHeader(QNetworkRequest::KnownHeaders header, const QVariant &value);

    static QDateTime fromHttpDate(const QByteArray &value);
    static QByteArray toHttpDate(const QDateTime &dt);

private:
    void setRawHeaderInternal(const QByteArray &key, const QByteArray &value);
    void parseAndSetHeader(const QByteArray &key, const QByteArray &value);
};

Q_DECLARE_TYPEINFO(QNetworkHeadersPrivate::RawHeaderPair, Q_MOVABLE_TYPE);

QT_END_NAMESPACE


#endif
