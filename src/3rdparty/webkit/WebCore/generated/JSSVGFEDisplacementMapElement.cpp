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


#if ENABLE(SVG) && ENABLE(SVG_FILTERS)

#include "SVGElement.h"
#include "JSSVGFEDisplacementMapElement.h"

#include <wtf/GetPtr.h>

#include "CSSMutableStyleDeclaration.h"
#include "CSSStyleDeclaration.h"
#include "CSSValue.h"
#include "JSCSSStyleDeclaration.h"
#include "JSCSSValue.h"
#include "JSSVGAnimatedEnumeration.h"
#include "JSSVGAnimatedLength.h"
#include "JSSVGAnimatedNumber.h"
#include "JSSVGAnimatedString.h"
#include "SVGFEDisplacementMapElement.h"

#include <runtime/Error.h>
#include <runtime/JSNumberCell.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGFEDisplacementMapElement)

/* Hash table */

static const HashTableValue JSSVGFEDisplacementMapElementTableValues[14] =
{
    { "in1", DontDelete|ReadOnly, (intptr_t)jsSVGFEDisplacementMapElementIn1, (intptr_t)0 },
    { "in2", DontDelete|ReadOnly, (intptr_t)jsSVGFEDisplacementMapElementIn2, (intptr_t)0 },
    { "scale", DontDelete|ReadOnly, (intptr_t)jsSVGFEDisplacementMapElementScale, (intptr_t)0 },
    { "xChannelSelector", DontDelete|ReadOnly, (intptr_t)jsSVGFEDisplacementMapElementXChannelSelector, (intptr_t)0 },
    { "yChannelSelector", DontDelete|ReadOnly, (intptr_t)jsSVGFEDisplacementMapElementYChannelSelector, (intptr_t)0 },
    { "x", DontDelete|ReadOnly, (intptr_t)jsSVGFEDisplacementMapElementX, (intptr_t)0 },
    { "y", DontDelete|ReadOnly, (intptr_t)jsSVGFEDisplacementMapElementY, (intptr_t)0 },
    { "width", DontDelete|ReadOnly, (intptr_t)jsSVGFEDisplacementMapElementWidth, (intptr_t)0 },
    { "height", DontDelete|ReadOnly, (intptr_t)jsSVGFEDisplacementMapElementHeight, (intptr_t)0 },
    { "result", DontDelete|ReadOnly, (intptr_t)jsSVGFEDisplacementMapElementResult, (intptr_t)0 },
    { "className", DontDelete|ReadOnly, (intptr_t)jsSVGFEDisplacementMapElementClassName, (intptr_t)0 },
    { "style", DontDelete|ReadOnly, (intptr_t)jsSVGFEDisplacementMapElementStyle, (intptr_t)0 },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsSVGFEDisplacementMapElementConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGFEDisplacementMapElementTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 255, JSSVGFEDisplacementMapElementTableValues, 0 };
#else
    { 36, 31, JSSVGFEDisplacementMapElementTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSSVGFEDisplacementMapElementConstructorTableValues[6] =
{
    { "SVG_CHANNEL_UNKNOWN", DontDelete|ReadOnly, (intptr_t)jsSVGFEDisplacementMapElementSVG_CHANNEL_UNKNOWN, (intptr_t)0 },
    { "SVG_CHANNEL_R", DontDelete|ReadOnly, (intptr_t)jsSVGFEDisplacementMapElementSVG_CHANNEL_R, (intptr_t)0 },
    { "SVG_CHANNEL_G", DontDelete|ReadOnly, (intptr_t)jsSVGFEDisplacementMapElementSVG_CHANNEL_G, (intptr_t)0 },
    { "SVG_CHANNEL_B", DontDelete|ReadOnly, (intptr_t)jsSVGFEDisplacementMapElementSVG_CHANNEL_B, (intptr_t)0 },
    { "SVG_CHANNEL_A", DontDelete|ReadOnly, (intptr_t)jsSVGFEDisplacementMapElementSVG_CHANNEL_A, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGFEDisplacementMapElementConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 15, JSSVGFEDisplacementMapElementConstructorTableValues, 0 };
#else
    { 16, 15, JSSVGFEDisplacementMapElementConstructorTableValues, 0 };
#endif

class JSSVGFEDisplacementMapElementConstructor : public DOMObject {
public:
    JSSVGFEDisplacementMapElementConstructor(ExecState* exec)
        : DOMObject(JSSVGFEDisplacementMapElementConstructor::createStructure(exec->lexicalGlobalObject()->objectPrototype()))
    {
        putDirect(exec->propertyNames().prototype, JSSVGFEDisplacementMapElementPrototype::self(exec), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValuePtr proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, ImplementsHasInstance)); 
    }
};

const ClassInfo JSSVGFEDisplacementMapElementConstructor::s_info = { "SVGFEDisplacementMapElementConstructor", 0, &JSSVGFEDisplacementMapElementConstructorTable, 0 };

bool JSSVGFEDisplacementMapElementConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGFEDisplacementMapElementConstructor, DOMObject>(exec, &JSSVGFEDisplacementMapElementConstructorTable, this, propertyName, slot);
}

