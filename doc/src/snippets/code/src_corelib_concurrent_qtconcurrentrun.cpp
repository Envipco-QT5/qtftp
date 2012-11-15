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
extern void aFunction();
QFuture<void> future = QtConcurrent::run(aFunction);
//! [0]


//! [1]
extern void aFunctionWithArguments(int arg1, double arg2, const QString &string);

int integer = ...;
double floatingPoint = ...;
QString string = ...;

QFuture<void> future = QtConcurrent::run(aFunctionWithArguments, integer, floatingPoint, string);
//! [1]


//! [2]
extern QString functionReturningAString();
QFuture<QString> future = QtConcurrent::run(functionReturningAString);
...
QString result = future.result();
//! [2]


//! [3]
extern QString someFunction(const QByteArray &input);

QByteArray bytearray = ...;

QFuture<QString> future = QtConcurrent::run(someFunction, bytearray);
...
QString result = future.result();
//! [3]


//! [4]
// call 'QStringList QString::split(const QString &sep, SplitBehavior behavior, Qt::CaseSensitivity cs) const' in a separate thread
QString string = ...;
QFuture<QStringList> future = QtConcurrent::run(string, &QString::split, QString(", "), QString::KeepEmptyParts, Qt::CaseSensitive);
...
QStringList result = future.result();
//! [4]


//! [5]
// call 'void QImage::invertPixels(InvertMode mode)' in a separate thread
QImage image = ...;
QFuture<void> future = QtConcurrent::run(image, &QImage::invertPixels, QImage::InvertRgba);
...
future.waitForFinished();
// At this point, the pixels in 'image' have been inverted
//! [5]


//! [6]
void someFunction(int arg1, double arg2);
QFuture<void> future = QtConcurrent::run(boost::bind(someFunction, 1, 2.0));
...
//! [6]
