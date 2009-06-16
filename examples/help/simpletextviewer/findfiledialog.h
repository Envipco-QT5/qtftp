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
** contact the sales department at http://www.qtsoftware.com/contact.
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef FINDFILEDIALOG_H
#define FINDFILEDIALOG_H

#include <QtGui/QDialog>

QT_BEGIN_NAMESPACE
class QComboBox;
class QDialogButtonBox;
class QLabel;
class QToolButton;
class QTreeWidget;
class QTreeWidgetItem;
QT_END_NAMESPACE

class Assistant;
class TextEdit;

//! [0]
class FindFileDialog : public QDialog
{
    Q_OBJECT

public:
    FindFileDialog(TextEdit *editor, Assistant *assistant);

private slots:
    void browse();
    void help();
    void openFile(QTreeWidgetItem *item = 0);
    void update();

private:
    void findFiles();
    void showFiles(const QStringList &files);

    void createButtons();
    void createComboBoxes();
    void createFilesTree();
    void createLabels();
    void createLayout();

    Assistant *currentAssistant;
    TextEdit *currentEditor;
    QTreeWidget *foundFilesTree;

    QComboBox *directoryComboBox;
    QComboBox *fileNameComboBox;

    QLabel *directoryLabel;
    QLabel *fileNameLabel;

    QDialogButtonBox *buttonBox;

    QToolButton *browseButton;
};
//! [0]

#endif
