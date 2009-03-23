/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the QtGui module of the Qt Toolkit.
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
** contact the sales department at qt-sales@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qgraphicsscene_bsp_p.h"

#ifndef QT_NO_GRAPHICSVIEW

#include <QtCore/qstring.h>
#include <private/qgraphicsitem_p.h>

QT_BEGIN_NAMESPACE

class QGraphicsSceneInsertItemBspTreeVisitor : public QGraphicsSceneBspTreeVisitor
{
public:
    QGraphicsItem *item;

    void visit(QList<QGraphicsItem *> *items)
    { items->prepend(item); }
};

class QGraphicsSceneRemoveItemBspTreeVisitor : public QGraphicsSceneBspTreeVisitor
{
public:
    QGraphicsItem *item;

    void visit(QList<QGraphicsItem *> *items)
    { items->removeAll(item); }
};

class QGraphicsSceneFindItemBspTreeVisitor : public QGraphicsSceneBspTreeVisitor
{
public:
    QList<QGraphicsItem *> *foundItems;

    void visit(QList<QGraphicsItem *> *items)
    {
        for (int i = 0; i < items->size(); ++i) {
            QGraphicsItem *item = items->at(i);
            if (!item->d_func()->itemDiscovered && item->isVisible()) {
                item->d_func()->itemDiscovered = 1;
                foundItems->prepend(item);
            }
        }
    }
};

QGraphicsSceneBspTree::QGraphicsSceneBspTree()
    : leafCnt(0)
{
    insertVisitor = new QGraphicsSceneInsertItemBspTreeVisitor;
    removeVisitor = new QGraphicsSceneRemoveItemBspTreeVisitor;
    findVisitor = new QGraphicsSceneFindItemBspTreeVisitor;
}

QGraphicsSceneBspTree::~QGraphicsSceneBspTree()
{
    delete insertVisitor;
    delete removeVisitor;
    delete findVisitor;
}

void QGraphicsSceneBspTree::initialize(const QRectF &rect, int depth)
{
    this->rect = rect;
    leafCnt = 0;
    nodes.resize((1 << (depth + 1)) - 1);
    nodes.fill(Node());
    leaves.resize(1 << depth);
    leaves.fill(QList<QGraphicsItem *>());

    initialize(rect, depth, 0);
}

void QGraphicsSceneBspTree::clear()
{
    leafCnt = 0;
    nodes.clear();
    leaves.clear();
}

void QGraphicsSceneBspTree::insertItem(QGraphicsItem *item, const QRectF &rect)
{
    insertVisitor->item = item;
    climbTree(insertVisitor, rect);
}

void QGraphicsSceneBspTree::removeItem(QGraphicsItem *item, const QRectF &rect)
{
    removeVisitor->item = item;
    climbTree(removeVisitor, rect);
}

void QGraphicsSceneBspTree::removeItems(const QSet<QGraphicsItem *> &items)
{
    for (int i = 0; i < leaves.size(); ++i) {
        QList<QGraphicsItem *> newItemList;
        const QList<QGraphicsItem *> &oldItemList = leaves[i];
        for (int j = 0; j < oldItemList.size(); ++j) {
            QGraphicsItem *item = oldItemList.at(j);
            if (!items.contains(item))
                newItemList << item;
        }
        leaves[i] = newItemList;
    }
}

QList<QGraphicsItem *> QGraphicsSceneBspTree::items(const QRectF &rect)
{
    QList<QGraphicsItem *> tmp;
    findVisitor->foundItems = &tmp;
    climbTree(findVisitor, rect);
    return tmp;
}

QList<QGraphicsItem *> QGraphicsSceneBspTree::items(const QPointF &pos)
{
    QList<QGraphicsItem *> tmp;
    findVisitor->foundItems = &tmp;
    climbTree(findVisitor, pos);
    return tmp;
}

int QGraphicsSceneBspTree::leafCount() const
{
    return leafCnt;
}

QString QGraphicsSceneBspTree::debug(int index) const
{
    const Node *node = &nodes.at(index);

    QString tmp;
    if (node->type == Node::Leaf) {
        QRectF rect = rectForIndex(index);
        if (!leaves[node->leafIndex].isEmpty()) {
            tmp += QString::fromLatin1("[%1, %2, %3, %4] contains %5 items\n")
                   .arg(rect.left()).arg(rect.top())
                   .arg(rect.width()).arg(rect.height())
                   .arg(leaves[node->leafIndex].size());
        }
    } else {
        if (node->type == Node::Horizontal) {
            tmp += debug(firstChildIndex(index));
            tmp += debug(firstChildIndex(index) + 1);
        } else {
            tmp += debug(firstChildIndex(index));
            tmp += debug(firstChildIndex(index) + 1);
        }
    }

    return tmp;
}

