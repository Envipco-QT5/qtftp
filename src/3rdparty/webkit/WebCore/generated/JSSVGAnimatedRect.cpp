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
#include "JSSVGAnimatedRect.h"

#include <wtf/GetPtr.h>

#include "FloatRect.h"
#include "JSSVGRect.h"


using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGAnimatedRect)

/* Hash table */

static const HashTableValue JSSVGAnimatedRectTableValues[3] =
{
    { "baseVal", DontDelete|ReadOnly, (intptr_t)jsSVGAnimatedRectBaseVal, (intptr_t)0 },
    { "animVal", DontDelete|ReadOnly, (intptr_t)jsSVGAnimatedRectAnimVal, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGAnimatedRectTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 1, JSSVGAnimatedRectTableValues, 0 };
#else
    { 4, 3, JSSVGAnimatedRectTableValues, 0 };
#endif

/* Hash table for prototype */

static const HashTableValue JSSVGAnimatedRectPrototypeTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGAnimatedRectPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGAnimatedRectPrototypeTableValues, 0 };
#else
    { 1, 0, JSSVGAnimatedRectPrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGAnimatedRectPrototype::s_info = { "SVGAnimatedRectPrototype", 0, &JSSVGAnimatedRectPrototypeTable, 0 };

JSObject* JSSVGAnimatedRectPrototype::self(ExecState* exec)
{
    return getDOMPrototype<JSSVGAnimatedRect>(exec);
}

const ClassInfo JSSVGAnimatedRect::s_info = { "SVGAnimatedRect", 0, &JSSVGAnimatedRectTable, 0 };

JSSVGAnimatedRect::JSSVGAnimatedRect(PassRefPtr<Structure> structure, PassRefPtr<SVGAnimatedRect> impl, SVGElement* context)
    : DOMObject(structure)
    , m_context(context)
    , m_impl(impl)
{
}

JSSVGAnimatedRect::~JSSVGAnimatedRect()
{
    forgetDOMObject(*Heap::heap(this)->globalData(), m_impl.get());

}

JSObject* JSSVGAnimatedRect::createPrototype(ExecState* exec)
{
    return new (exec) JSSVGAnimatedRectPrototype(JSSVGAnimatedRectPrototype::createStructure(exec->lexicalGlobalObject()->objectPrototype()));
}

bool JSSVGAnimatedRect::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGAnimatedRect, Base>(exec, &JSSVGAnimatedRectTable, this, propertyName, slot);
}

JSValuePtr jsSVGAnimatedRectBaseVal(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGAnimatedRect* imp = static_cast<SVGAnimatedRect*>(static_cast<JSSVGAnimatedRect*>(asObject(slot.slotBase()))->impl());
    return toJS(exec, JSSVGDynamicPODTypeWrapperCache<FloatRect, SVGAnimatedRect>::lookupOrCreateWrapper(imp, &SVGAnimatedRect::baseVal, &SVGAnimatedRect::setBaseVal).get(), static_cast<JSSVGAnimatedRect*>(asObject(slot.slotBase()))->context());
}

JSValuePtr jsSVGAnimatedRectAnimVal(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGAnimatedRect* imp = static_cast<SVGAnimatedRect*>(static_cast<JSSVGAnimatedRect*>(asObject(slot.slotBase()))->impl());
    return toJS(exec, JSSVGDynamicPODTypeWrapperCache<FloatRect, SVGAnimatedRect>::lookupOrCreateWrapper(imp, &SVGAnimatedRect::animVal, &SVGAnimatedRect::setAnimVal).get(), static_cast<JSSVGAnimatedRect*>(asObject(slot.slotBase()))->context());
}

JSC::JSValuePtr toJS(JSC::ExecState* exec, SVGAnimatedRect* object, SVGElement* context)
{
    return getDOMObjectWrapper<JSSVGAnimatedRect>(exec, object, context);
}
SVGAnimatedRect* toSVGAnimatedRect(JSC::JSValuePtr value)
{
    return value->isObject(&JSSVGAnimatedRect::s_info) ? static_cast<JSSVGAnimatedRect*>(asObject(value))->impl() : 0;
}

}

#endif // ENABLE(SVG)
