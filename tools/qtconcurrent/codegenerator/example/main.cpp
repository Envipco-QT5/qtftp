/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the tools applications of the Qt Toolkit.
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
#include <QDebug>
#include "codegenerator.h"
using namespace CodeGenerator;

int main()
{
    // The code generator works on items. Each item has a generate() function:
    Item item("");
    qDebug() << item.generate(); // produces "".
    
    // There are several Item subclasses. Text items contains a text string which they
    // reproduce when generate is called:
    Text text(" Hi there");
    qDebug() << text.generate(); // produces " Hi there".
    
    // Items can be concatenated:
    Item sentence = text + Text(" Bye there") ;
    qDebug() << sentence.generate(); // produces "Hi there Bye there".
    // (Internally, this creates a tree of items, and generate is called recursively 
    // for items that have children.)

    // Repeater items repeat their content when generate is called:
    Repeater repeater = text;
    repeater.setRepeatCount(3);
    qDebug() << repeater.generate(); // produces "Hi there Hi there Hi there".
    
    // Counters evaluate to the current repeat index.
    Repeater repeater2 = text + Counter();
    repeater2.setRepeatCount(3);
    qDebug() << repeater2.generate(); // produces "Hi there0 Hi there1 Hi there2".

    // Groups provide sub-groups which are repeated according to the current repeat index.
    // Counters inside Groups evaluate to the local repeat index for the Group.
    Group arguments("Arg" + Counter()  + " arg" + Counter());
    Repeater function("void foo(" + arguments + ");\n");
    function.setRepeatCount(3);
    qDebug() << function.generate();

    // Produces:
    // void foo(Arg1 arg1);
    // void foo(Arg1 arg1, Arg2 arg2);
    // void foo(Arg1 arg1, Arg2 arg2, Arg3 arg3);
}
