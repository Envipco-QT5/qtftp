/********************************************************************************
** Form generated from reading ui file 'textfinder.ui'
**
** Created: Mon Sep 1 09:31:03 2008
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef TEXTFINDER_H
#define TEXTFINDER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *vboxLayout;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit;
    QLabel *searchLabel;
    QPushButton *findButton;
    QTextEdit *textEdit;
    QSpacerItem *spacerItem;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(378, 158);
        vboxLayout = new QVBoxLayout(Form);
#ifndef Q_OS_MAC
        vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout->setMargin(9);
#endif
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        gridLayout = new QGridLayout();
#ifndef Q_OS_MAC
        gridLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout->setMargin(0);
#endif
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lineEdit = new QLineEdit(Form);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        searchLabel = new QLabel(Form);
        searchLabel->setObjectName(QString::fromUtf8("searchLabel"));

        gridLayout->addWidget(searchLabel, 0, 0, 1, 1);

        findButton = new QPushButton(Form);
        findButton->setObjectName(QString::fromUtf8("findButton"));

        gridLayout->addWidget(findButton, 0, 2, 1, 1);


        vboxLayout->addLayout(gridLayout);

        textEdit = new QTextEdit(Form);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        vboxLayout->addWidget(textEdit);

        spacerItem = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem);

#ifndef QT_NO_SHORTCUT
        searchLabel->setBuddy(lineEdit);
#endif // QT_NO_SHORTCUT

        retranslateUi(Form);
        QObject::connect(lineEdit, SIGNAL(returnPressed()), findButton, SLOT(animateClick()));

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Find Text", 0, QApplication::UnicodeUTF8));
        searchLabel->setText(QApplication::translate("Form", "&Keyword:", 0, QApplication::UnicodeUTF8));
        findButton->setText(QApplication::translate("Form", "&Find", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(Form);
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // TEXTFINDER_H