/* Hash table for prototype */

static const HashTableValue JSSVGFEDisplacementMapElementPrototypeTableValues[7] =
{
    { "SVG_CHANNEL_UNKNOWN", DontDelete|ReadOnly, (intptr_t)jsSVGFEDisplacementMapElementSVG_CHANNEL_UNKNOWN, (intptr_t)0 },
    { "SVG_CHANNEL_R", DontDelete|ReadOnly, (intptr_t)jsSVGFEDisplacementMapElementSVG_CHANNEL_R, (intptr_t)0 },
    { "SVG_CHANNEL_G", DontDelete|ReadOnly, (intptr_t)jsSVGFEDisplacementMapElementSVG_CHANNEL_G, (intptr_t)0 },
    { "SVG_CHANNEL_B", DontDelete|ReadOnly, (intptr_t)jsSVGFEDisplacementMapElementSVG_CHANNEL_B, (intptr_t)0 },
    { "SVG_CHANNEL_A", DontDelete|ReadOnly, (intptr_t)jsSVGFEDisplacementMapElementSVG_CHANNEL_A, (intptr_t)0 },
    { "getPresentationAttribute", DontDelete|Function, (intptr_t)jsSVGFEDisplacementMapElementPrototypeFunctionGetPresentationAttribute, (intptr_t)1 },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGFEDisplacementMapElementPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 15, JSSVGFEDisplacementMapElementPrototypeTableValues, 0 };
#else
    { 16, 15, JSSVGFEDisplacementMapElementPrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGFEDisplacementMapElementPrototype::s_info = { "SVGFEDisplacementMapElementPrototype", 0, &JSSVGFEDisplacementMapElementPrototypeTable, 0 };

JSObject* JSSVGFEDisplacementMapElementPrototype::self(ExecState* exec)
{
    return getDOMPrototype<JSSVGFEDisplacementMapElement>(exec);
}

bool JSSVGFEDisplacementMapElementPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticPropertySlot<JSSVGFEDisplacementMapElementPrototype, JSObject>(exec, &JSSVGFEDisplacementMapElementPrototypeTable, this, propertyName, slot);
}

const ClassInfo JSSVGFEDisplacementMapElement::s_info = { "SVGFEDisplacementMapElement", &JSSVGElement::s_info, &JSSVGFEDisplacementMapElementTable, 0 };

JSSVGFEDisplacementMapElement::JSSVGFEDisplacementMapElement(PassRefPtr<Structure> structure, PassRefPtr<SVGFEDisplacementMapElement> impl)
    : JSSVGElement(structure, impl)
{
}

JSObject* JSSVGFEDisplacementMapElement::createPrototype(ExecState* exec)
{
    return new (exec) JSSVGFEDisplacementMapElementPrototype(JSSVGFEDisplacementMapElementPrototype::createStructure(JSSVGElementPrototype::self(exec)));
}

bool JSSVGFEDisplacementMapElement::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGFEDisplacementMapElement, Base>(exec, &JSSVGFEDisplacementMapElementTable, this, propertyName, slot);
}

