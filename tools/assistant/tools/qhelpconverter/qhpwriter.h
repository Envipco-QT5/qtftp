/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Assistant of the Qt Toolkit.
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

#ifndef QHPWRITER_H
#define QHPWRITER_H

#include <QtXml/QXmlStreamWriter>
#include "filterpage.h"

QT_BEGIN_NAMESPACE

class AdpReader;

class QhpWriter : public QXmlStreamWriter
{
public:
    enum IdentifierPrefix {SkipAll, FilePrefix, GlobalPrefix};
    QhpWriter(const QString &namespaceName,
        const QString &virtualFolder);
    void setAdpReader(AdpReader *reader);
    void setFilterAttributes(const QStringList &attributes);
    void setCustomFilters(const QList<CustomFilter> filters);
    void setFiles(const QStringList &files);
    void generateIdentifiers(IdentifierPrefix prefix,
        const QString prefixString = QString()); 
    bool writeFile(const QString &fileName);

private:
    void writeCustomFilters();
    void writeFilterSection();
    void writeToc();
    void writeKeywords();
    void writeFiles();

    QString m_namespaceName;
    QString m_virtualFolder;
    AdpReader *m_adpReader;
    QStringList m_filterAttributes;
    QList<CustomFilter> m_customFilters;
    QStringList m_files;
    IdentifierPrefix m_prefix;
    QString m_prefixString;
};

QT_END_NAMESPACE

#endif
