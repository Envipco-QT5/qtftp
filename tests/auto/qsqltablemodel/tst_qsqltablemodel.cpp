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
#include "../qsqldatabase/tst_databases.h"
#include <QtSql>

//TESTED_CLASS=
//TESTED_FILES=

Q_DECLARE_METATYPE(QModelIndex)

class tst_QSqlTableModel : public QObject
{
    Q_OBJECT

public:
    tst_QSqlTableModel();
    virtual ~tst_QSqlTableModel();


    void dropTestTables();
    void createTestTables();
    void recreateTestTables();
    void repopulateTestTables();

    tst_Databases dbs;

public slots:
    void initTestCase_data();
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();
private slots:

    void select();
    void submitAll();
    void setRecord_data();
    void setRecord();
    void insertRow();
    void insertRecord();
    void insertMultiRecords();
    void removeRow();
    void removeRows();
    void removeInsertedRow();
    void setFilter();
    void setInvalidFilter();

    void emptyTable();
    void tablesAndSchemas();
    void whitespaceInIdentifiers();
    void primaryKeyOrder();

    void sqlite_bigTable();

    // bug specific tests
    void insertRecordBeforeSelect();
    void submitAllOnInvalidTable();
    void insertRecordsInLoop();
    void sqlite_attachedDatabase(); // For task 130799
};

tst_QSqlTableModel::tst_QSqlTableModel()
{
    qRegisterMetaType<QModelIndex>("QModelIndex");
    dbs.open();
}

tst_QSqlTableModel::~tst_QSqlTableModel()
{
}

void tst_QSqlTableModel::dropTestTables()
{
    for (int i = 0; i < dbs.dbNames.count(); ++i) {
        QSqlDatabase db = QSqlDatabase::database(dbs.dbNames.at(i));
        QSqlQuery q(db);

        QStringList tableNames;
        tableNames << qTableName("test")
                   << qTableName("test2")
                   << qTableName("test3")
                   << qTableName("emptytable")
                   << qTableName("bigtable");
        if (testWhiteSpaceNames(db.driverName()))
            tableNames << qTableName("qtestw hitespace");

        tst_Databases::safeDropTables(db, tableNames);

        if (db.driverName().startsWith("QPSQL")) {
            q.exec("DROP SCHEMA " + qTableName("testschema") + " CASCADE");
        }
    }
}

void tst_QSqlTableModel::createTestTables()
{
    for (int i = 0; i < dbs.dbNames.count(); ++i) {
        QSqlDatabase db = QSqlDatabase::database(dbs.dbNames.at(i));
        QSqlQuery q(db);

        QVERIFY_SQL( q, exec("create table " + qTableName("test") + "(id int, name varchar(20), title int)"));

        QVERIFY_SQL( q, exec("create table " + qTableName("test2") + "(id int, title varchar(20))"));

        QVERIFY_SQL( q, exec("create table " + qTableName("test3") + "(id int, random varchar(20), randomtwo varchar(20))"));

        QVERIFY_SQL( q, exec("create table " + qTableName("emptytable") + "(id int)"));

        if (testWhiteSpaceNames(db.driverName())) {
            QString qry = "create table " + qTableName("qtestw hitespace", db.driver()) + " ("+ db.driver()->escapeIdentifier("a field", QSqlDriver::FieldName) + " int)";
            QVERIFY_SQL( q, exec(qry));
        }
    }
}

void tst_QSqlTableModel::repopulateTestTables()
{
    for (int i = 0; i < dbs.dbNames.count(); ++i) {
        QSqlDatabase db = QSqlDatabase::database(dbs.dbNames.at(i));
        QSqlQuery q(db);

        QVERIFY_SQL( q, exec("delete from " + qTableName("test")));
        QVERIFY_SQL( q, exec("insert into " + qTableName("test") + " values(1, 'harry', 1)"));
        QVERIFY_SQL( q, exec("insert into " + qTableName("test") + " values(2, 'trond', 2)"));
        QVERIFY_SQL( q, exec("insert into " + qTableName("test") + " values(3, 'vohi', 3)"));

        QVERIFY_SQL( q, exec("delete from " + qTableName("test2")));
        QVERIFY_SQL( q, exec("insert into " + qTableName("test2") + " values(1, 'herr')"));
        QVERIFY_SQL( q, exec("insert into " + qTableName("test2") + " values(2, 'mister')"));

        QVERIFY_SQL( q, exec("delete from " + qTableName("test3")));
        QVERIFY_SQL( q, exec("insert into " + qTableName("test3") + " values(1, 'foo', 'bar')"));
        QVERIFY_SQL( q, exec("insert into " + qTableName("test3") + " values(2, 'baz', 'joe')"));
    }
}

