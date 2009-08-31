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

#ifndef Patternist_FunctionArgument_H
#define Patternist_FunctionArgument_H

#include <QList>
#include <QSharedData>

#include "qxmlname.h"
#include "qsequencetype_p.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace QPatternist
{
    /**
     * @short Carries meta data for a function argument as found in XPath's
     * builtin functions and user declared functions in XQuery and XSL-T.
     *
     * @ingroup Patternist_functions
     * @see VariableDeclaration
     * @author Frans Englich <frans.englich@nokia.com>
     */
    class FunctionArgument : public QSharedData
    {
    public:
        typedef QExplicitlySharedDataPointer<FunctionArgument> Ptr;
        typedef QList<FunctionArgument::Ptr> List;

        FunctionArgument(const QXmlName name,
                         const SequenceType::Ptr &type);

        QXmlName name() const;
        SequenceType::Ptr type() const;

    private:
        Q_DISABLE_COPY(FunctionArgument)
        const QXmlName m_name;
        const SequenceType::Ptr m_type;
    };
}

QT_END_NAMESPACE

QT_END_HEADER

#endif