JSValuePtr jsSVGFEDisplacementMapElementIn1(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGFEDisplacementMapElement* imp = static_cast<SVGFEDisplacementMapElement*>(static_cast<JSSVGFEDisplacementMapElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedString> obj = imp->in1Animated();
    return toJS(exec, obj.get(), imp);
}

JSValuePtr jsSVGFEDisplacementMapElementIn2(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGFEDisplacementMapElement* imp = static_cast<SVGFEDisplacementMapElement*>(static_cast<JSSVGFEDisplacementMapElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedString> obj = imp->in2Animated();
    return toJS(exec, obj.get(), imp);
}

JSValuePtr jsSVGFEDisplacementMapElementScale(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGFEDisplacementMapElement* imp = static_cast<SVGFEDisplacementMapElement*>(static_cast<JSSVGFEDisplacementMapElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedNumber> obj = imp->scaleAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValuePtr jsSVGFEDisplacementMapElementXChannelSelector(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGFEDisplacementMapElement* imp = static_cast<SVGFEDisplacementMapElement*>(static_cast<JSSVGFEDisplacementMapElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedEnumeration> obj = imp->xChannelSelectorAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValuePtr jsSVGFEDisplacementMapElementYChannelSelector(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGFEDisplacementMapElement* imp = static_cast<SVGFEDisplacementMapElement*>(static_cast<JSSVGFEDisplacementMapElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedEnumeration> obj = imp->yChannelSelectorAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValuePtr jsSVGFEDisplacementMapElementX(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGFEDisplacementMapElement* imp = static_cast<SVGFEDisplacementMapElement*>(static_cast<JSSVGFEDisplacementMapElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedLength> obj = imp->xAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValuePtr jsSVGFEDisplacementMapElementY(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGFEDisplacementMapElement* imp = static_cast<SVGFEDisplacementMapElement*>(static_cast<JSSVGFEDisplacementMapElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedLength> obj = imp->yAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValuePtr jsSVGFEDisplacementMapElementWidth(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGFEDisplacementMapElement* imp = static_cast<SVGFEDisplacementMapElement*>(static_cast<JSSVGFEDisplacementMapElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedLength> obj = imp->widthAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValuePtr jsSVGFEDisplacementMapElementHeight(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGFEDisplacementMapElement* imp = static_cast<SVGFEDisplacementMapElement*>(static_cast<JSSVGFEDisplacementMapElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedLength> obj = imp->heightAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValuePtr jsSVGFEDisplacementMapElementResult(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGFEDisplacementMapElement* imp = static_cast<SVGFEDisplacementMapElement*>(static_cast<JSSVGFEDisplacementMapElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedString> obj = imp->resultAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValuePtr jsSVGFEDisplacementMapElementClassName(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGFEDisplacementMapElement* imp = static_cast<SVGFEDisplacementMapElement*>(static_cast<JSSVGFEDisplacementMapElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedString> obj = imp->classNameAnimated();
    return toJS(exec, obj.get(), imp);
}

JSValuePtr jsSVGFEDisplacementMapElementStyle(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGFEDisplacementMapElement* imp = static_cast<SVGFEDisplacementMapElement*>(static_cast<JSSVGFEDisplacementMapElement*>(asObject(slot.slotBase()))->impl());
    return toJS(exec, WTF::getPtr(imp->style()));
}

JSValuePtr jsSVGFEDisplacementMapElementConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    return static_cast<JSSVGFEDisplacementMapElement*>(asObject(slot.slotBase()))->getConstructor(exec);
}
JSValuePtr JSSVGFEDisplacementMapElement::getConstructor(ExecState* exec)
{
    return getDOMConstructor<JSSVGFEDisplacementMapElementConstructor>(exec);
}

JSValuePtr jsSVGFEDisplacementMapElementPrototypeFunctionGetPresentationAttribute(ExecState* exec, JSObject*, JSValuePtr thisValue, const ArgList& args)
{
    if (!thisValue->isObject(&JSSVGFEDisplacementMapElement::s_info))
        return throwError(exec, TypeError);
    JSSVGFEDisplacementMapElement* castedThisObj = static_cast<JSSVGFEDisplacementMapElement*>(asObject(thisValue));
    SVGFEDisplacementMapElement* imp = static_cast<SVGFEDisplacementMapElement*>(castedThisObj->impl());
    const UString& name = args.at(exec, 0)->toString(exec);


    JSC::JSValuePtr result = toJS(exec, WTF::getPtr(imp->getPresentationAttribute(name)));
    return result;
}

// Constant getters

JSValuePtr jsSVGFEDisplacementMapElementSVG_CHANNEL_UNKNOWN(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(0));
}

JSValuePtr jsSVGFEDisplacementMapElementSVG_CHANNEL_R(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(1));
}

JSValuePtr jsSVGFEDisplacementMapElementSVG_CHANNEL_G(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(2));
}

JSValuePtr jsSVGFEDisplacementMapElementSVG_CHANNEL_B(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(3));
}

JSValuePtr jsSVGFEDisplacementMapElementSVG_CHANNEL_A(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(4));
}


}

#endif // ENABLE(SVG) && ENABLE(SVG_FILTERS)