void tst_QSqlTableModel::recreateTestTables()
{
    dropTestTables();
    createTestTables();
    repopulateTestTables();
}

void tst_QSqlTableModel::initTestCase_data()
{
    if (dbs.fillTestTable() == 0) {
        qWarning("NO DATABASES");
        QSKIP("No database drivers are available in this Qt configuration", SkipAll);
    }
}

void tst_QSqlTableModel::initTestCase()
{
    recreateTestTables();
}

void tst_QSqlTableModel::cleanupTestCase()
{
    dropTestTables();
    dbs.close();
}

void tst_QSqlTableModel::init()
{
}

void tst_QSqlTableModel::cleanup()
{
    repopulateTestTables();
}

void tst_QSqlTableModel::select()
{
    QFETCH_GLOBAL(QString, dbName);
    QSqlDatabase db = QSqlDatabase::database(dbName);
    CHECK_DATABASE(db);

    QSqlTableModel model(0, db);
    model.setTable(qTableName("test"));
    model.setSort(0, Qt::AscendingOrder);
    QVERIFY_SQL(model, select());

    QCOMPARE(model.rowCount(), 3);
    QCOMPARE(model.columnCount(), 3);

    QCOMPARE(model.data(model.index(0, 0)).toInt(), 1);
    QCOMPARE(model.data(model.index(0, 1)).toString(), QString("harry"));
    QCOMPARE(model.data(model.index(0, 2)).toInt(), 1);
    QCOMPARE(model.data(model.index(0, 3)), QVariant());

    QCOMPARE(model.data(model.index(1, 0)).toInt(), 2);
    QCOMPARE(model.data(model.index(1, 1)).toString(), QString("trond"));
    QCOMPARE(model.data(model.index(1, 2)).toInt(), 2);
    QCOMPARE(model.data(model.index(1, 3)), QVariant());

    QCOMPARE(model.data(model.index(2, 0)).toInt(), 3);
    QCOMPARE(model.data(model.index(2, 1)).toString(), QString("vohi"));
    QCOMPARE(model.data(model.index(2, 2)).toInt(), 3);
    QCOMPARE(model.data(model.index(2, 3)), QVariant());

    QCOMPARE(model.data(model.index(3, 0)), QVariant());
    QCOMPARE(model.data(model.index(3, 1)), QVariant());
    QCOMPARE(model.data(model.index(3, 2)), QVariant());
    QCOMPARE(model.data(model.index(3, 3)), QVariant());
}

void tst_QSqlTableModel::setRecord_data()
{
    QTest::addColumn<uint>("submitpolicy");
    QTest::newRow("OnFieldChange") << (uint)QSqlTableModel::OnFieldChange;
    QTest::newRow("OnRowChange") << (uint)QSqlTableModel::OnRowChange;
    QTest::newRow("OnManualSubmit") << (uint)QSqlTableModel::OnManualSubmit;
}

void tst_QSqlTableModel::setRecord()
{
	// This needs to be tested with ODBC, which requires a manual change to qsqldatabase\tst_databases.h
	// to ensure an ODBC db is added

    QFETCH_GLOBAL(QString, dbName);
    QFETCH(uint, submitpolicy);
    QSqlDatabase db = QSqlDatabase::database(dbName);
    CHECK_DATABASE(db);

    QSqlTableModel model(0, db);
    model.setEditStrategy((QSqlTableModel::EditStrategy)submitpolicy);
    model.setTable(qTableName("test3"));
    model.setSort(0, Qt::AscendingOrder);
    QVERIFY_SQL(model, select());

    for (int i = 0; i < model.rowCount(); ++i) {
        QSignalSpy spy(&model, SIGNAL(dataChanged(QModelIndex,QModelIndex)));

        QSqlRecord rec = model.record(i);
        rec.setValue(1, rec.value(1).toString() + 'X');
        rec.setValue(2, rec.value(2).toString() + 'X');
        QVERIFY(model.setRecord(i, rec));

        if ((QSqlTableModel::EditStrategy)submitpolicy == QSqlTableModel::OnManualSubmit)
            QVERIFY(model.submitAll());
        else {
            // dataChanged() is not emitted when submitAll() is called
            QCOMPARE(spy.count(), 2);
            QCOMPARE(spy.at(0).count(), 2);
            QCOMPARE(qvariant_cast<QModelIndex>(spy.at(0).at(0)), model.index(i, 1));
            QCOMPARE(qvariant_cast<QModelIndex>(spy.at(0).at(1)), model.index(i, 1));
        }
    }

    QCOMPARE(model.data(model.index(0, 1)).toString(), QString("fooX"));
    QCOMPARE(model.data(model.index(0, 2)).toString(), QString("barX"));
    QCOMPARE(model.data(model.index(1, 1)).toString(), QString("bazX"));
    QCOMPARE(model.data(model.index(1, 2)).toString(), QString("joeX"));
}

