/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Linguist of the Qt Toolkit.
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
** In addition, as a special exception, Nokia gives you certain
** additional rights.  These rights are described in the Nokia Qt LGPL
** Exception version 1.1, included in the file LGPL_EXCEPTION.txt in this
** package.
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

#ifndef SOURCECODEVIEW_H
#define SOURCECODEVIEW_H

#include <QDir>
#include <QHash>
#include <QPlainTextEdit>

QT_BEGIN_NAMESPACE

class SourceCodeView : public QPlainTextEdit
{
    Q_OBJECT
public:
    SourceCodeView(QWidget *parent = 0);
    void setSourceContext(const QString &fileName, const int lineNum);

public slots:
    void setActivated(bool activated);

private:
    void showSourceCode(const QString &fileName, const int lineNum);

    bool m_isActive;
    QString m_fileToLoad;
    int m_lineNumToLoad;
    QString m_currentFileName;

    QHash<QString, QString> fileHash;
};

QT_END_NAMESPACE

#endif // SOURCECODEVIEW_H
