/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtXmlPatterns module of the Qt Toolkit.
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

#include "qbuiltintypes_p.h"
#include "qitem_p.h"

#include "qanynodetype_p.h"

QT_BEGIN_NAMESPACE

using namespace QPatternist;

bool AnyNodeType::xdtTypeMatches(const ItemType::Ptr &other) const
{
    return other->isNodeType();
}

bool AnyNodeType::itemMatches(const Item &item) const
{
    return item.isNode();
}

ItemType::Ptr AnyNodeType::atomizedType() const
{
    return BuiltinTypes::xsAnyAtomicType;
}

QString AnyNodeType::displayName(const NamePool::Ptr &) const
{
    return QLatin1String("node()");
}

ItemType::Ptr AnyNodeType::xdtSuperType() const
{
    return BuiltinTypes::item;
}

bool AnyNodeType::isNodeType() const
{
    return true;
}

bool AnyNodeType::isAtomicType() const
{
    return false;
}

QXmlNodeModelIndex::NodeKind AnyNodeType::nodeKind() const
{
    /* node() is an abstract type, so we don't have a value for it in
     * QXmlNodeModelIndex::NodeKind. */
    return QXmlNodeModelIndex::NodeKind(0);
}

PatternPriority AnyNodeType::patternPriority() const
{
    return -0.5;
}

QT_END_NAMESPACE