void QGraphicsSceneBspTree::initialize(const QRectF &rect, int depth, int index)
{
    Node *node = &nodes[index];
    if (index == 0) {
        node->type = Node::Horizontal;
        node->offset = rect.center().x();
    }

    if (depth) {
        Node::Type type;
        QRectF rect1, rect2;
        qreal offset1, offset2;

        if (node->type == Node::Horizontal) {
            type = Node::Vertical;
            rect1.setRect(rect.left(), rect.top(), rect.width(), rect.height() / 2);
            rect2.setRect(rect1.left(), rect1.bottom(), rect1.width(), rect.height() - rect1.height());
            offset1 = rect1.center().x();
            offset2 = rect2.center().x();
        } else {
            type = Node::Horizontal;
            rect1.setRect(rect.left(), rect.top(), rect.width() / 2, rect.height());
            rect2.setRect(rect1.right(), rect1.top(), rect.width() - rect1.width(), rect1.height());
            offset1 = rect1.center().y();
            offset2 = rect2.center().y();
        }

        int childIndex = firstChildIndex(index);

        Node *child = &nodes[childIndex];
        child->offset = offset1;
        child->type = type;

        child = &nodes[childIndex + 1];
        child->offset = offset2;
        child->type = type;

        initialize(rect1, depth - 1, childIndex);
        initialize(rect2, depth - 1, childIndex + 1);
    } else {
        node->type = Node::Leaf;
        node->leafIndex = leafCnt++;
    }
}

void QGraphicsSceneBspTree::climbTree(QGraphicsSceneBspTreeVisitor *visitor, const QPointF &pos, int index)
{
    if (nodes.isEmpty())
        return;

    const Node &node = nodes.at(index);
    int childIndex = firstChildIndex(index);

    switch (node.type) {
    case Node::Leaf: {
        visitor->visit(&leaves[node.leafIndex]);
        break;
    }
    case Node::Vertical:
        if (pos.x() < node.offset) {
            climbTree(visitor, pos, childIndex);
        } else {
            climbTree(visitor, pos, childIndex + 1);
        }
        break;
    case Node::Horizontal:
        if (pos.y() < node.offset) {
            climbTree(visitor, pos, childIndex);
        } else {
            climbTree(visitor, pos, childIndex + 1);
        }
        break;
    }
}

void QGraphicsSceneBspTree::climbTree(QGraphicsSceneBspTreeVisitor *visitor, const QRectF &rect, int index)
{
    if (nodes.isEmpty())
        return;

    const Node &node = nodes.at(index);
    int childIndex = firstChildIndex(index);

    switch (node.type) {
    case Node::Leaf: {
        visitor->visit(&leaves[node.leafIndex]);
        break;
    }
    case Node::Vertical:
        if (rect.left() < node.offset) {
            climbTree(visitor, rect, childIndex);
            if (rect.right() >= node.offset)
                climbTree(visitor, rect, childIndex + 1);
        } else {
            climbTree(visitor, rect, childIndex + 1);
        }
        break;
    case Node::Horizontal:
        int childIndex = firstChildIndex(index);
        if (rect.top() < node.offset) {
            climbTree(visitor, rect, childIndex);
            if (rect.bottom() >= node.offset)
                climbTree(visitor, rect, childIndex + 1);
        } else {
            climbTree(visitor, rect, childIndex + 1);
        }
    }
}

QRectF QGraphicsSceneBspTree::rectForIndex(int index) const
{
    if (index <= 0)
        return rect;

    int parentIdx = parentIndex(index);
    QRectF rect = rectForIndex(parentIdx);
    const Node *parent = &nodes.at(parentIdx);

    if (parent->type == Node::Horizontal) {
        if (index & 1)
            rect.setRight(parent->offset);
        else
            rect.setLeft(parent->offset);
    } else {
        if (index & 1)
            rect.setBottom(parent->offset);
        else
            rect.setTop(parent->offset);
    }

    return rect;
}

QT_END_NAMESPACE

#endif // QT_NO_GRAPHICSVIEW