void tst_QSqlTableModel::insertRow()
{
    QFETCH_GLOBAL(QString, dbName);
    QSqlDatabase db = QSqlDatabase::database(dbName);
    CHECK_DATABASE(db);

    QSqlTableModel model(0, db);
    model.setEditStrategy(QSqlTableModel::OnRowChange);
    model.setTable(qTableName("test"));
    model.setSort(0, Qt::AscendingOrder);
    QVERIFY_SQL(model, select());

    QVERIFY(model.insertRow(2));
    QSqlRecord rec = model.record(1);
    rec.setValue(0, 42);
    rec.setValue(1, QString("vohi"));
    QVERIFY(model.setRecord(2, rec));

    QCOMPARE(model.data(model.index(2, 0)).toInt(), 42);
    QCOMPARE(model.data(model.index(2, 1)).toString(), QString("vohi"));
    QCOMPARE(model.data(model.index(2, 2)).toInt(), 2);

    QVERIFY(model.submitAll());
}

void tst_QSqlTableModel::insertRecord()
{
    QFETCH_GLOBAL(QString, dbName);
    QSqlDatabase db = QSqlDatabase::database(dbName);
    CHECK_DATABASE(db);

    QSqlTableModel model(0, db);
    model.setEditStrategy(QSqlTableModel::OnManualSubmit);
    model.setTable(qTableName("test"));
    model.setSort(0, Qt::AscendingOrder);
    QVERIFY_SQL(model, select());

    QSqlRecord rec = model.record();
    rec.setValue(0, 42);
    rec.setValue(1, QString("vohi"));
    rec.setValue(2, 1);
    QVERIFY(model.insertRecord(1, rec));
    QCOMPARE(model.rowCount(), 4);

    QCOMPARE(model.data(model.index(1, 0)).toInt(), 42);
    QCOMPARE(model.data(model.index(1, 1)).toString(), QString("vohi"));
    QCOMPARE(model.data(model.index(1, 2)).toInt(), 1);

    model.revertAll();
    model.setEditStrategy(QSqlTableModel::OnRowChange);

    QVERIFY(model.insertRecord(-1, rec));

    QCOMPARE(model.data(model.index(3, 0)).toInt(), 42);
    QCOMPARE(model.data(model.index(3, 1)).toString(), QString("vohi"));
    QCOMPARE(model.data(model.index(3, 2)).toInt(), 1);
}

void tst_QSqlTableModel::insertMultiRecords()
{
    QFETCH_GLOBAL(QString, dbName);
    QSqlDatabase db = QSqlDatabase::database(dbName);
    CHECK_DATABASE(db);

    QSqlTableModel model(0, db);
    model.setEditStrategy(QSqlTableModel::OnManualSubmit);
    model.setTable(qTableName("test"));
    model.setSort(0, Qt::AscendingOrder);
    QVERIFY_SQL(model, select());

    QCOMPARE(model.rowCount(), 3);

    QVERIFY(model.insertRow(2));

    QCOMPARE(model.data(model.index(2, 0)), QVariant());
    QCOMPARE(model.data(model.index(2, 1)), QVariant());
    QCOMPARE(model.data(model.index(2, 2)), QVariant());

    QVERIFY(model.insertRow(3));
    QVERIFY(model.insertRow(0));

    QCOMPARE(model.data(model.index(5, 0)).toInt(), 3);
    QCOMPARE(model.data(model.index(5, 1)).toString(), QString("vohi"));
    QCOMPARE(model.data(model.index(5, 2)).toInt(), 3);

    QVERIFY(model.setData(model.index(0, 0), QVariant(42)));
    QVERIFY(model.setData(model.index(3, 0), QVariant(43)));
    QVERIFY(model.setData(model.index(4, 0), QVariant(44)));
    QVERIFY(model.setData(model.index(4, 1), QVariant(QLatin1String("gunnar"))));
    QVERIFY(model.setData(model.index(4, 2), QVariant(1)));

    QVERIFY(model.submitAll());
    model.clear();
    model.setTable(qTableName("test"));
    model.setSort(0, Qt::AscendingOrder);
    QVERIFY_SQL(model, select());

    QCOMPARE(model.data(model.index(0, 0)).toInt(), 1);
    QCOMPARE(model.data(model.index(1, 0)).toInt(), 2);
    QCOMPARE(model.data(model.index(2, 0)).toInt(), 3);
    QCOMPARE(model.data(model.index(3, 0)).toInt(), 42);
    QCOMPARE(model.data(model.index(4, 0)).toInt(), 43);
    QCOMPARE(model.data(model.index(5, 0)).toInt(), 44);
    QCOMPARE(model.data(model.index(5, 1)).toString(), QString("gunnar"));
    QCOMPARE(model.data(model.index(5, 2)).toInt(), 1);
}

