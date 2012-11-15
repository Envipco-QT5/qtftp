/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the test suite of the Qt Toolkit.
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


#include <QtTest/QtTest>

#include "qsqlrecord.h"
#include "qsqlfield.h"
#include "qstringlist.h"




#include <qsqlrecord.h>

//TESTED_CLASS=
//TESTED_FILES=

#define NUM_FIELDS 4

class tst_QSqlRecord : public QObject
{
Q_OBJECT

public:
    tst_QSqlRecord();
    virtual ~tst_QSqlRecord();


public slots:
    void init();
    void cleanup();
private slots:
    void value();
#ifdef QT3_SUPPORT
    void toStringList_data();
    void toStringList();
    void toString_data();
    void toString();
#endif // QT3_SUPPORT
    void setValue_data();
    void setValue();
    void setNull();
    void setGenerated();
    void remove();
    void position();
    void operator_Assign();
    void isNull();
    void isGenerated();
    void isEmpty();
    void insert();
    void fieldName();
    void field();
    void count();
    void contains();
    void clearValues_data();
    void clearValues();
    void clear();
    void append();

private:
    QSqlRecord* rec;
    QSqlField* fields[ NUM_FIELDS ];
    void createTestRecord();
};

tst_QSqlRecord::tst_QSqlRecord()
{
    rec = 0;
    for ( int i = 0; i < NUM_FIELDS; ++i )
        fields[ i ] = 0;
}

tst_QSqlRecord::~tst_QSqlRecord()
{
    delete rec;
    for ( int i = 0; i < NUM_FIELDS; ++i )
        delete fields[ i ];
    rec = 0;
}

void tst_QSqlRecord::init()
{
    cleanup();
}

void tst_QSqlRecord::cleanup()
{
    delete rec;
    for ( int i = 0; i < NUM_FIELDS; ++i ) {
	delete fields[ i ];
	fields[ i ] = 0;
    }
    rec = 0;
}

void tst_QSqlRecord::createTestRecord()
{
    delete rec;
    rec = new QSqlRecord();
    fields[ 0 ] = new QSqlField( "string", QVariant::String );
    fields[ 1 ] = new QSqlField( "int", QVariant::Int );
    fields[ 2 ] = new QSqlField( "double", QVariant::Double );
    fields[ 3 ] = new QSqlField( "bool", QVariant::Bool );
    for ( int i = 0; i < NUM_FIELDS; ++i )
	rec->append( *(fields[ i ] ) );
}


void tst_QSqlRecord::append()
{
    delete rec;
    rec = new QSqlRecord();
    rec->append( QSqlField( "string", QVariant::String ) );
    QCOMPARE( rec->field( 0 ).name(), (QString) "string" );
    QVERIFY( !rec->isEmpty() );
    QCOMPARE( (int)rec->count(), 1 );
    rec->append( QSqlField( "int", QVariant::Int ) );
    QCOMPARE( rec->field( 1 ).name(), (QString) "int" );
    QCOMPARE( (int)rec->count(), 2 );
    rec->append( QSqlField( "double", QVariant::Double ) );
    QCOMPARE( rec->field( 2 ).name(), (QString) "double" );
    QCOMPARE( (int)rec->count(), 3 );
    rec->append( QSqlField( "bool", QVariant::Bool ) );
    QCOMPARE( rec->field( 3 ).name(), (QString) "bool" );
    QCOMPARE( (int)rec->count(), 4 );
    QCOMPARE( rec->indexOf( "string" ), 0 );
    QCOMPARE( rec->indexOf( "int" ), 1 );
    QCOMPARE( rec->indexOf( "double" ), 2 );
    QCOMPARE( rec->indexOf( "bool" ), 3 );
#ifdef QT3_SUPPORT
    QCOMPARE( rec->position( "string" ), 0 );
    QCOMPARE( rec->position( "int" ), 1 );
    QCOMPARE( rec->position( "double" ), 2 );
    QCOMPARE( rec->position( "bool" ), 3 );
#endif
}

