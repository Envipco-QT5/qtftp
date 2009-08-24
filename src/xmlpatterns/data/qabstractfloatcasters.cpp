/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtXmlPatterns module of the Qt Toolkit.
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

/*
 * NOTE: This file is included by qabstractfloatcasters_p.h
 * if you need some includes, put them in qabstractfloatcasters_p.h (outside of the namespace)
 */

template <const bool isDouble>
Item NumericToAbstractFloatCaster<isDouble>::castFrom(const Item &from,
                                                           const QExplicitlySharedDataPointer<DynamicContext> &) const
{
    // toDouble() returns same thing than toFloat()
    return toItem(AbstractFloat<isDouble>::fromValue(from.template as<Numeric>()->toDouble()));
}

template <const bool isDouble>
Item StringToAbstractFloatCaster<isDouble>::castFrom(const Item &from,
                                                          const QExplicitlySharedDataPointer<DynamicContext> &) const
{
    return toItem(AbstractFloat<isDouble>::fromLexical(from.stringValue()));
}

template <const bool isDouble>
Item BooleanToAbstractFloatCaster<isDouble>::castFrom(const Item &from,
                                                           const QExplicitlySharedDataPointer<DynamicContext> &context) const
{
    if(from.template as<AtomicValue>()->evaluateEBV(context))
        return isDouble ? toItem(CommonValues::DoubleOne) : toItem(CommonValues::FloatOne);
    else
        return isDouble ? toItem(CommonValues::DoubleZero) : toItem(CommonValues::FloatZero);
}

