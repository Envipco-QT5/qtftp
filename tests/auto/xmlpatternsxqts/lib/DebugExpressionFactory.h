/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the test suite of the Qt Toolkit.
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

#ifndef PatternistSDK_DebugExpressionFactory_H
#define PatternistSDK_DebugExpressionFactory_H

#include "Global.h"
#include "qexpressionfactory_p.h"
#include "qfunctionfactory_p.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace QPatternistSDK
{
    class ASTItem;

    /**
     * @short Is a QPatternist::ExpressionFactory, with the
     * difference that it provides the hooks for building from a tree of
     * debug data from the compiled expression.
     *
     * This tree can be retrieved via astTree(). The astTree() function
     * returns the AST built the last time createExpression() was called.
     *
     * @ingroup PatternistSDK
     * @author Frans Englich <frans.englich@nokia.com>
     */
    class Q_PATTERNISTSDK_EXPORT DebugExpressionFactory : public QPatternist::ExpressionFactory
    {
    public:
        DebugExpressionFactory() : m_ast(0)
        {
        }

        typedef QExplicitlySharedDataPointer<DebugExpressionFactory> Ptr;
        /**
         * Identical to ExpressionFactory::createExpression() with the difference
         * that it builds an ASTItem tree which can be accessed via astTree().
         */
        virtual QPatternist::Expression::Ptr createExpression(QIODevice *const expr,
                                                              const QPatternist::StaticContext::Ptr &context,
                                                              const QXmlQuery::QueryLanguage lang,
                                                              const QPatternist::SequenceType::Ptr &requiredType,
                                                              const QUrl &queryURI,
                                                              const QXmlName &initialTemplateName);

        /**
         * @returns an ASTItem tree built for the last created expression,
         * via createExpression().
         */
        virtual ASTItem *astTree() const;

        /**
         * @returns a list containing string representations of all available
         * functions in Patternist. Each QString in the returned QStringList
         * is a function synopsis for human consumption.
         */
        static QStringList availableFunctionSignatures();

    protected:
        /**
         * Performs the ASTItem tree building.
         */
        virtual void processTreePass(const QPatternist::Expression::Ptr &tree,
                                     const CompilationStage stage);

        void processTemplateRule(const QPatternist::Expression::Ptr &body,
                                 const QPatternist::TemplatePattern::Ptr &pattern,
                                 const QXmlName &mode,
                                 const TemplateCompilationStage stage);

        void processNamedTemplate(const QXmlName &name,
                                  const QPatternist::Expression::Ptr &body,
                                  const TemplateCompilationStage stage);
    private:
        static ASTItem *buildASTTree(const QPatternist::Expression::Ptr &expr,
                                     ASTItem *const parent,
                                     const QPatternist::SequenceType::Ptr &reqType);
        ASTItem *m_ast;
    };
}

QT_END_NAMESPACE

QT_END_HEADER

#endif
// vim: et:ts=4:sw=4:sts=4