void tst_QSqlRecord::clear()
{
    createTestRecord();

    rec->clear();
    QCOMPARE( (int)rec->count(), 0 );
    QVERIFY( rec->isEmpty() );
#ifdef QT3_SUPPORT
    QVERIFY( rec->fieldPtr( 0 ) == 0 );
    QVERIFY( rec->fieldPtr( "_This should give a warning!_" ) == 0 );
#endif
    QVERIFY( !rec->contains( fields[0]->name() ) );
}

void tst_QSqlRecord::clearValues()
{
    QFETCH( int, ival );
    QFETCH( QString, sval );
    QFETCH( double, dval );
    QFETCH( int, bval );
    delete rec;

    rec = new QSqlRecord();
    rec->append( QSqlField( "string", QVariant::String ) );
    QCOMPARE( rec->field(0).name(), (QString) "string" );
    QVERIFY( !rec->isEmpty() );
    QCOMPARE( (int)rec->count(), 1 );
    rec->append( QSqlField( "int", QVariant::Int ) );
    QCOMPARE( rec->field(1).name(), (QString) "int" );
    QCOMPARE( (int)rec->count(), 2 );
    rec->append( QSqlField( "double", QVariant::Double ) );
    QCOMPARE( rec->field(2).name(), (QString) "double" );
    QCOMPARE( (int)rec->count(), 3 );
    rec->append( QSqlField( "bool", QVariant::Bool ) );
    QCOMPARE( rec->field(3).name(), (QString) "bool" );
    QCOMPARE( (int)rec->count(), 4 );
    QCOMPARE( rec->indexOf( "string" ), 0 );
    QCOMPARE( rec->indexOf( "int" ), 1 );
    QCOMPARE( rec->indexOf( "double" ), 2 );
    QCOMPARE( rec->indexOf( "bool" ), 3 );
#ifdef QT3_SUPPORT
    QCOMPARE( rec->position( "string" ), 0 );
    QCOMPARE( rec->position( "int" ), 1 );
    QCOMPARE( rec->position( "double" ), 2 );
    QCOMPARE( rec->position( "bool" ), 3 );
#endif
}

void tst_QSqlRecord::contains()
{
    createTestRecord();
    for ( int i = 0; i < NUM_FIELDS; ++i )
	QVERIFY( rec->contains( fields[ i ]->name() ) );
    QVERIFY( !rec->contains( "__Harry__" ) );
}

void tst_QSqlRecord::count()
{
    createTestRecord();
    QCOMPARE( (int)rec->count(), NUM_FIELDS );
    rec->remove( 3 );
    QCOMPARE( (int)rec->count(), NUM_FIELDS - 1 );
    rec->clear();
    QCOMPARE( (int)rec->count(), 0 );
    QCOMPARE( (int)QSqlRecord().count(), 0 );
}

void tst_QSqlRecord::field()
{
    createTestRecord();

    int i;
    for ( i = 0; i < NUM_FIELDS; ++i )
	QVERIFY( rec->field( i ) == *fields[ i ] );
#ifdef QT3_SUPPORT
    QVERIFY( rec->fieldPtr( NUM_FIELDS ) == 0 );
#endif

    for ( i = 0; i < NUM_FIELDS; ++i )
	QVERIFY( rec->field( (fields[ i ] )->name() ) == *( fields[ i ] ) );
    QVERIFY( rec->indexOf( "_This should give a warning!_" ) == -1 );
}

void tst_QSqlRecord::fieldName()
{
    createTestRecord();

    for ( int i = 0; i < NUM_FIELDS; ++i )
	QVERIFY( rec->field( (fields[ i ] )->name() ) == *( fields[ i ] ) );
    QVERIFY( rec->fieldName( NUM_FIELDS ).isNull() );
}

