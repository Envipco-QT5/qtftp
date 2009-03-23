/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"


#if ENABLE(SVG)

#include "SVGElement.h"
#include "JSSVGPathSegCurvetoQuadraticSmoothAbs.h"

#include <wtf/GetPtr.h>

#include "SVGPathSegCurvetoQuadraticSmooth.h"

#include <runtime/JSNumberCell.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGPathSegCurvetoQuadraticSmoothAbs)

/* Hash table */

static const HashTableValue JSSVGPathSegCurvetoQuadraticSmoothAbsTableValues[3] =
{
    { "x", DontDelete, (intptr_t)jsSVGPathSegCurvetoQuadraticSmoothAbsX, (intptr_t)setJSSVGPathSegCurvetoQuadraticSmoothAbsX },
    { "y", DontDelete, (intptr_t)jsSVGPathSegCurvetoQuadraticSmoothAbsY, (intptr_t)setJSSVGPathSegCurvetoQuadraticSmoothAbsY },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGPathSegCurvetoQuadraticSmoothAbsTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 1, JSSVGPathSegCurvetoQuadraticSmoothAbsTableValues, 0 };
#else
    { 4, 3, JSSVGPathSegCurvetoQuadraticSmoothAbsTableValues, 0 };
#endif

/* Hash table for prototype */

static const HashTableValue JSSVGPathSegCurvetoQuadraticSmoothAbsPrototypeTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGPathSegCurvetoQuadraticSmoothAbsPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGPathSegCurvetoQuadraticSmoothAbsPrototypeTableValues, 0 };
#else
    { 1, 0, JSSVGPathSegCurvetoQuadraticSmoothAbsPrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGPathSegCurvetoQuadraticSmoothAbsPrototype::s_info = { "SVGPathSegCurvetoQuadraticSmoothAbsPrototype", 0, &JSSVGPathSegCurvetoQuadraticSmoothAbsPrototypeTable, 0 };

JSObject* JSSVGPathSegCurvetoQuadraticSmoothAbsPrototype::self(ExecState* exec)
{
    return getDOMPrototype<JSSVGPathSegCurvetoQuadraticSmoothAbs>(exec);
}

const ClassInfo JSSVGPathSegCurvetoQuadraticSmoothAbs::s_info = { "SVGPathSegCurvetoQuadraticSmoothAbs", &JSSVGPathSeg::s_info, &JSSVGPathSegCurvetoQuadraticSmoothAbsTable, 0 };

JSSVGPathSegCurvetoQuadraticSmoothAbs::JSSVGPathSegCurvetoQuadraticSmoothAbs(PassRefPtr<Structure> structure, PassRefPtr<SVGPathSegCurvetoQuadraticSmoothAbs> impl, SVGElement* context)
    : JSSVGPathSeg(structure, impl, context)
{
}

JSObject* JSSVGPathSegCurvetoQuadraticSmoothAbs::createPrototype(ExecState* exec)
{
    return new (exec) JSSVGPathSegCurvetoQuadraticSmoothAbsPrototype(JSSVGPathSegCurvetoQuadraticSmoothAbsPrototype::createStructure(JSSVGPathSegPrototype::self(exec)));
}

bool JSSVGPathSegCurvetoQuadraticSmoothAbs::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGPathSegCurvetoQuadraticSmoothAbs, Base>(exec, &JSSVGPathSegCurvetoQuadraticSmoothAbsTable, this, propertyName, slot);
}

JSValuePtr jsSVGPathSegCurvetoQuadraticSmoothAbsX(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGPathSegCurvetoQuadraticSmoothAbs* imp = static_cast<SVGPathSegCurvetoQuadraticSmoothAbs*>(static_cast<JSSVGPathSegCurvetoQuadraticSmoothAbs*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->x());
}

JSValuePtr jsSVGPathSegCurvetoQuadraticSmoothAbsY(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGPathSegCurvetoQuadraticSmoothAbs* imp = static_cast<SVGPathSegCurvetoQuadraticSmoothAbs*>(static_cast<JSSVGPathSegCurvetoQuadraticSmoothAbs*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->y());
}

void JSSVGPathSegCurvetoQuadraticSmoothAbs::put(ExecState* exec, const Identifier& propertyName, JSValuePtr value, PutPropertySlot& slot)
{
    lookupPut<JSSVGPathSegCurvetoQuadraticSmoothAbs, Base>(exec, propertyName, value, &JSSVGPathSegCurvetoQuadraticSmoothAbsTable, this, slot);
}

void setJSSVGPathSegCurvetoQuadraticSmoothAbsX(ExecState* exec, JSObject* thisObject, JSValuePtr value)
{
    SVGPathSegCurvetoQuadraticSmoothAbs* imp = static_cast<SVGPathSegCurvetoQuadraticSmoothAbs*>(static_cast<JSSVGPathSegCurvetoQuadraticSmoothAbs*>(thisObject)->impl());
    imp->setX(value->toFloat(exec));
    if (static_cast<JSSVGPathSegCurvetoQuadraticSmoothAbs*>(thisObject)->context())
        static_cast<JSSVGPathSegCurvetoQuadraticSmoothAbs*>(thisObject)->context()->svgAttributeChanged(static_cast<JSSVGPathSegCurvetoQuadraticSmoothAbs*>(thisObject)->impl()->associatedAttributeName());
}

void setJSSVGPathSegCurvetoQuadraticSmoothAbsY(ExecState* exec, JSObject* thisObject, JSValuePtr value)
{
    SVGPathSegCurvetoQuadraticSmoothAbs* imp = static_cast<SVGPathSegCurvetoQuadraticSmoothAbs*>(static_cast<JSSVGPathSegCurvetoQuadraticSmoothAbs*>(thisObject)->impl());
    imp->setY(value->toFloat(exec));
    if (static_cast<JSSVGPathSegCurvetoQuadraticSmoothAbs*>(thisObject)->context())
        static_cast<JSSVGPathSegCurvetoQuadraticSmoothAbs*>(thisObject)->context()->svgAttributeChanged(static_cast<JSSVGPathSegCurvetoQuadraticSmoothAbs*>(thisObject)->impl()->associatedAttributeName());
}


}

#endif // ENABLE(SVG)
