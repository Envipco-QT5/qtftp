/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtScript module of the Qt Toolkit.
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

#include <QtCore/QTextStream>

#ifndef QT_NO_SCRIPT

#include "qscriptasm_p.h"
#include "qscriptvalueimpl_p.h"
#include "qscriptengine_p.h"
#include "qscriptcontext_p.h"
#include "qscriptmember_p.h"
#include "qscriptobject_p.h"

QT_BEGIN_NAMESPACE

const char *QScriptInstruction::opcode[] = {
#define STR(a) #a
#define Q_SCRIPT_DEFINE_OPERATOR(op) STR(i##op) ,
#include "instruction.table"
#undef Q_SCRIPT_DEFINE_OPERATOR
#undef STR
};

void QScriptInstruction::print(QTextStream &out) const
{
    out << opcode[op];

    if (! operand[0].isValid())
        return;

    out << '(' << operand[0].toString();

    if (operand[1].isValid())
        out << ", " << operand[1].toString();

    out << ')';
}

namespace QScript {

Code::Code():
    optimized(false),
    firstInstruction(0),
    lastInstruction(0),
    astPool(0)
{
}

Code::~Code()
{
    delete[] firstInstruction;
}

void Code::init(const CompilationUnit &compilation, NodePool *pool)
{
    optimized = false;
    const QVector<QScriptInstruction> ilist = compilation.instructions();
    firstInstruction = new QScriptInstruction[ilist.count()];
    lastInstruction = firstInstruction + ilist.count();
    qCopy(ilist.begin(), ilist.end(), firstInstruction);
    exceptionHandlers = compilation.exceptionHandlers();
    astPool = pool;
}

} // namespace QScript

QT_END_NAMESPACE

#endif // QT_NO_SCRIPT
