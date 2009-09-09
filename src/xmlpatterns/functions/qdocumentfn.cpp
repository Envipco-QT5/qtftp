/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
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

#include "qforclause_p.h"
#include "qfunctionfactory_p.h"
#include "qrangevariablereference_p.h"

#include "qdocumentfn_p.h"

QT_BEGIN_NAMESPACE

using namespace QPatternist;

Expression::Ptr DocumentFN::typeCheck(const StaticContext::Ptr &context,
                                      const SequenceType::Ptr &reqType)
{
    /* See the class documentation for the rewrite that we're doing here. */

    /* Generate type checking code for our operands such that they match. */
    typeCheckOperands(context);

    const QSourceLocation myLocation(context->locationFor(this));
    const FunctionFactory::Ptr functions(context->functionSignatures());

    Expression::Ptr uriSource;

    {
        Expression::List distinctValuesArgs;
        distinctValuesArgs.append(m_operands.first());

        uriSource = functions->createFunctionCall(QXmlName(StandardNamespaces::fn, StandardLocalNames::distinct_values),
                                                  distinctValuesArgs,
                                                  context,
                                                  this);
        context->addLocation(uriSource.data(), myLocation);
    }

    const VariableSlotID rangeSlot = context->allocateRangeSlot();
    const Expression::Ptr uriReference(new RangeVariableReference(uriSource, rangeSlot));
    context->addLocation(uriReference.data(), myLocation);

    Expression::List docArgs;

    if(m_operands.count() == 2)
    {
        Expression::List baseUriArgs;
        baseUriArgs.append(uriReference);
        baseUriArgs.append(m_operands.at(1));

        const Expression::Ptr fnBaseUri(functions->createFunctionCall(QXmlName(StandardNamespaces::fn, StandardLocalNames::resolve_uri),
                                                                      baseUriArgs,
                                                                      context,
                                                                      this));
        context->addLocation(fnBaseUri.data(), myLocation);
        docArgs.append(fnBaseUri);
    }
    else
        docArgs.append(uriReference);

    const Expression::Ptr fnDoc(functions->createFunctionCall(QXmlName(StandardNamespaces::fn, StandardLocalNames::doc),
                                                              docArgs,
                                                              context,
                                                              this));
    context->addLocation(fnDoc.data(), myLocation);


    Expression::Ptr newMe(new ForClause(rangeSlot,
                                        uriSource,
                                        fnDoc,
                                        -1 /* We have no position variable. */));

    Expression::Ptr oldMe(this);
    rewrite(oldMe, newMe, context);
    return newMe->typeCheck(context, reqType);
}

QT_END_NAMESPACE
