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

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

//! [0]
#include <QSharedData>
#include <QString>

class EmployeeData : public QSharedData
{
  public:
    EmployeeData() : id(-1) { name.clear(); }
    EmployeeData(const EmployeeData &other)
        : QSharedData(other), id(other.id), name(other.name) { }
    ~EmployeeData() { }

    int id;
    QString name;
};

class Employee
{
  public:
//! [1]
    Employee() { d = new EmployeeData; }
//! [1] //! [2]
    Employee(int id, QString name) {
        d = new EmployeeData;
        setId(id);
        setName(name);
    }
//! [2] //! [7]
    Employee(const Employee &other) 
          : d (other.d) 
    { 
    } 
//! [7]  
//! [3]
    void setId(int id) { d->id = id; }
//! [3] //! [4]
    void setName(QString name) { d->name = name; }
//! [4]

//! [5]
    int id() const { return d->id; }
//! [5] //! [6]
    QString name() const { return d->name; }
//! [6]

  private:
    QSharedDataPointer<EmployeeData> d;
};
//! [0]

#endif