void tst_QSqlTableModel::submitAll()
{
    QFETCH_GLOBAL(QString, dbName);
    QSqlDatabase db = QSqlDatabase::database(dbName);
    CHECK_DATABASE(db);

    QSqlTableModel model(0, db);
    model.setTable(qTableName("test"));
    model.setSort(0, Qt::AscendingOrder);
    model.setEditStrategy(QSqlTableModel::OnManualSubmit);
    QVERIFY_SQL(model, select());

    QVERIFY(model.setData(model.index(0, 1), "harry2", Qt::EditRole));
    QVERIFY(model.setData(model.index(1, 1), "trond2", Qt::EditRole));

    QCOMPARE(model.data(model.index(0, 1)).toString(), QString("harry2"));
    QCOMPARE(model.data(model.index(1, 1)).toString(), QString("trond2"));

    QVERIFY_SQL(model, submitAll());

    QCOMPARE(model.data(model.index(0, 1)).toString(), QString("harry2"));
    QCOMPARE(model.data(model.index(1, 1)).toString(), QString("trond2"));

    QVERIFY(model.setData(model.index(0, 1), "harry", Qt::EditRole));
    QVERIFY(model.setData(model.index(1, 1), "trond", Qt::EditRole));

    QCOMPARE(model.data(model.index(0, 1)).toString(), QString("harry"));
    QCOMPARE(model.data(model.index(1, 1)).toString(), QString("trond"));

    QVERIFY_SQL(model, submitAll());

    QCOMPARE(model.data(model.index(0, 1)).toString(), QString("harry"));
    QCOMPARE(model.data(model.index(1, 1)).toString(), QString("trond"));
}

void tst_QSqlTableModel::removeRow()
{
    QFETCH_GLOBAL(QString, dbName);
    QSqlDatabase db = QSqlDatabase::database(dbName);
    CHECK_DATABASE(db);

    QSqlTableModel model(0, db);
    model.setTable(qTableName("test"));
    model.setSort(0, Qt::AscendingOrder);
    model.setEditStrategy(QSqlTableModel::OnManualSubmit);
    QVERIFY_SQL(model, select());
    QCOMPARE(model.rowCount(), 3);

    // headerDataChanged must be emitted by the model when the edit strategy is OnManualSubmit,
    // when OnFieldChange or OnRowChange it's not needed because the model will re-select.
    qRegisterMetaType<Qt::Orientation>("Qt::Orientation");
    QSignalSpy headerDataChangedSpy(&model, SIGNAL(headerDataChanged(Qt::Orientation, int, int)));

    QVERIFY(model.removeRow(1));
    QCOMPARE(headerDataChangedSpy.count(), 1);
    QCOMPARE(*static_cast<const Qt::Orientation *>(headerDataChangedSpy.at(0).value(0).constData()), Qt::Vertical);
    QCOMPARE(headerDataChangedSpy.at(0).at(1).toInt(), 1);
    QCOMPARE(headerDataChangedSpy.at(0).at(2).toInt(), 1);
    QVERIFY(model.submitAll());
    QCOMPARE(model.rowCount(), 2);

    QCOMPARE(model.data(model.index(0, 0)).toInt(), 1);
    QCOMPARE(model.data(model.index(1, 0)).toInt(), 3);
    model.clear();

    recreateTestTables();

    model.setTable(qTableName("test"));
    model.setEditStrategy(QSqlTableModel::OnRowChange);
    QVERIFY_SQL(model, select());
    QCOMPARE(model.rowCount(), 3);

    headerDataChangedSpy.clear();
    QVERIFY(model.removeRow(1));
    QCOMPARE(headerDataChangedSpy.count(), 0);
    QCOMPARE(model.rowCount(), 2);

    QCOMPARE(model.data(model.index(0, 1)).toString(), QString("harry"));
    QCOMPARE(model.data(model.index(1, 1)).toString(), QString("vohi"));
}

