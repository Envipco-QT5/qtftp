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

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef Patternist_NumericType_H
#define Patternist_NumericType_H

#include "qatomictype_p.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace QPatternist
{
    /**
     * @short Represents the internal and abstract type @c fs:numeric.
     *
     * @see <a href="http://www.w3.org/TR/xquery-semantics/#dt-fs_numeric">XQuery 1.0
     * and XPath 2.0 Formal Semantics, Definition: fs:numeric</a>
     * @ingroup Patternist_types
     * @author Frans Englich <frans.englich@nokia.com>
     */
    class NumericType : public AtomicType
    {
    public:
        virtual ~NumericType();

        virtual bool itemMatches(const Item &item) const;
        virtual bool xdtTypeMatches(const ItemType::Ptr &other) const;

        /**
         * @returns always "numeric". That is, no namespace prefix
         */
        virtual QString displayName(const NamePool::Ptr &np) const;

        /**
         * @returns always @c true
         */
        virtual bool isAbstract() const;

        /**
         * @returns always @c false
         */
        virtual bool isNodeType() const;

        /**
         * @returns always @c true
         */
        virtual bool isAtomicType() const;

        /**
         * @returns always xs:anyAtomicType
         */
        virtual SchemaType::Ptr wxsSuperType() const;

        /**
         * @returns always xs:anyAtomicType
         */
        virtual ItemType::Ptr xdtSuperType() const;

        /**
         * @returns @c null. It makes no sense to atomize the abstract type @c fs:numeric.
         */
        virtual ItemType::Ptr atomizedType() const;

        /**
         * NumericType cannot be visited. This function is only implemented
         * to satisfy the abstract super class's interface.
         *
         * @returns always a @c null pointer
         */
        virtual AtomicTypeVisitorResult::Ptr accept(const AtomicTypeVisitor::Ptr &visitor,
                                                    const SourceLocationReflection *const) const;

        /**
         * NumericType cannot be visited. This function is only implemented
         * to satisfy the abstract super class's interface.
         *
         * @returns always a @c null pointer
         */
        virtual AtomicTypeVisitorResult::Ptr accept(const ParameterizedAtomicTypeVisitor::Ptr &visitor,
                                                    const qint16 op,
                                                    const SourceLocationReflection *const) const;

        /**
         * The type @c fs:numeric is an abstract type which therefore
         * cannot be involved in comparisons. Hence, this function returns
         * @c null. This function is only implemented to satisfy the abstract
         * super class's interface.
         *
         * @returns always a @c null pointer
         */
        virtual AtomicComparatorLocator::Ptr comparatorLocator() const;

        /**
         * The type @c fs:numeric is an abstract type which therefore
         * cannot be involved in arithmetics. Hence, this function returns
         * @c null. This function is only implemented to satisfy the abstract
         * super class's interface.
         *
         * @returns always a @c null pointer
         */
        virtual AtomicMathematicianLocator::Ptr mathematicianLocator() const;


        /**
         * The type @c fs:numeric is an abstract type which therefore
         * cannot be involved in casting. Hence, this function returns
         * @c null. This function is only implemented to satisfy the abstract
         * super class's interface.
         *
         * @returns always a @c null pointer
         */
        virtual AtomicCasterLocator::Ptr casterLocator() const;

    protected:
        friend class BuiltinTypes;
        NumericType();
    };
}

QT_END_NAMESPACE

QT_END_HEADER

#endif
