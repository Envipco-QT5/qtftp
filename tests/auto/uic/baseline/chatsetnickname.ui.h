/********************************************************************************
** Form generated from reading ui file 'chatsetnickname.ui'
**
** Created: Thu Jul 10 09:47:34 2008
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef CHATSETNICKNAME_H
#define CHATSETNICKNAME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NicknameDialog
{
public:
    QVBoxLayout *vboxLayout;
    QVBoxLayout *vboxLayout1;
    QLabel *label;
    QLineEdit *nickname;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QSpacerItem *spacerItem1;

    void setupUi(QDialog *NicknameDialog)
    {
        if (NicknameDialog->objectName().isEmpty())
            NicknameDialog->setObjectName(QString::fromUtf8("NicknameDialog"));
        NicknameDialog->resize(396, 105);
        QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(1), static_cast<QSizePolicy::Policy>(1));
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(NicknameDialog->sizePolicy().hasHeightForWidth());
        NicknameDialog->setSizePolicy(sizePolicy);
        vboxLayout = new QVBoxLayout(NicknameDialog);
#ifndef Q_OS_MAC
        vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout->setMargin(9);
#endif
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout1 = new QVBoxLayout();
#ifndef Q_OS_MAC
        vboxLayout1->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout1->setMargin(0);
#endif
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        label = new QLabel(NicknameDialog);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        vboxLayout1->addWidget(label);

        nickname = new QLineEdit(NicknameDialog);
        nickname->setObjectName(QString::fromUtf8("nickname"));

        vboxLayout1->addWidget(nickname);


        vboxLayout->addLayout(vboxLayout1);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setMargin(0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(NicknameDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(NicknameDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);

        spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem1);


        vboxLayout->addLayout(hboxLayout);


        retranslateUi(NicknameDialog);
        QObject::connect(okButton, SIGNAL(clicked()), NicknameDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), NicknameDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(NicknameDialog);
    } // setupUi

    void retranslateUi(QDialog *NicknameDialog)
    {
        NicknameDialog->setWindowTitle(QApplication::translate("NicknameDialog", "Set nickname", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("NicknameDialog", "New nickname:", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("NicknameDialog", "OK", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("NicknameDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(NicknameDialog);
    } // retranslateUi

};

namespace Ui {
    class NicknameDialog: public Ui_NicknameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CHATSETNICKNAME_H
