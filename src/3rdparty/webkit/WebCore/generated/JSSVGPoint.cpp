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
#include "JSSVGPoint.h"

#include <wtf/GetPtr.h>

#include "JSSVGMatrix.h"
#include "JSSVGPoint.h"

#include <runtime/Error.h>
#include <runtime/JSNumberCell.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGPoint)

/* Hash table */

static const HashTableValue JSSVGPointTableValues[3] =
{
    { "x", DontDelete, (intptr_t)jsSVGPointX, (intptr_t)setJSSVGPointX },
    { "y", DontDelete, (intptr_t)jsSVGPointY, (intptr_t)setJSSVGPointY },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGPointTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 1, JSSVGPointTableValues, 0 };
#else
    { 4, 3, JSSVGPointTableValues, 0 };
#endif

/* Hash table for prototype */

static const HashTableValue JSSVGPointPrototypeTableValues[2] =
{
    { "matrixTransform", DontDelete|Function, (intptr_t)jsSVGPointPrototypeFunctionMatrixTransform, (intptr_t)1 },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGPointPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGPointPrototypeTableValues, 0 };
#else
    { 2, 1, JSSVGPointPrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGPointPrototype::s_info = { "SVGPointPrototype", 0, &JSSVGPointPrototypeTable, 0 };

JSObject* JSSVGPointPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSSVGPoint>(exec, globalObject);
}

bool JSSVGPointPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticFunctionSlot<JSObject>(exec, &JSSVGPointPrototypeTable, this, propertyName, slot);
}

const ClassInfo JSSVGPoint::s_info = { "SVGPoint", 0, &JSSVGPointTable, 0 };

JSSVGPoint::JSSVGPoint(PassRefPtr<Structure> structure, PassRefPtr<JSSVGPODTypeWrapper<FloatPoint> > impl, SVGElement* context)
    : DOMObject(structure)
    , m_context(context)
    , m_impl(impl)
{
}

JSSVGPoint::~JSSVGPoint()
{
    forgetDOMObject(*Heap::heap(this)->globalData(), m_impl.get());

}

JSObject* JSSVGPoint::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSSVGPointPrototype(JSSVGPointPrototype::createStructure(globalObject->objectPrototype()));
}

bool JSSVGPoint::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGPoint, Base>(exec, &JSSVGPointTable, this, propertyName, slot);
}

JSValuePtr jsSVGPointX(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    FloatPoint imp(*static_cast<JSSVGPoint*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp.x());
}

JSValuePtr jsSVGPointY(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    FloatPoint imp(*static_cast<JSSVGPoint*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp.y());
}

void JSSVGPoint::put(ExecState* exec, const Identifier& propertyName, JSValuePtr value, PutPropertySlot& slot)
{
    lookupPut<JSSVGPoint, Base>(exec, propertyName, value, &JSSVGPointTable, this, slot);
}

void setJSSVGPointX(ExecState* exec, JSObject* thisObject, JSValuePtr value)
{
    FloatPoint imp(*static_cast<JSSVGPoint*>(thisObject)->impl());
    imp.setX(value->toFloat(exec));
        static_cast<JSSVGPoint*>(thisObject)->impl()->commitChange(imp, static_cast<JSSVGPoint*>(thisObject)->context());
}

void setJSSVGPointY(ExecState* exec, JSObject* thisObject, JSValuePtr value)
{
    FloatPoint imp(*static_cast<JSSVGPoint*>(thisObject)->impl());
    imp.setY(value->toFloat(exec));
        static_cast<JSSVGPoint*>(thisObject)->impl()->commitChange(imp, static_cast<JSSVGPoint*>(thisObject)->context());
}

JSValuePtr jsSVGPointPrototypeFunctionMatrixTransform(ExecState* exec, JSObject*, JSValuePtr thisValue, const ArgList& args)
{
    if (!thisValue->isObject(&JSSVGPoint::s_info))
        return throwError(exec, TypeError);
    JSSVGPoint* castedThisObj = static_cast<JSSVGPoint*>(asObject(thisValue));
    JSSVGPODTypeWrapper<FloatPoint>* wrapper = castedThisObj->impl();
    FloatPoint imp(*wrapper);
    TransformationMatrix matrix = toSVGMatrix(args.at(exec, 0));


    JSC::JSValuePtr result = toJS(exec, JSSVGStaticPODTypeWrapper<FloatPoint>::create(imp.matrixTransform(matrix)).get(), castedThisObj->context());
    wrapper->commitChange(imp, castedThisObj->context());
    return result;
}

JSC::JSValuePtr toJS(JSC::ExecState* exec, JSSVGPODTypeWrapper<FloatPoint>* object, SVGElement* context)
{
    return getDOMObjectWrapper<JSSVGPoint, JSSVGPODTypeWrapper<FloatPoint> >(exec, object, context);
}
FloatPoint toSVGPoint(JSC::JSValuePtr value)
{
    return value->isObject(&JSSVGPoint::s_info) ? (FloatPoint) *static_cast<JSSVGPoint*>(asObject(value))->impl() : FloatPoint();
}

}

#endif // ENABLE(SVG)
