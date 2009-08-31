/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Designer of the Qt Toolkit.
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

#include "qwebview_plugin.h"

#include <QtDesigner/QExtensionFactory>
#include <QtDesigner/QExtensionManager>

#include <QtCore/qplugin.h>
#include <QtWebKit/QWebView>

static const char *toolTipC = "QtWebKit Web widget";

QT_BEGIN_NAMESPACE

QWebViewPlugin::QWebViewPlugin(QObject *parent) :
    QObject(parent),
    m_initialized(false)
{
}

QString QWebViewPlugin::name() const
{
    return QLatin1String("QWebView");
}

QString QWebViewPlugin::group() const
{
    return QLatin1String("Display Widgets");
}

QString QWebViewPlugin::toolTip() const
{
    return QString(QLatin1String(toolTipC));
}

QString QWebViewPlugin::whatsThis() const
{
    return QString(QLatin1String(toolTipC));
}

QString QWebViewPlugin::includeFile() const
{
    return QLatin1String("QtWebKit/QWebView");
}

QIcon QWebViewPlugin::icon() const
{
    return QIcon(QLatin1String(":/trolltech/qwebview/images/qwebview.png"));
}

bool QWebViewPlugin::isContainer() const
{
    return false;
}

QWidget *QWebViewPlugin::createWidget(QWidget *parent)
{
    return new QWebView(parent);
}

bool QWebViewPlugin::isInitialized() const
{
    return m_initialized;
}

void QWebViewPlugin::initialize(QDesignerFormEditorInterface * /*core*/)
{
    if (m_initialized)
        return;

    m_initialized = true;
}

QString QWebViewPlugin::domXml() const
{
    return QLatin1String("\
    <ui language=\"c++\">\
        <widget class=\"QWebView\" name=\"webView\">\
            <property name=\"url\">\
                <url>\
                    <string>about:blank</string>\
                </url>\
            </property>\
            <property name=\"geometry\">\
                <rect>\
                    <x>0</x>\
                    <y>0</y>\
                    <width>300</width>\
                    <height>200</height>\
                </rect>\
            </property>\
        </widget>\
    </ui>");
}

Q_EXPORT_PLUGIN2(customwidgetplugin, QWebViewPlugin)

QT_END_NAMESPACE
