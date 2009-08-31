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

#include "qtokenrevealer_p.h"

QT_BEGIN_NAMESPACE

using namespace QPatternist;

TokenRevealer::TokenRevealer(const QUrl &uri,
                              const Tokenizer::Ptr &other) : Tokenizer(uri)
                                                           , m_tokenizer(other)
{
    Q_ASSERT(other);
}

TokenRevealer::~TokenRevealer()
{
    qDebug() << "Tokens Revealed:" << m_result;
}

void TokenRevealer::setParserContext(const ParserContext::Ptr &parseInfo)
{
    m_tokenizer->setParserContext(parseInfo);
}

Tokenizer::Token TokenRevealer::nextToken(YYLTYPE *const sourceLocator)
{
    const Token token(m_tokenizer->nextToken(sourceLocator));
    const QString asString(tokenToString(token));
    const TokenType type = token.type;

    /* Indent. */
    switch(type)
    {
        case CURLY_LBRACE:
        {
            m_result += QLatin1Char('\n') + m_indentationString + asString + QLatin1Char('\n');
            m_indentationString.append(QLatin1String("    "));
            m_result += m_indentationString;
            break;
        }
        case CURLY_RBRACE:
        {
            m_indentationString.chop(4);
            m_result += QLatin1Char('\n') + m_indentationString + asString;
            break;
        }
        case SEMI_COLON:
        /* Fallthrough. */
        case COMMA:
        {
            m_result += asString + QLatin1Char('\n') + m_indentationString;
            break;
        }
        default:
            m_result += asString + QLatin1Char(' ');
    }

    return token;
}

int TokenRevealer::commenceScanOnly()
{
    return m_tokenizer->commenceScanOnly();
}

void TokenRevealer::resumeTokenizationFrom(const int position)
{
    m_tokenizer->resumeTokenizationFrom(position);
}

QT_END_NAMESPACE