void tst_QSqlRecord::insert()
{
    QSqlRecord iRec;
    int i;
    for ( i = 0; i <= 100; ++i ) {
	iRec.insert( i, QSqlField( QString::number( i ), QVariant::Int ) );
    }
    for ( i = 0; i <= 100; ++i ) {
	QCOMPARE( iRec.fieldName( i ), QString::number( i ) );
    }
//    iRec.insert( 505, QSqlField( "Harry", QVariant::Double ) );
//    QCOMPARE( iRec.fieldName( 505 ), (QString)"Harry" );
//    QVERIFY( iRec.field( 505 ).type() == QVariant::Double );

    iRec.insert( 42, QSqlField( "Everything", QVariant::String ) );
    QCOMPARE( iRec.fieldName( 42 ), (QString)"Everything" );
    QVERIFY( iRec.field( 42 ).type() == QVariant::String );
}

void tst_QSqlRecord::isEmpty()
{
    QSqlRecord eRec;
    QVERIFY( eRec.isEmpty() );
    eRec.append( QSqlField( "Harry", QVariant::String ) );
    QVERIFY( !eRec.isEmpty() );
    eRec.remove( 0 );
    QVERIFY( eRec.isEmpty() );
    eRec.insert( 0, QSqlField( "Harry", QVariant::String ) );
    QVERIFY( !eRec.isEmpty() );
    eRec.clear();
    QVERIFY( eRec.isEmpty() );
}

void tst_QSqlRecord::isGenerated()
{
    createTestRecord();

    int i;
    for ( i = 0; i < NUM_FIELDS; ++i )
	QVERIFY( rec->isGenerated( i ) );

    for ( i = 0; i < NUM_FIELDS; ++i )
	QVERIFY( rec->isGenerated( fields[ i ]->name() ) );

    for ( i = 0; i < NUM_FIELDS; ++i ) {
	if ( i % 2 )
	    rec->setGenerated( i, false );
    }
    rec->setGenerated( NUM_FIELDS * 2, false ); // nothing should happen here

    for ( i = 0; i < NUM_FIELDS; ++i ) {
	if ( i % 2 ) {
	    QVERIFY( !rec->isGenerated( i ) );
	} else {
	    QVERIFY( rec->isGenerated( i ) );
        }
    }

    for ( i = 0; i < NUM_FIELDS; ++i )
	if ( i % 2 ) {
	    QVERIFY( !rec->isGenerated( fields[ i ]->name() ) );
	} else {
	    QVERIFY( rec->isGenerated( fields[ i ]->name() ) );
        }

    rec->setGenerated( "_This should give a warning!_",  false ); // nothing should happen here
}

void tst_QSqlRecord::isNull()
{
    createTestRecord();

    int i;
    for ( i = 0; i < NUM_FIELDS; ++i ) {
	QVERIFY( rec->isNull( i ) );
	QVERIFY( rec->isNull( fields[ i ]->name() ) );
    }

    for ( i = 0; i < NUM_FIELDS; ++i ) {
	if ( i % 2 )
	    rec->setNull( i );
    }
    rec->setNull( NUM_FIELDS ); // nothing should happen here

    for ( i = 0; i < NUM_FIELDS; ++i ) {
	if ( i % 2 ) {
	    QVERIFY( rec->isNull( i ) );
	    QVERIFY( rec->isNull( fields[ i ]->name() ) );
        }
    }

    for ( i = 0; i < NUM_FIELDS; ++i ) {
	rec->setNull( fields[ i ]->name() );
    }
    rec->setNull( "_This should give a warning!_" ); // nothing should happen here

    for ( i = 0; i < NUM_FIELDS; ++i ) {
	QVERIFY( rec->isNull( i ) );
	QVERIFY( rec->isNull( fields[ i ]->name() ) );
    }
}

