/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Designer of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
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
** contact the sales department at http://www.qtsoftware.com/contact.
** $QT_END_LICENSE$
**
****************************************************************************/

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of Qt Designer.  This header
// file may change from version to version without notice, or even be removed.
//
// We mean it.
//

#ifndef SHARED_EXTENSIONFACTORY_H
#define SHARED_EXTENSIONFACTORY_H

#include <QtDesigner/default_extensionfactory.h>
#include <QtDesigner/QExtensionManager>

QT_BEGIN_NAMESPACE

namespace qdesigner_internal {

// Extension factory for registering an extension for an object type.
template <class ExtensionInterface, class Object, class Extension>
class ExtensionFactory: public QExtensionFactory
{
public:
    explicit ExtensionFactory(const QString &iid, QExtensionManager *parent = 0);

    // Convenience for registering the extension. Do not use for derived classes.
    static void registerExtension(QExtensionManager *mgr, const QString &iid);

protected:
    virtual QObject *createExtension(QObject *qObject, const QString &iid, QObject *parent) const;

private:
    // Can be overwritten to perform checks on the object.
    // Default does a qobject_cast to the desired class.
    virtual Object *checkObject(QObject *qObject) const;

    const QString m_iid;
};

template <class ExtensionInterface, class Object, class Extension>
ExtensionFactory<ExtensionInterface, Object, Extension>::ExtensionFactory(const QString &iid, QExtensionManager *parent) :
    QExtensionFactory(parent),
    m_iid(iid)
{
}

template <class ExtensionInterface, class Object, class Extension>
Object *ExtensionFactory<ExtensionInterface, Object, Extension>::checkObject(QObject *qObject) const
{
    return qobject_cast<Object*>(qObject);
}

template <class ExtensionInterface, class Object, class Extension>
QObject *ExtensionFactory<ExtensionInterface, Object, Extension>::createExtension(QObject *qObject, const QString &iid, QObject *parent) const
{
    if (iid != m_iid)
        return 0;

    Object *object = checkObject(qObject);
    if (!object)
        return 0;

    return new Extension(object, parent);
}

template <class ExtensionInterface, class Object, class Extension>
void ExtensionFactory<ExtensionInterface, Object, Extension>::registerExtension(QExtensionManager *mgr, const QString &iid)
{
    ExtensionFactory *factory = new ExtensionFactory(iid, mgr);
    mgr->registerExtensions(factory, iid);
}
}  // namespace qdesigner_internal

QT_END_NAMESPACE

#endif // SHARED_EXTENSIONFACTORY_H
