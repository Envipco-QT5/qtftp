/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the documentation of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

//! [0]
// all 5 strings share the same data
QString s1 = "abcd";
QString s2 = s1;
QString s3 = s2;
QString s4 = s3;
QString s5 = s2;
//! [0]


//! [1]
// s1, s2 and s5 share the same data, neither s3 nor s4 are shared
QString s1 = "abcd";
QString s2 = s1;
Q3DeepCopy<QString> s3 = s2;  // s3 is a deep copy of s2
QString s4 = s3;             // s4 is a deep copy of s3
QString s5 = s2;
//! [1]


//! [2]
// s1, s2 and s5 share the same data, s3 and s4 share the same data
QString s1 = "abcd";
QString s2 = s1;
QString s3 = Q3DeepCopy<QString>( s2 );  // s3 is a deep copy of s2
QString s4 = s3;                        // s4 is a shallow copy of s3
QString s5 = s2;
//! [2]


//! [3]
Q3DeepCopy<QString> global_string;  // global string data
QMutex global_mutex;               // mutex to protext global_string

...

void setGlobalString( const QString &str )
{
    global_mutex.lock();
    global_string = str;           // global_string is a deep copy of str
    global_mutex.unlock();
}

...

void MyThread::run()
{
    global_mutex.lock();
    QString str = global_string;          // str is a deep copy of global_string
    global_mutex.unlock();

    // process the string data
    ...

    // update global_string
    setGlobalString( str );
}
//! [3]
