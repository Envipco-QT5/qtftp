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

#ifndef QSCRIPTECMAERROR_P_H
#define QSCRIPTECMAERROR_P_H

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

#include "qscriptecmacore_p.h"

#ifndef QT_NO_SCRIPT

QT_BEGIN_NAMESPACE

namespace QScript { namespace Ecma {

class Error: public Core
{
public:
    Error(QScriptEnginePrivate *engine);
    virtual ~Error();

    virtual void execute(QScriptContextPrivate *context);

    virtual void mark(QScriptEnginePrivate *eng, int generation);

    void newError(QScriptValueImpl *result, const QString &message = QString());
    void newEvalError(QScriptValueImpl *result, const QString &message = QString());
    void newRangeError(QScriptValueImpl *result, const QString &message = QString());
    void newReferenceError(QScriptValueImpl *result, const QString &message = QString());
    void newSyntaxError(QScriptValueImpl *result, const QString &message = QString());
    void newTypeError(QScriptValueImpl *result, const QString &message = QString());
    void newURIError(QScriptValueImpl *result, const QString &message = QString());

    bool isEvalError(const QScriptValueImpl &value) const;
    bool isRangeError(const QScriptValueImpl &value) const;
    bool isReferenceError(const QScriptValueImpl &value) const;
    bool isSyntaxError(const QScriptValueImpl &value) const;
    bool isTypeError(const QScriptValueImpl &value) const;
    bool isURIError(const QScriptValueImpl &value) const;

    static QStringList backtrace(const QScriptValueImpl &error);

    QScriptValueImpl evalErrorCtor;
    QScriptValueImpl rangeErrorCtor;
    QScriptValueImpl referenceErrorCtor;
    QScriptValueImpl syntaxErrorCtor;
    QScriptValueImpl typeErrorCtor;
    QScriptValueImpl uriErrorCtor;

    QScriptValueImpl evalErrorPrototype;
    QScriptValueImpl rangeErrorPrototype;
    QScriptValueImpl referenceErrorPrototype;
    QScriptValueImpl syntaxErrorPrototype;
    QScriptValueImpl typeErrorPrototype;
    QScriptValueImpl uriErrorPrototype;

protected:
    static QScriptValueImpl method_toString(QScriptContextPrivate *context, QScriptEnginePrivate *eng, QScriptClassInfo *classInfo);
    static QScriptValueImpl method_backtrace(QScriptContextPrivate *context, QScriptEnginePrivate *eng, QScriptClassInfo *classInfo);

private:
    void newError(QScriptValueImpl *result, const QScriptValueImpl &proto,
                  const QString &message = QString());
    void newErrorPrototype(QScriptValueImpl *result, const QScriptValueImpl &proto,
                           QScriptValueImpl &ztor, const QString &name);
};

} } // namespace QScript::Ecma

QT_END_NAMESPACE

#endif // QT_NO_SCRIPT
#endif // QSCRIPTECMAERROR_P_H