void tst_QSqlTableModel::removeRows()
{
    QFETCH_GLOBAL(QString, dbName);
    QSqlDatabase db = QSqlDatabase::database(dbName);
    CHECK_DATABASE(db);

    QSqlTableModel model(0, db);
    model.setTable(qTableName("test"));
    model.setSort(0, Qt::AscendingOrder);
    model.setEditStrategy(QSqlTableModel::OnFieldChange);
    QVERIFY_SQL(model, select());
    QCOMPARE(model.rowCount(), 3);

    QSignalSpy beforeDeleteSpy(&model, SIGNAL(beforeDelete(int)));
    QVERIFY_SQL(model, removeRows(0, 2));
    QVERIFY(beforeDeleteSpy.count() == 2);
    QVERIFY(beforeDeleteSpy.at(0).at(0).toInt() == 0);
    QVERIFY(beforeDeleteSpy.at(1).at(0).toInt() == 1);
    QCOMPARE(model.rowCount(), 1);
    QCOMPARE(model.data(model.index(0, 1)).toString(), QString("vohi"));
    model.clear();

    recreateTestTables();
    model.setTable(qTableName("test"));
    model.setEditStrategy(QSqlTableModel::OnManualSubmit);
    QVERIFY_SQL(model, select());
    QCOMPARE(model.rowCount(), 3);
    beforeDeleteSpy.clear();

    // When the edit strategy is OnManualSubmit the beforeDelete() signal
    // isn't emitted until submitAll() is called.
    qRegisterMetaType<Qt::Orientation>("Qt::Orientation");
    QSignalSpy headerDataChangedSpy(&model, SIGNAL(headerDataChanged(Qt::Orientation, int, int)));
    QVERIFY(model.removeRows(0, 2, QModelIndex()));
    QCOMPARE(headerDataChangedSpy.count(), 2);
    QCOMPARE(headerDataChangedSpy.at(0).at(1).toInt(), 0);
    QCOMPARE(headerDataChangedSpy.at(0).at(2).toInt(), 0);
    QCOMPARE(headerDataChangedSpy.at(1).at(1).toInt(), 1);
    QCOMPARE(headerDataChangedSpy.at(1).at(2).toInt(), 1);
    QCOMPARE(model.rowCount(), 3);
    QVERIFY(beforeDeleteSpy.count() == 0);
    QVERIFY(model.submitAll());
    QVERIFY(beforeDeleteSpy.count() == 2);
    QVERIFY(beforeDeleteSpy.at(0).at(0).toInt() == 0);
    QVERIFY(beforeDeleteSpy.at(1).at(0).toInt() == 1);
    QCOMPARE(model.rowCount(), 1);
    QCOMPARE(model.data(model.index(0, 1)).toString(), QString("vohi"));
}

void tst_QSqlTableModel::removeInsertedRow()
{
    QFETCH_GLOBAL(QString, dbName);
    QSqlDatabase db = QSqlDatabase::database(dbName);
    CHECK_DATABASE(db);

    for (int i = 0; i <= 1; ++i) {

        QSqlTableModel model(0, db);
        model.setTable(qTableName("test"));
        model.setSort(0, Qt::AscendingOrder);

        model.setEditStrategy(i == 0
                ? QSqlTableModel::OnRowChange : QSqlTableModel::OnManualSubmit);
        QVERIFY_SQL(model, select());
        QCOMPARE(model.rowCount(), 3);

        QVERIFY(model.insertRow(1));
        QCOMPARE(model.rowCount(), 4);

        QVERIFY(model.removeRow(1));
        QCOMPARE(model.rowCount(), 3);

        QCOMPARE(model.data(model.index(0, 1)).toString(), QString("harry"));
        QCOMPARE(model.data(model.index(1, 1)).toString(), QString("trond"));
        QCOMPARE(model.data(model.index(2, 1)).toString(), QString("vohi"));
        model.clear();

        recreateTestTables();
    }
}

void tst_QSqlTableModel::emptyTable()
{
    QFETCH_GLOBAL(QString, dbName);
    QSqlDatabase db = QSqlDatabase::database(dbName);
    CHECK_DATABASE(db);

    QSqlTableModel model(0, db);
    QCOMPARE(model.rowCount(), 0);
    QCOMPARE(model.columnCount(), 0);

    model.setTable(qTableName("emptytable"));
    QCOMPARE(model.rowCount(), 0);
    QCOMPARE(model.columnCount(), 1);

    QVERIFY_SQL(model, select());
    QCOMPARE(model.rowCount(), 0);
    QCOMPARE(model.columnCount(), 1);
}

void tst_QSqlTableModel::tablesAndSchemas()
{
    QFETCH_GLOBAL(QString, dbName);
    QSqlDatabase db = QSqlDatabase::database(dbName);
    CHECK_DATABASE(db);

    DBMS_SPECIFIC(db, "QPSQL");

    QSqlQuery q(db);
    q.exec("DROP SCHEMA " + qTableName("testschema") + " CASCADE");
    QVERIFY_SQL( q, exec("create schema " + qTableName("testschema")));
    QString tableName = qTableName("testschema") + '.' + qTableName("testtable");
    QVERIFY_SQL( q, exec("create table " + tableName + "(id int)"));
    QVERIFY_SQL( q, exec("insert into " + tableName + " values(1)"));
    QVERIFY_SQL( q, exec("insert into " + tableName + " values(2)"));

    QSqlTableModel model(0, db);
    model.setTable(tableName);
    QVERIFY_SQL(model, select());
    QCOMPARE(model.rowCount(), 2);
    QCOMPARE(model.columnCount(), 1);
}

