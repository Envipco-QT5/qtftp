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

#include <QtGui>

#include "xbelwriter.h"

//! [0]
XbelWriter::XbelWriter(QTreeWidget *treeWidget)
    : treeWidget(treeWidget)
{
    setAutoFormatting(true);
}
//! [0]

//! [1]
bool XbelWriter::writeFile(QIODevice *device)
{
    setDevice(device);

    writeStartDocument();
    writeDTD("<!DOCTYPE xbel>");
    writeStartElement("xbel");
    writeAttribute("version", "1.0");
    for (int i = 0; i < treeWidget->topLevelItemCount(); ++i)
        writeItem(treeWidget->topLevelItem(i));

    writeEndDocument();
    return true;
}
//! [1]

//! [2]
void XbelWriter::writeItem(QTreeWidgetItem *item)
{
    QString tagName = item->data(0, Qt::UserRole).toString();
    if (tagName == "folder") {
        bool folded = !treeWidget->isItemExpanded(item);
        writeStartElement(tagName);
        writeAttribute("folded", folded ? "yes" : "no");
        writeTextElement("title", item->text(0));
        for (int i = 0; i < item->childCount(); ++i)
            writeItem(item->child(i));
        writeEndElement();
    } else if (tagName == "bookmark") {
        writeStartElement(tagName);
        if (!item->text(1).isEmpty())
            writeAttribute("href", item->text(1));
        writeTextElement("title", item->text(0));
        writeEndElement();
    } else if (tagName == "separator") {
        writeEmptyElement(tagName);
    }
}
//! [2]
