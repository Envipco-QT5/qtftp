/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
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
** contact the sales department at http://www.qtsoftware.com/contact.
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
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
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
** contact the sales department at http://www.qtsoftware.com/contact.
** $QT_END_LICENSE$
**
***************************************************************************
*/

#ifndef PatternistSDK_TreeItem_H
#define PatternistSDK_TreeItem_H

#include <QObject>

#include "Global.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

class QVariant;
template<typename T> class QList;
template<typename T> class QPointer;

namespace QPatternistSDK
{
    /**
     * @short TreeItem is a node in a hierachial structure and is used together
     * with TreeModel.
     *
     * TreeItem is abstract base class. Instances of sub-classes of TreeItem
     * can be used with TreeModel in order to use hierarchial data in Qt's
     * model/view framework.
     *
     * TreeItem is a QObject in order to be able to be used with QPointer.
     *
     * @author Frans Englich <fenglich@trolltech.com>
     * @see TreeModel
     * @ingroup PatternistSDK
     */
    class Q_PATTERNISTSDK_EXPORT TreeItem : public QObject
    {
        Q_OBJECT
    public:
        typedef QList<QPointer<TreeItem> > List;

        virtual ~TreeItem() {}
        virtual void appendChild(TreeItem *item) = 0;
        virtual TreeItem *child(const unsigned int row) const = 0;
        virtual unsigned int childCount() const = 0;
        virtual TreeItem *parent() const = 0;

        virtual TreeItem::List children() const = 0;
        virtual int columnCount() const = 0;

        /**
         * Determines the position among the children of
         * this TreeItem's parent. This is done by introspecting the result
         * of children().
         */
        int row() const;

        virtual QVariant data(const Qt::ItemDataRole role, int column) const = 0;

    Q_SIGNALS:
        /**
         * Emitted whenever this item changed. This is used for keeping
         * views in synchronization with the item model which houses
         * this item.
         *
         * @param item the item which changed. That is, this TreeItem.
         */
        void changed(TreeItem *item);
    };
}

QT_END_NAMESPACE

QT_END_HEADER

#endif
// vim: et:ts=4:sw=4:sts=4
