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
** contact the sales department at http://qt.nokia.com/contact.
** $QT_END_LICENSE$
**
****************************************************************************/


#ifndef Q_tst_SuiteTest
#define Q_tst_SuiteTest

#include <QtCore/QObject>
#include "../../qxmlquery/TestFundament.h"

/*!
 \class tst_SuiteTest
 \internal
 \since 4.5
 \brief Base class for tst_XmlPatternsXQTS and tst_XmlPatternsXSLTS.
 */
class tst_SuiteTest : public QObject
                    , private TestFundament
{
    Q_OBJECT

protected:
    /**
     * @p isXSLT is @c true if the catalog opened is an
     * XSL-T test suite.
     *
     * @p alwaysRun is @c true if the test should always be run,
     * regardless of if the file runTests exists.
     */
    tst_SuiteTest(const bool isXSLT,
                  const bool alwaysRun = false);

    /**
     * The reason why we pass in a mutable reference and have void as return
     * value instead of simply returning the string, is that we in some
     * implementations use QTestLib's macros such as QVERIFY, which contains
     * return statements. Yay for QTestLib.
     */
    virtual void catalogPath(QString &write) const = 0;

    bool dontRun() const;

private Q_SLOTS:
    void initTestCase();
    void runTestSuite() const;
    void checkTestSuiteResult() const;

private:
    /**
     * An absolute path to the catalog.
     */
    QString         m_catalogPath;
    const QString   m_existingBaseline;
    const QString   m_candidateBaseline;
    const bool      m_abortRun;
    const bool      m_isXSLT;
};

#endif

// vim: et:ts=4:sw=4:sts=4
