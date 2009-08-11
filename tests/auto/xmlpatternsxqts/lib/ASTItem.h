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
/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Patternist project on Trolltech Labs.
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
***************************************************************************
*/

#ifndef PatternistSDK_ASTItem_H
#define PatternistSDK_ASTItem_H

#include <QList>
#include <QString>

#include "TreeItem.h"
#include "Global.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace QPatternistSDK
{
    /**
     * @short Is a node in a ASTItem tree; each ASTItem contains
     * debug information about an QPatternist::Expression.
     *
     * ASTItem, by implementing TreeItem, leverages debug data about QPatternist::Expression
     * instances into Qt's model/view framework.
     *
     * @ingroup PatternistSDK
     * @author Frans Englich <fenglich@trolltech.com>
     */
    class Q_PATTERNISTSDK_EXPORT ASTItem : public TreeItem
    {
    public:
        virtual ~ASTItem();
        ASTItem(ASTItem *parent,
                const QString &name,
                const QString &details = QString(),
                const QString &staticType = QString(),
                const QString &reqType = QString());

        virtual void appendChild(TreeItem *item);
        virtual TreeItem *child(const unsigned int row) const;
        virtual unsigned int childCount() const;
        virtual QVariant data(const Qt::ItemDataRole role, int column) const;
        virtual TreeItem::List children() const;
        virtual TreeItem *parent() const;
        int columnCount() const;

        /**
         * Returns a string representation of this AST node, recursively including
         * children. For example, the query <tt>1 eq number()</tt> would result in the string:
         *
@verbatim
ValueComparison(eq)
  xs:integer(0)
  FunctionCall(fn:number)
    ContextItem
@endverbatim
         */
        QString toString() const;

    private:
        QString toString(const QString &indent) const;

        const QString m_name;
        const QString m_details;
        const QString m_reqType;
        const QString m_staticType;
        TreeItem::List m_children;
        TreeItem *m_parent;
    };
}

QT_END_NAMESPACE

QT_END_HEADER

#endif
// vim: et:ts=4:sw=4:sts=4
