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
#include "JSSVGPathSegLinetoAbs.h"

#include <wtf/GetPtr.h>

#include "SVGPathSegLineto.h"

#include <runtime/JSNumberCell.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGPathSegLinetoAbs)

/* Hash table */

static const HashTableValue JSSVGPathSegLinetoAbsTableValues[3] =
{
    { "x", DontDelete, (intptr_t)jsSVGPathSegLinetoAbsX, (intptr_t)setJSSVGPathSegLinetoAbsX },
    { "y", DontDelete, (intptr_t)jsSVGPathSegLinetoAbsY, (intptr_t)setJSSVGPathSegLinetoAbsY },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGPathSegLinetoAbsTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 1, JSSVGPathSegLinetoAbsTableValues, 0 };
#else
    { 4, 3, JSSVGPathSegLinetoAbsTableValues, 0 };
#endif

/* Hash table for prototype */

static const HashTableValue JSSVGPathSegLinetoAbsPrototypeTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGPathSegLinetoAbsPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGPathSegLinetoAbsPrototypeTableValues, 0 };
#else
    { 1, 0, JSSVGPathSegLinetoAbsPrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGPathSegLinetoAbsPrototype::s_info = { "SVGPathSegLinetoAbsPrototype", 0, &JSSVGPathSegLinetoAbsPrototypeTable, 0 };

JSObject* JSSVGPathSegLinetoAbsPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSSVGPathSegLinetoAbs>(exec, globalObject);
}

const ClassInfo JSSVGPathSegLinetoAbs::s_info = { "SVGPathSegLinetoAbs", &JSSVGPathSeg::s_info, &JSSVGPathSegLinetoAbsTable, 0 };

JSSVGPathSegLinetoAbs::JSSVGPathSegLinetoAbs(PassRefPtr<Structure> structure, PassRefPtr<SVGPathSegLinetoAbs> impl, SVGElement* context)
    : JSSVGPathSeg(structure, impl, context)
{
}

JSObject* JSSVGPathSegLinetoAbs::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSSVGPathSegLinetoAbsPrototype(JSSVGPathSegLinetoAbsPrototype::createStructure(JSSVGPathSegPrototype::self(exec, globalObject)));
}

bool JSSVGPathSegLinetoAbs::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGPathSegLinetoAbs, Base>(exec, &JSSVGPathSegLinetoAbsTable, this, propertyName, slot);
}

JSValuePtr jsSVGPathSegLinetoAbsX(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGPathSegLinetoAbs* imp = static_cast<SVGPathSegLinetoAbs*>(static_cast<JSSVGPathSegLinetoAbs*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->x());
}

JSValuePtr jsSVGPathSegLinetoAbsY(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGPathSegLinetoAbs* imp = static_cast<SVGPathSegLinetoAbs*>(static_cast<JSSVGPathSegLinetoAbs*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->y());
}

void JSSVGPathSegLinetoAbs::put(ExecState* exec, const Identifier& propertyName, JSValuePtr value, PutPropertySlot& slot)
{
    lookupPut<JSSVGPathSegLinetoAbs, Base>(exec, propertyName, value, &JSSVGPathSegLinetoAbsTable, this, slot);
}

void setJSSVGPathSegLinetoAbsX(ExecState* exec, JSObject* thisObject, JSValuePtr value)
{
    SVGPathSegLinetoAbs* imp = static_cast<SVGPathSegLinetoAbs*>(static_cast<JSSVGPathSegLinetoAbs*>(thisObject)->impl());
    imp->setX(value->toFloat(exec));
    if (static_cast<JSSVGPathSegLinetoAbs*>(thisObject)->context())
        static_cast<JSSVGPathSegLinetoAbs*>(thisObject)->context()->svgAttributeChanged(static_cast<JSSVGPathSegLinetoAbs*>(thisObject)->impl()->associatedAttributeName());
}

void setJSSVGPathSegLinetoAbsY(ExecState* exec, JSObject* thisObject, JSValuePtr value)
{
    SVGPathSegLinetoAbs* imp = static_cast<SVGPathSegLinetoAbs*>(static_cast<JSSVGPathSegLinetoAbs*>(thisObject)->impl());
    imp->setY(value->toFloat(exec));
    if (static_cast<JSSVGPathSegLinetoAbs*>(thisObject)->context())
        static_cast<JSSVGPathSegLinetoAbs*>(thisObject)->context()->svgAttributeChanged(static_cast<JSSVGPathSegLinetoAbs*>(thisObject)->impl()->associatedAttributeName());
}


}

#endif // ENABLE(SVG)
