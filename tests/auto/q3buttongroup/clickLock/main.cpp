/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the test suite of the Qt Toolkit.
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
#include <QtGui>
#include <Qt3Support>
#include <QtTest/QtTest>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    Q3ButtonGroup bg;
    bg.setColumnLayout(0, Qt::Vertical);
    QHBoxLayout* layout = new QHBoxLayout;
    QBoxLayout* oldbox = qobject_cast<QBoxLayout*>(bg.layout());
    if (oldbox)
        oldbox->addLayout(layout);

    const int buttonCount = 7;
    QPushButton* buttons[buttonCount];
    for (int i = 0; i < buttonCount; ++i) {
        buttons[i] = new QPushButton(QString::number(i), &bg);
        layout->addWidget(buttons[i]);
    }
    bg.insert(buttons[buttonCount - 1] , buttonCount);

    bg.show();

    int clickCount = 10;
    for (int i = 0; i < clickCount; ++i) {
        QTest::mouseClick(buttons[buttonCount - 1], Qt::LeftButton);
        QApplication::processEvents();
    }
}