void tst_QSqlRecord::operator_Assign()
{
    createTestRecord();
    int i;
    QSqlRecord buf2, buf3, buf4; // since buffers are implicitely shared, we exaggerate a bit here
    buf2 = *rec;
    buf3 = *rec;
    buf4 = *rec;
    for ( i = 0; i < NUM_FIELDS; ++i ) {
	QVERIFY( buf2.field( i ) == *fields[ i ] );
	QVERIFY( buf3.field( i ) == *( fields[ i ] ) );
	QVERIFY( buf4.field( i ) == *( fields[ i ] ) );
    }
    for ( i = 0; i < NUM_FIELDS; ++i )
	buf3.setNull( i );
    buf3.remove( NUM_FIELDS - 1 );
    QSqlRecord buf5 = buf3;
    for ( i = 0; i < NUM_FIELDS - 1; ++i ) {
	QSqlField fi ( fields[ i ]->name(), fields[ i ]->type() );
	fi.clear();
	QVERIFY( buf5.field( i ) == fi );
	QVERIFY( buf5.isGenerated( i ) );
    }
}

void tst_QSqlRecord::position()
{
    createTestRecord();
    int i;
    for ( i = 0; i < NUM_FIELDS; ++i ) {
	QCOMPARE( rec->indexOf( fields[ i ]->name() ), i );
#ifdef QT3_SUPPORT
	QCOMPARE( rec->position( fields[ i ]->name() ), i );
#endif
    }
}

void tst_QSqlRecord::remove()
{
    createTestRecord();
    int i;
    for ( i = 0; i < NUM_FIELDS; ++i ) {
	rec->setGenerated( i, false );
	QCOMPARE( (int)rec->count(), NUM_FIELDS - i );
	rec->remove( 0 );
	QCOMPARE( (int)rec->count(), NUM_FIELDS - i - 1 );
    }
    rec->remove( NUM_FIELDS * 2 ); // nothing should happen
    for ( i = 0; i < NUM_FIELDS; ++i ) {
	rec->insert( i, QSqlField( fields[ i ]->name(), fields[ i ]->type() ) );
	QVERIFY( rec->isGenerated( i ) );
    }
}

void tst_QSqlRecord::setGenerated()
{
    isGenerated();
}

void tst_QSqlRecord::setNull()
{
    isNull();
}

void tst_QSqlRecord::setValue()
{
    int i;

    delete rec;
    rec = new QSqlRecord();
    rec->append( QSqlField( "string", QVariant::String ) );
    QCOMPARE( rec->field( 0 ).name(), (QString) "string" );
    QVERIFY( !rec->isEmpty() );
    QCOMPARE( (int)rec->count(), 1 );
    rec->append( QSqlField( "int", QVariant::Int ) );
    QCOMPARE( rec->field( 1 ).name(), (QString) "int" );
    QCOMPARE( (int)rec->count(), 2 );
    rec->append( QSqlField( "double", QVariant::Double ) );
    QCOMPARE( rec->field( 2 ).name(), (QString) "double" );
    QCOMPARE( (int)rec->count(), 3 );
    rec->append( QSqlField( "bool", QVariant::Bool ) );
    QCOMPARE( rec->field( 3 ).name(), (QString) "bool" );
    QCOMPARE( (int)rec->count(), 4 );
    QCOMPARE( rec->indexOf( "string" ), 0 );
    QCOMPARE( rec->indexOf( "int" ), 1 );
    QCOMPARE( rec->indexOf( "double" ), 2 );
    QCOMPARE( rec->indexOf( "bool" ), 3 );
#ifdef QT3_SUPPORT
    QCOMPARE( rec->position( "string" ), 0 );
    QCOMPARE( rec->position( "int" ), 1 );
    QCOMPARE( rec->position( "double" ), 2 );
    QCOMPARE( rec->position( "bool" ), 3 );
#endif

    QFETCH( int, ival );
    QFETCH( QString, sval );
    QFETCH( double, dval );
    QFETCH( int, bval );

    for ( i = 0; i < 4; ++i )
	rec->setNull( i );

    rec->setValue( 0, sval );
    rec->setValue( 1, ival );
    rec->setValue( 2, dval );
    rec->setValue( 3, QVariant(bval) );
    QVERIFY( rec->value( 0 ) == sval );
    QVERIFY( rec->value( 1 ) == ival );
    QVERIFY( rec->value( 2 ) == dval );
    QVERIFY( rec->value( 3 ) == QVariant(bval) );
    for ( i = 0; i < 4; ++i )
	QVERIFY( !rec->isNull( i ) );

    QSqlRecord rec2 = *rec;
    QVERIFY( rec2.value( 0 ) == sval );
    QVERIFY( rec2.value( 1 ) == ival );
    QVERIFY( rec2.value( 2 ) == dval );
    QVERIFY( rec2.value( 3 ) == QVariant(bval) );

    rec2.setValue( "string", "__Harry__" );
    QVERIFY( rec2.value( 0 ) == "__Harry__" );

    for ( i = 0; i < 4; ++i )
	QVERIFY( !rec2.isNull( i ) );

    QCOMPARE( rec->value( 0 ).toString(), sval );
    QCOMPARE( rec->value( 1 ).toInt(), ival );
    QCOMPARE( rec->value( 2 ).toDouble(), dval );
    QCOMPARE( rec->value( 3 ), QVariant(bval) );
}

