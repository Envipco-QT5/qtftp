/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the QtScript module of the Qt Toolkit.
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

#ifndef QSCRIPTVALUEITERATORIMPL_P_H
#define QSCRIPTVALUEITERATORIMPL_P_H

#include "qscriptvalueimplfwd_p.h"

#ifndef QT_NO_SCRIPT

#include "qscriptmemberfwd_p.h"

QT_BEGIN_NAMESPACE

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

class QScriptClassDataIterator;
class QScriptNameIdImpl;

class QScriptValueIteratorImpl
{
public:
    QScriptValueIteratorImpl(const QScriptValueImpl &obj);
    ~QScriptValueIteratorImpl();

    bool ignoresDontEnum() const;
    void setIgnoresDontEnum(bool ignore);

    bool enumeratePrototype() const;
    void setEnumeratePrototype(bool enable);

    bool hasNext();
    void next();

    bool hasPrevious();
    void previous();

    QScript::Member *member();

    QScriptNameIdImpl *nameId() const;
    QString name() const;

    QScriptValueImpl value() const;
    void setValue(const QScriptValueImpl &value);

    uint flags() const;

    void remove();

    void toFront();
    void toBack();

    QScriptValueImpl object() const;
    void setObject(const QScriptValueImpl &obj);

private:
    bool acceptsMember(const QScriptValueImpl &o, const QScript::Member &m) const;
    QScriptClassDataIterator *getClassDataIterator();

    QScriptValueImpl m_frontObject;

    bool m_ignoresDontEnum;
    bool m_enumerateProto;

    QScriptValueImpl m_object;
    QScript::Member m_member;

    int m_searchIndex;
    QScriptValueImpl m_foundObject;
    QScript::Member m_foundMember;
    bool m_foundForward;
    QScriptClassDataIterator *m_classDataIterator;
    bool m_searchClassDataIterator;
};

QT_END_NAMESPACE

#endif // QT_NO_SCRIPT

#endif