void tst_QSqlTableModel::whitespaceInIdentifiers()
{
    QFETCH_GLOBAL(QString, dbName);
    QSqlDatabase db = QSqlDatabase::database(dbName);
    CHECK_DATABASE(db);

    if (!testWhiteSpaceNames(db.driverName()))
        QSKIP("DBMS doesn't support whitespaces in identifiers", SkipSingle);

    QString tableName = qTableName("qtestw hitespace", db.driver());

    QSqlTableModel model(0, db);
    model.setTable(tableName);
    QVERIFY_SQL(model, select());
}

void tst_QSqlTableModel::primaryKeyOrder()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "primaryKeyOrderTest");
    db.setDatabaseName(":memory:");
    QVERIFY_SQL(db, open());

    QSqlQuery q(db);

    QVERIFY_SQL( q, exec("create table foo(a varchar(20), id int primary key, b varchar(20))"));

    QSqlTableModel model(0, db);
    model.setTable("foo");

    QSqlIndex pk = model.primaryKey();
    QCOMPARE(pk.count(), 1);
    QCOMPARE(pk.fieldName(0), QLatin1String("id"));

    QVERIFY(model.insertRow(0));
    QVERIFY(model.setData(model.index(0, 0), "hello"));
    QVERIFY(model.setData(model.index(0, 1), 42));
    QVERIFY(model.setData(model.index(0, 2), "blah"));
    QVERIFY_SQL(model, submitAll());

    QVERIFY(model.setData(model.index(0, 1), 43));
    QVERIFY_SQL(model, submitAll());

    QCOMPARE(model.data(model.index(0, 1)).toInt(), 43);
}

void tst_QSqlTableModel::setInvalidFilter()
{
    QFETCH_GLOBAL(QString, dbName);
    QSqlDatabase db = QSqlDatabase::database(dbName);
    CHECK_DATABASE(db);

    // set an invalid filter, make sure it fails
    QSqlTableModel model(0, db);
    model.setTable(qTableName("test"));
    model.setFilter("blahfahsel");

    QCOMPARE(model.filter(), QString("blahfahsel"));
    QVERIFY(!model.select());

    // set a valid filter later, make sure if passes
    model.setFilter("id = 1");
    QVERIFY_SQL(model, select());
}

void tst_QSqlTableModel::setFilter()
{
    QFETCH_GLOBAL(QString, dbName);
    QSqlDatabase db = QSqlDatabase::database(dbName);
    CHECK_DATABASE(db);

    QSqlTableModel model(0, db);
    model.setTable(qTableName("test"));
    model.setFilter("id = 1");
    QCOMPARE(model.filter(), QString("id = 1"));
    QVERIFY_SQL(model, select());

    QCOMPARE(model.rowCount(), 1);
    QCOMPARE(model.data(model.index(0, 0)).toInt(), 1);

    QSignalSpy rowsRemovedSpy(&model, SIGNAL(rowsRemoved(QModelIndex,int,int)));
    QSignalSpy rowsAboutToBeRemovedSpy(&model,
            SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int)));
    QSignalSpy rowsInsertedSpy(&model, SIGNAL(rowsInserted(QModelIndex,int,int)));
    QSignalSpy rowsAboutToBeInsertedSpy(&model,
            SIGNAL(rowsAboutToBeInserted(QModelIndex,int,int)));
    model.setFilter("id = 2");

    // check the signals
    QCOMPARE(rowsAboutToBeRemovedSpy.count(), 1);
    QCOMPARE(rowsRemovedSpy.count(), 1);
    QCOMPARE(rowsAboutToBeInsertedSpy.count(), 1);
    QCOMPARE(rowsInsertedSpy.count(), 1);
    QList<QVariant> args = rowsAboutToBeRemovedSpy.takeFirst();
    QCOMPARE(args.count(), 3);
    QCOMPARE(qvariant_cast<QModelIndex>(args.at(0)), QModelIndex());
    QCOMPARE(args.at(1).toInt(), 0);
    QCOMPARE(args.at(2).toInt(), 0);
    args = rowsRemovedSpy.takeFirst();
    QCOMPARE(args.count(), 3);
    QCOMPARE(qvariant_cast<QModelIndex>(args.at(0)), QModelIndex());
    QCOMPARE(args.at(1).toInt(), 0);
    QCOMPARE(args.at(2).toInt(), 0);
    args = rowsInsertedSpy.takeFirst();
    QCOMPARE(args.count(), 3);
    QCOMPARE(qvariant_cast<QModelIndex>(args.at(0)), QModelIndex());
    QCOMPARE(args.at(1).toInt(), 0);
    QCOMPARE(args.at(2).toInt(), 0);
    args = rowsAboutToBeInsertedSpy.takeFirst();
    QCOMPARE(args.count(), 3);
    QCOMPARE(qvariant_cast<QModelIndex>(args.at(0)), QModelIndex());
    QCOMPARE(args.at(1).toInt(), 0);
    QCOMPARE(args.at(2).toInt(), 0);

    QCOMPARE(model.rowCount(), 1);
    QCOMPARE(model.data(model.index(0, 0)).toInt(), 2);
}