#ifdef QT3_SUPPORT
void tst_QSqlRecord::toString()
{
    createTestRecord();
    QString result;
    QFETCH( QString, prefix );
    QFETCH( QString, sep );
    rec->setGenerated( 1, false );
    for (int i = 0; i < NUM_FIELDS; ++i ) {
	if ( i == 1 )
	    continue;
	if ( prefix.isEmpty() ) {
	    result += fields[ i ]->name();
	} else {
	    result += prefix + '.' + fields[ i ]->name();
	}
	if ( i != NUM_FIELDS - 1 )
	    result += sep + ' ';
    }
    QCOMPARE( rec->toString( prefix, sep ), result );
}

void tst_QSqlRecord::toStringList()
{
    createTestRecord();
    QStringList result;
    QFETCH( QString, prefix );
    rec->setGenerated( 1, false );
    for (int i = 0; i < NUM_FIELDS; ++i ) {
	if ( i == 1 )
	    continue;
	if ( prefix.isEmpty() ) {
	    result << fields[ i ]->name();
	} else {
	    result << ( prefix + '.' + fields[ i ]->name() );
	}
    }
    QCOMPARE(rec->toStringList( prefix ), result);
}

void tst_QSqlRecord::toString_data()
{
    clearValues_data( t );
}

void tst_QSqlRecord::toStringList_data()
{
    clearValues_data( t );
}
#endif // QT3_SUPPORT

void tst_QSqlRecord::value()
{
    // this test is already covered in setValue()
    QSqlRecord rec2;
    rec2.append( QSqlField( "string", QVariant::String ) );
    rec2.setValue( "string", "Harry" );
    QVERIFY( rec2.value( "string" ) == "Harry" );
}

void tst_QSqlRecord::setValue_data()
{
    clearValues_data();
}

void tst_QSqlRecord::clearValues_data()
{
    QTest::addColumn<QString>("prefix");
    QTest::addColumn<QString>("sep");
    QTest::addColumn<int>("ival");
    QTest::addColumn<QString>("sval");
    QTest::addColumn<double>("dval");
    QTest::addColumn<int>("bval");

    QTest::newRow( "data0" ) << QString::fromLatin1("tablename") << QString::fromLatin1(",") << 10
                          << QString::fromLatin1("Trond K.") << 2222.231234441 << 0;
    QTest::newRow( "data1" ) << QString::fromLatin1("mytable") << QString::fromLatin1(".") << 12
                          << QString::fromLatin1("Josten") << 544444444444423232.32334441 << 1;
    QTest::newRow( "data2" ) << QString::fromLatin1("tabby") << QString::fromLatin1("-") << 12
                          << QString::fromLatin1("Odvin") << 899129389283.32334441 << 1;
    QTest::newRow( "data3" ) << QString::fromLatin1("per") << QString::fromLatin1("00") << 12
                          << QString::fromLatin1("Brge") << 29382939182.99999919 << 0;
}

QTEST_MAIN(tst_QSqlRecord)
#include "tst_qsqlrecord.moc"
