/********************************************************************************
** Form generated from reading ui file 'Widget.ui'
**
** Created: Thu Jul 10 09:47:35 2008
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef WIDGET_H
#define WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *vboxLayout;
    QLabel *Alabel;
    QGroupBox *groupBox;
    QPushButton *pushButton;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(400, 300);
        vboxLayout = new QVBoxLayout(Form);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        Alabel = new QLabel(Form);
        Alabel->setObjectName(QString::fromUtf8("Alabel"));

        vboxLayout->addWidget(Alabel);

        groupBox = new QGroupBox(Form);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));

        vboxLayout->addWidget(groupBox);

        pushButton = new QPushButton(Form);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        vboxLayout->addWidget(pushButton);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0, QApplication::UnicodeUTF8));
        Alabel->setText(QApplication::translate("Form", "A label.\n"
"One new line.\n"
"Another new line.\n"
"Last line.", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Form", "A Group Box", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Form", "PushButton", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(Form);
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // WIDGET_H