void tst_QSqlTableModel::sqlite_bigTable()
{
    QFETCH_GLOBAL(QString, dbName);
    QSqlDatabase db = QSqlDatabase::database(dbName);
    CHECK_DATABASE(db);

    DBMS_SPECIFIC(db, "QSQLITE");

    bool hasTransactions = db.driver()->hasFeature(QSqlDriver::Transactions);
    if (hasTransactions) QVERIFY(db.transaction());
    QSqlQuery q(db);
    QVERIFY_SQL( q, exec("create table "+qTableName("bigtable")+"(id int primary key, name varchar)"));
    QVERIFY_SQL( q, prepare("insert into "+qTableName("bigtable")+"(id, name) values (?, ?)"));
    QTime startTime;
    startTime.start();
    for (int i = 0; i < 10000; ++i) {
        q.addBindValue(i);
        q.addBindValue(QString::number(i));
        if(i%1000 == 0 && startTime.elapsed() > 5000)
            qDebug() << i << "records written";
        QVERIFY_SQL( q, exec());
    }
    q.clear();
    if (hasTransactions) QVERIFY(db.commit());

    QSqlTableModel model(0, db);
    model.setTable(qTableName("bigtable"));
    QVERIFY_SQL(model, select());

    QSqlRecord rec = model.record();
    rec.setValue("id", 424242);
    rec.setValue("name", "Guillaume");
    QVERIFY_SQL(model, insertRecord(-1, rec));

    model.clear();
}

// For task 118547: couldn't insert records unless select()
// had first been called.
void tst_QSqlTableModel::insertRecordBeforeSelect()
{
    QFETCH_GLOBAL(QString, dbName);
    QSqlDatabase db = QSqlDatabase::database(dbName);
    CHECK_DATABASE(db);

    QSqlTableModel model(0, db);
    model.setTable(qTableName("test"));
    QCOMPARE(model.lastError().type(), QSqlError::NoError);

    QSqlRecord buffer = model.record();
    buffer.setValue("id", 13);
    buffer.setValue("name", QString("The Lion King"));
    buffer.setValue("title", 0);
    QVERIFY_SQL(model, insertRecord(-1, buffer));

    buffer.setValue("id", 26);
    buffer.setValue("name", QString("T. Leary"));
    buffer.setValue("title", 0);
    QVERIFY_SQL(model, insertRecord(1, buffer));

    int rowCount = model.rowCount();
    model.clear();
    QCOMPARE(model.rowCount(), 0);

    QSqlTableModel model2(0, db);
    model2.setTable(qTableName("test"));
    QVERIFY_SQL(model2, select());
    QCOMPARE(model2.rowCount(), rowCount);
}

// For task 118547: set errors if table doesn't exist and if records
// are inserted and submitted on a non-existing table.
void tst_QSqlTableModel::submitAllOnInvalidTable()
{
    QFETCH_GLOBAL(QString, dbName);
    QSqlDatabase db = QSqlDatabase::database(dbName);
    CHECK_DATABASE(db);

    QSqlTableModel model(0, db);
    model.setEditStrategy(QSqlTableModel::OnManualSubmit);

    // setTable returns a void, so the error can only be caught by
    // manually checking lastError(). ### Qt5: This should be changed!
    model.setTable(qTableName("invalidTable"));
    QCOMPARE(model.lastError().type(), QSqlError::StatementError);

    // This will give us an empty record which is expected behavior
    QSqlRecord buffer = model.record();
    buffer.setValue("bogus", 1000);
    buffer.setValue("bogus2", QString("I will go nowhere!"));

    // Inserting the record into the *model* will work (OnManualSubmit)
    QVERIFY_SQL(model, insertRecord(-1, buffer));

    // The submit and select shall fail because the table doesn't exist
    QEXPECT_FAIL("", "The table doesn't exist: submitAll() shall fail",
        Continue);
    QVERIFY_SQL(model, submitAll());
    QEXPECT_FAIL("", "The table doesn't exist: select() shall fail",
        Continue);
    QVERIFY_SQL(model, select());
}

