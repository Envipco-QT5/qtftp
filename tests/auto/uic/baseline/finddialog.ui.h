/*
*********************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
**
** This file is part of the Qt Linguist of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License versions 2.0 or 3.0 as published by the Free Software
** Foundation and appearing in the files LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file.  Alternatively you may (at
** your option) use any later version of the GNU General Public
** License if such license has been publicly approved by Nokia Corporation and/or its subsidiary(-ies)
** (or its successors, if any) and the KDE Free Qt Foundation. In
** addition, as a special exception, Trolltech gives you certain
** additional rights. These rights are described in the Trolltech GPL
** Exception version 1.2, which can be found at
** http://www.trolltech.com/products/qt/gplexception/ and in the file
** GPL_EXCEPTION.txt in this package.
**
** Please review the following information to ensure GNU General
** Public Licensing requirements will be met:
** http://trolltech.com/products/qt/licenses/licensing/opensource/. If
** you are unsure which license is appropriate for your use, please
** review the following information:
** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
** or contact the sales department at sales@trolltech.com.
**
** In addition, as a special exception, Trolltech, as the sole
** copyright holder for Qt Designer, grants users of the Qt/Eclipse
** Integration plug-in the right for the Qt/Eclipse Integration to
** link to functionality provided by Qt Designer and its related
** libraries.
**
** This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
** INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE. Trolltech reserves all rights not expressly
** granted herein.
**
*********************************************************************
*/

/********************************************************************************
** Form generated from reading ui file 'finddialog.ui'
**
** Created: Mon Sep 1 09:31:03 2008
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FindDialog
{
public:
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout1;
    QLabel *findWhat;
    QLineEdit *led;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QCheckBox *sourceText;
    QCheckBox *translations;
    QCheckBox *matchCase;
    QCheckBox *comments;
    QCheckBox *ignoreAccelerators;
    QVBoxLayout *vboxLayout1;
    QPushButton *findNxt;
    QPushButton *cancel;
    QSpacerItem *spacerItem;

    void setupUi(QDialog *FindDialog)
    {
        if (FindDialog->objectName().isEmpty())
            FindDialog->setObjectName(QString::fromUtf8("FindDialog"));
        FindDialog->resize(414, 170);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(FindDialog->sizePolicy().hasHeightForWidth());
        FindDialog->setSizePolicy(sizePolicy);
        hboxLayout = new QHBoxLayout(FindDialog);
        hboxLayout->setSpacing(6);
        hboxLayout->setMargin(11);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setMargin(0);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setMargin(0);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        findWhat = new QLabel(FindDialog);
        findWhat->setObjectName(QString::fromUtf8("findWhat"));

        hboxLayout1->addWidget(findWhat);

        led = new QLineEdit(FindDialog);
        led->setObjectName(QString::fromUtf8("led"));

        hboxLayout1->addWidget(led);


        vboxLayout->addLayout(hboxLayout1);

        groupBox = new QGroupBox(FindDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setMargin(9);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        sourceText = new QCheckBox(groupBox);
        sourceText->setObjectName(QString::fromUtf8("sourceText"));
        sourceText->setChecked(true);

        gridLayout->addWidget(sourceText, 1, 0, 1, 1);

        translations = new QCheckBox(groupBox);
        translations->setObjectName(QString::fromUtf8("translations"));
        translations->setChecked(true);

        gridLayout->addWidget(translations, 2, 0, 1, 1);

        matchCase = new QCheckBox(groupBox);
        matchCase->setObjectName(QString::fromUtf8("matchCase"));

        gridLayout->addWidget(matchCase, 0, 1, 1, 1);

        comments = new QCheckBox(groupBox);
        comments->setObjectName(QString::fromUtf8("comments"));
        comments->setChecked(true);

        gridLayout->addWidget(comments, 0, 0, 1, 1);

        ignoreAccelerators = new QCheckBox(groupBox);
        ignoreAccelerators->setObjectName(QString::fromUtf8("ignoreAccelerators"));
        ignoreAccelerators->setChecked(true);

        gridLayout->addWidget(ignoreAccelerators, 1, 1, 1, 1);


        vboxLayout->addWidget(groupBox);


        hboxLayout->addLayout(vboxLayout);

        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setSpacing(6);
        vboxLayout1->setMargin(0);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        findNxt = new QPushButton(FindDialog);
        findNxt->setObjectName(QString::fromUtf8("findNxt"));
        findNxt->setDefault(true);
        findNxt->setFlat(false);

        vboxLayout1->addWidget(findNxt);

        cancel = new QPushButton(FindDialog);
        cancel->setObjectName(QString::fromUtf8("cancel"));

        vboxLayout1->addWidget(cancel);

        spacerItem = new QSpacerItem(20, 51, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout1->addItem(spacerItem);


        hboxLayout->addLayout(vboxLayout1);

#ifndef QT_NO_SHORTCUT
        findWhat->setBuddy(led);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(led, findNxt);
        QWidget::setTabOrder(findNxt, cancel);
        QWidget::setTabOrder(cancel, comments);
        QWidget::setTabOrder(comments, sourceText);
        QWidget::setTabOrder(sourceText, translations);
        QWidget::setTabOrder(translations, matchCase);

        retranslateUi(FindDialog);
        QObject::connect(cancel, SIGNAL(clicked()), FindDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(FindDialog);
    } // setupUi

    void retranslateUi(QDialog *FindDialog)
    {
        FindDialog->setWindowTitle(QApplication::translate("FindDialog", "Find", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        FindDialog->setWhatsThis(QApplication::translate("FindDialog", "This window allows you to search for some text in the translation source file.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        findWhat->setText(QApplication::translate("FindDialog", "&Find what:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        led->setWhatsThis(QApplication::translate("FindDialog", "Type in the text to search for.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        groupBox->setTitle(QApplication::translate("FindDialog", "Options", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        sourceText->setWhatsThis(QApplication::translate("FindDialog", "Source texts are searched when checked.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        sourceText->setText(QApplication::translate("FindDialog", "&Source texts", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        translations->setWhatsThis(QApplication::translate("FindDialog", "Translations are searched when checked.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        translations->setText(QApplication::translate("FindDialog", "&Translations", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        matchCase->setWhatsThis(QApplication::translate("FindDialog", "Texts such as 'TeX' and 'tex' are considered as different when checked.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        matchCase->setText(QApplication::translate("FindDialog", "&Match case", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        comments->setWhatsThis(QApplication::translate("FindDialog", "Comments and contexts are searched when checked.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        comments->setText(QApplication::translate("FindDialog", "&Comments", 0, QApplication::UnicodeUTF8));
        ignoreAccelerators->setText(QApplication::translate("FindDialog", "Ignore &accelerators", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        findNxt->setWhatsThis(QApplication::translate("FindDialog", "Click here to find the next occurrence of the text you typed in.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        findNxt->setText(QApplication::translate("FindDialog", "Find Next", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        cancel->setWhatsThis(QApplication::translate("FindDialog", "Click here to close this window.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        cancel->setText(QApplication::translate("FindDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(FindDialog);
    } // retranslateUi

};

namespace Ui {
    class FindDialog: public Ui_FindDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // FINDDIALOG_H
