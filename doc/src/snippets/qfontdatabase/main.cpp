/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the documentation of the Qt Toolkit.
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
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
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

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

//! [0]
    QFontDatabase database;
    QTreeWidget fontTree;
    fontTree.setColumnCount(2);
    fontTree.setHeaderLabels(QStringList() << "Font" << "Smooth Sizes");

    foreach (QString family, database.families()) {
        QTreeWidgetItem *familyItem = new QTreeWidgetItem(&fontTree);
        familyItem->setText(0, family);

        foreach (QString style, database.styles(family)) {
            QTreeWidgetItem *styleItem = new QTreeWidgetItem(familyItem);
            styleItem->setText(0, style);

            QString sizes;
            foreach (int points, database.smoothSizes(family, style))
                sizes += QString::number(points) + " ";

            styleItem->setText(1, sizes.trimmed());
        }
//! [0] //! [1]
    }
//! [1]

    fontTree.resizeColumnToContents(0);
    fontTree.show();
    return app.exec();
}