// For task 147575: the rowsRemoved signal emitted from the model was lying
void tst_QSqlTableModel::insertRecordsInLoop()
{
    QFETCH_GLOBAL(QString, dbName);
    QSqlDatabase db = QSqlDatabase::database(dbName);
    CHECK_DATABASE(db);

    QSqlTableModel model(0, db);
    model.setTable(qTableName("test"));
    model.setEditStrategy(QSqlTableModel::OnManualSubmit);
    model.select();

    QSqlRecord record = model.record();
    record.setValue(0, 10);
    record.setValue(1, "Testman");
    record.setValue(2, 1);

    QSignalSpy spyRowsRemoved(&model, SIGNAL(rowsRemoved(const QModelIndex &, int, int)));
    QSignalSpy spyRowsInserted(&model, SIGNAL(rowsInserted(const QModelIndex &, int, int)));
    for (int i = 0; i < 10; i++) {
        QVERIFY(model.insertRecord(model.rowCount(), record));
        QCOMPARE(spyRowsInserted.at(i).at(1).toInt(), i+3); // The table already contains three rows
        QCOMPARE(spyRowsInserted.at(i).at(2).toInt(), i+3);
    }
    model.submitAll(); // submitAll() calls select() which clears and repopulates the table

    int firstRowIndex = 0, lastRowIndex = 12;
    QCOMPARE(spyRowsRemoved.count(), 1);
    QCOMPARE(spyRowsRemoved.at(0).at(1).toInt(), firstRowIndex);
    QCOMPARE(spyRowsRemoved.at(0).at(2).toInt(), lastRowIndex);

    QCOMPARE(spyRowsInserted.at(10).at(1).toInt(), firstRowIndex);
    QCOMPARE(spyRowsInserted.at(10).at(2).toInt(), lastRowIndex);
    QCOMPARE(spyRowsInserted.count(), 11);

    QCOMPARE(model.rowCount(), 13);
    QCOMPARE(model.columnCount(), 3);
}

void tst_QSqlTableModel::sqlite_attachedDatabase()
{
    QFETCH_GLOBAL(QString, dbName);
    QSqlDatabase db = QSqlDatabase::database(dbName);
    CHECK_DATABASE(db);

    DBMS_SPECIFIC(db, "QSQLITE");

    QSqlDatabase attachedDb = QSqlDatabase::cloneDatabase(db, db.driverName() + QLatin1String("attached"));
    attachedDb.setDatabaseName(db.databaseName()+QLatin1String("attached.dat"));
    QVERIFY_SQL(attachedDb, open());
    QSqlQuery q(attachedDb);
    tst_Databases::safeDropTables(attachedDb, QStringList() << "atest" << "atest2");
    QVERIFY_SQL( q, exec("CREATE TABLE atest(id int, text varchar(20))"));
    QVERIFY_SQL( q, exec("CREATE TABLE atest2(id int, text varchar(20))"));
    QVERIFY_SQL( q, exec("INSERT INTO atest VALUES(1, 'attached-atest')"));
    QVERIFY_SQL( q, exec("INSERT INTO atest2 VALUES(2, 'attached-atest2')"));

    QSqlQuery q2(db);
    tst_Databases::safeDropTables(db, QStringList() << "atest");
    QVERIFY_SQL(q2, exec("CREATE TABLE atest(id int, text varchar(20))"));
    QVERIFY_SQL(q2, exec("INSERT INTO atest VALUES(3, 'main')"));
    QVERIFY_SQL(q2, exec("ATTACH DATABASE \""+attachedDb.databaseName()+"\" as adb"));

    // This should query the table in the attached database (schema supplied)
    QSqlTableModel model(0, db);
    model.setTable("adb.atest");
    QVERIFY_SQL(model, select());
    QCOMPARE(model.rowCount(), 1);
    QCOMPARE(model.data(model.index(0, 0), Qt::DisplayRole).toInt(), 1);
    QCOMPARE(model.data(model.index(0, 1), Qt::DisplayRole).toString(), QLatin1String("attached-atest"));

    // This should query the table in the attached database (unique tablename)
    model.setTable("atest2");
    QVERIFY_SQL(model, select());
    QCOMPARE(model.rowCount(), 1);
    QCOMPARE(model.data(model.index(0, 0), Qt::DisplayRole).toInt(), 2);
    QCOMPARE(model.data(model.index(0, 1), Qt::DisplayRole).toString(), QLatin1String("attached-atest2"));

    // This should query the table in the main database (tables in main db has 1st priority)
    model.setTable("atest");
    QVERIFY_SQL(model, select());
    QCOMPARE(model.rowCount(), 1);
    QCOMPARE(model.data(model.index(0, 0), Qt::DisplayRole).toInt(), 3);
    QCOMPARE(model.data(model.index(0, 1), Qt::DisplayRole).toString(), QLatin1String("main"));
}

QTEST_MAIN(tst_QSqlTableModel)
#include "tst_qsqltablemodel.moc"
