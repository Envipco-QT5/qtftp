/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the demonstration applications of the Qt Toolkit.
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

#ifndef TOOLBARSEARCH_H
#define TOOLBARSEARCH_H

#include "searchlineedit.h"

QT_BEGIN_NAMESPACE
class QUrl;
class QAction;
class QStringListModel;
QT_END_NAMESPACE

class AutoSaver;

class ToolbarSearch : public SearchLineEdit
{
    Q_OBJECT

signals:
    void search(const QUrl &url);

public:
    ToolbarSearch(QWidget *parent = 0);
    ~ToolbarSearch();

public slots:
    void clear();
    void searchNow();

private slots:
    void save();
    void aboutToShowMenu();
    void triggeredMenuAction(QAction *action);

private:
    void load();

    AutoSaver *m_autosaver;
    int m_maxSavedSearches;
    QStringListModel *m_stringListModel;
};

#endif // TOOLBARSEARCH_H

