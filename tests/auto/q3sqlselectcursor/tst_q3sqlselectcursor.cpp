/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
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
** contact the sales department at qt-sales@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/


#include <QtTest/QtTest>

#include <q3sqlselectcursor.h>

#include <qsqldriver.h>

#define NODATABASE_SKIP "No database drivers are available in this Qt configuration"


#include "../qsqldatabase/tst_databases.h"

//TESTED_FILES=

QT_FORWARD_DECLARE_CLASS(QSqlDatabase)

class tst_Q3SqlSelectCursor : public QObject
{
Q_OBJECT

public:
    tst_Q3SqlSelectCursor();
    virtual ~tst_Q3SqlSelectCursor();


public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();
private slots:
    void value_data() { generic_data(); }
    void value();
    void _exec_data() { generic_data(); }
    void _exec();

private:
    void generic_data();
    void createTestTables( QSqlDatabase db );
    void dropTestTables( QSqlDatabase db );
    void populateTestTables( QSqlDatabase db );

    tst_Databases dbs;
};

tst_Q3SqlSelectCursor::tst_Q3SqlSelectCursor()
{
}

tst_Q3SqlSelectCursor::~tst_Q3SqlSelectCursor()
{
}

void tst_Q3SqlSelectCursor::generic_data()
{
    if ( dbs.fillTestTable() == 0 )
        QSKIP( "No database drivers are available in this Qt configuration", SkipAll );
}

void tst_Q3SqlSelectCursor::createTestTables( QSqlDatabase db )
{
    if ( !db.isValid() )
	return;
    QSqlQuery q( db );
    // please never ever change this table; otherwise fix all tests ;)
    QVERIFY_SQL(q, exec( "create table " + qTableName( "qtest" ) + " ( id int not null, t_varchar varchar(40) not null,"
	    "t_char char(40), t_numeric numeric(6, 3), primary key (id, t_varchar) )" ));
}

void tst_Q3SqlSelectCursor::dropTestTables( QSqlDatabase db )
{
    tst_Databases::safeDropTables( db, QStringList() << qTableName( "qtest" ) );
}

void tst_Q3SqlSelectCursor::populateTestTables( QSqlDatabase db )
{
    if ( !db.isValid() )
	return;
    QSqlQuery q( db );

    q.exec( "delete from " + qTableName( "qtest" ) ); //non-fatal
    QVERIFY_SQL(q, exec( "insert into " + qTableName( "qtest" ) + " (id, t_varchar, t_char, t_numeric) values ( 0, 'VarChar0', 'Char0', 1.1 )" ));
    QVERIFY_SQL(q, exec( "insert into " + qTableName( "qtest" ) + " (id, t_varchar, t_char, t_numeric) values ( 1, 'VarChar1', 'Char1', 2.2 )" ));
    QVERIFY_SQL(q, exec( "insert into " + qTableName( "qtest" ) + " (id, t_varchar, t_char, t_numeric) values ( 2, 'VarChar2', 'Char2', 3.3 )" ));
    QVERIFY_SQL(q, exec( "insert into " + qTableName( "qtest" ) + " (id, t_varchar, t_char, t_numeric) values ( 3, 'VarChar3', 'Char3', 4.4 )" ));
}

void tst_Q3SqlSelectCursor::initTestCase()
{
    dbs.open();

    for ( QStringList::ConstIterator it = dbs.dbNames.begin(); it != dbs.dbNames.end(); ++it ) {
	QSqlDatabase db = QSqlDatabase::database( (*it) );
	CHECK_DATABASE( db );

	dropTestTables( db ); //in case of leftovers
	createTestTables( db );
	populateTestTables( db );
    }
}

void tst_Q3SqlSelectCursor::cleanupTestCase()
{
    for ( QStringList::ConstIterator it = dbs.dbNames.begin(); it != dbs.dbNames.end(); ++it ) {
	QSqlDatabase db = QSqlDatabase::database( (*it) );
	CHECK_DATABASE( db );
	dropTestTables( db );
    }

    dbs.close();
}

void tst_Q3SqlSelectCursor::init()
{
}

void tst_Q3SqlSelectCursor::cleanup()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    if ( QTest::currentTestFailed() ) {
	//since Oracle ODBC totally craps out on error, we init again
	db.close();
	db.open();
    }
}

void tst_Q3SqlSelectCursor::value()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    Q3SqlSelectCursor cur( "select * from " + qTableName( "qtest" ) + " order by id", db );
    QVERIFY( cur.select() );
    QVERIFY_SQL(cur, isActive());
    int i = 0;
    while ( cur.next() ) {
	QVERIFY( cur.value( "id" ).toInt() == i );
	i++;
    }
}

void tst_Q3SqlSelectCursor::_exec()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );
    
    Q3SqlSelectCursor cur( QString(), db );
    QVERIFY_SQL(cur, isActive() == false);

    cur.exec( "select * from " + qTableName( "qtest" ) ); //nothing should happen
    QVERIFY_SQL(cur, isActive());
    int i = 0;
    while ( cur.next() ) {
	QVERIFY( cur.value( "id" ).toInt() == i );
	i++;
    }
}


QTEST_MAIN(tst_Q3SqlSelectCursor)
#include "tst_q3sqlselectcursor.moc"
