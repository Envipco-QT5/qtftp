/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
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

#ifndef XBELREADER_H
#define XBELREADER_H

#include <QIcon>
#include <QXmlStreamReader>

QT_BEGIN_NAMESPACE
class QTreeWidget;
class QTreeWidgetItem;
QT_END_NAMESPACE

//! [0]
class XbelReader : public QXmlStreamReader
{
public:
//! [1]
    XbelReader(QTreeWidget *treeWidget);
//! [1]

    bool read(QIODevice *device);

private:
//! [2]
    void readUnknownElement();
    void readXBEL();
    void readTitle(QTreeWidgetItem *item);
    void readSeparator(QTreeWidgetItem *item);
    void readFolder(QTreeWidgetItem *item);
    void readBookmark(QTreeWidgetItem *item);

    QTreeWidgetItem *createChildItem(QTreeWidgetItem *item);

    QTreeWidget *treeWidget;
//! [2]

    QIcon folderIcon;
    QIcon bookmarkIcon;
};
//! [0]

#endif
