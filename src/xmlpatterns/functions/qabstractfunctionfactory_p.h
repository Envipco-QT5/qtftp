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

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef Patternist_AbstractFunctionFactory_H
#define Patternist_AbstractFunctionFactory_H

#include "qcommonnamespaces_p.h"
#include "qfunctionfactory_p.h"
#include "qfunctionsignature_p.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace QPatternist
{

    /**
     * @short Supplies convenience code for the function factories.
     *
     * @ingroup Patternist_functions
     * @see XPath10CoreFunctions
     * @see XPath20CoreFunctions
     * @see XSLT10CoreFunctions
     * @author Vincent Ricard <magic@magicninja.org>
     */
    class AbstractFunctionFactory : public FunctionFactory
    {
    public:
        virtual Expression::Ptr createFunctionCall(const QXmlName name,
                                                   const Expression::List &arguments,
                                                   const StaticContext::Ptr &context,
                                                   const SourceLocationReflection *const r);

        virtual FunctionSignature::Hash functionSignatures() const;

    protected:
        /**
         * This function is responsible for creating the actual Expression, corresponding
         * to @p localName and the function signature @p sign. It is called by
         * createFunctionCall(), once it have been determined the function actually
         * exists and have the correct arity.
         *
         * This function will only be called for names in the @c fn namespace.
         */
        virtual Expression::Ptr retrieveExpression(const QXmlName name,
                                                   const Expression::List &args,
                                                   const FunctionSignature::Ptr &sign) const = 0;

        inline
        FunctionSignature::Ptr addFunction(const QXmlName::LocalNameCode localName,
                                           const FunctionSignature::Arity minArgs,
                                           const FunctionSignature::Arity maxArgs,
                                           const SequenceType::Ptr &returnType,
                                           const Expression::Properties props)
        {
            return addFunction(localName,
                               minArgs,
                               maxArgs,
                               returnType,
                               Expression::IDIgnorableExpression,
                               props);
        }

        FunctionSignature::Ptr addFunction(const QXmlName::LocalNameCode &localName,
                                           const FunctionSignature::Arity minArgs,
                                           const FunctionSignature::Arity maxArgs,
                                           const SequenceType::Ptr &returnType,
                                           const Expression::ID id = Expression::IDIgnorableExpression,
                                           const Expression::Properties props = Expression::Properties(),
                                           const StandardNamespaces::ID ns = StandardNamespaces::fn)
        {
            const QXmlName name(ns, localName);

            const FunctionSignature::Ptr s(new FunctionSignature(name, minArgs, maxArgs,
                                                                 returnType, props, id));

            m_signatures.insert(name, s);
            return s;
        }

        static inline QXmlName::LocalNameCode argument(const NamePool::Ptr &np, const char *const name)
        {
            return np->allocateLocalName(QLatin1String(name));
        }

        FunctionSignature::Hash m_signatures;

    private:
        /**
         * @short Determines whether @p arity is a valid number of
         * arguments for the function with signature @p sign.
         *
         * If it is not, a static error with error code ReportContext::XPST0017
         * is issued via @p context.
         */
        void verifyArity(const FunctionSignature::Ptr &sign,
                         const StaticContext::Ptr &context,
                         const xsInteger arity,
                         const SourceLocationReflection *const r) const;

    };
}

QT_END_NAMESPACE

QT_END_HEADER

#endif
