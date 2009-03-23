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
#include "JSSVGElement.h"

#include <wtf/GetPtr.h>

#include "JSSVGElement.h"
#include "JSSVGSVGElement.h"
#include "KURL.h"
#include "SVGElement.h"
#include "SVGSVGElement.h"

#include <runtime/JSString.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGElement)

/* Hash table */

static const HashTableValue JSSVGElementTableValues[5] =
{
    { "id", DontDelete, (intptr_t)jsSVGElementId, (intptr_t)setJSSVGElementId },
    { "xmlbase", DontDelete, (intptr_t)jsSVGElementXmlbase, (intptr_t)setJSSVGElementXmlbase },
    { "ownerSVGElement", DontDelete|ReadOnly, (intptr_t)jsSVGElementOwnerSVGElement, (intptr_t)0 },
    { "viewportElement", DontDelete|ReadOnly, (intptr_t)jsSVGElementViewportElement, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGElementTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 15, JSSVGElementTableValues, 0 };
#else
    { 9, 7, JSSVGElementTableValues, 0 };
#endif

/* Hash table for prototype */

static const HashTableValue JSSVGElementPrototypeTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGElementPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGElementPrototypeTableValues, 0 };
#else
    { 1, 0, JSSVGElementPrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGElementPrototype::s_info = { "SVGElementPrototype", 0, &JSSVGElementPrototypeTable, 0 };

JSObject* JSSVGElementPrototype::self(ExecState* exec)
{
    return getDOMPrototype<JSSVGElement>(exec);
}

const ClassInfo JSSVGElement::s_info = { "SVGElement", &JSElement::s_info, &JSSVGElementTable, 0 };

JSSVGElement::JSSVGElement(PassRefPtr<Structure> structure, PassRefPtr<SVGElement> impl)
    : JSElement(structure, impl)
{
}

JSObject* JSSVGElement::createPrototype(ExecState* exec)
{
    return new (exec) JSSVGElementPrototype(JSSVGElementPrototype::createStructure(JSElementPrototype::self(exec)));
}

bool JSSVGElement::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGElement, Base>(exec, &JSSVGElementTable, this, propertyName, slot);
}

JSValuePtr jsSVGElementId(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGElement* imp = static_cast<SVGElement*>(static_cast<JSSVGElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->id());
}

JSValuePtr jsSVGElementXmlbase(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGElement* imp = static_cast<SVGElement*>(static_cast<JSSVGElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->xmlbase());
}

JSValuePtr jsSVGElementOwnerSVGElement(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGElement* imp = static_cast<SVGElement*>(static_cast<JSSVGElement*>(asObject(slot.slotBase()))->impl());
    return toJS(exec, WTF::getPtr(imp->ownerSVGElement()));
}

JSValuePtr jsSVGElementViewportElement(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGElement* imp = static_cast<SVGElement*>(static_cast<JSSVGElement*>(asObject(slot.slotBase()))->impl());
    return toJS(exec, WTF::getPtr(imp->viewportElement()));
}

void JSSVGElement::put(ExecState* exec, const Identifier& propertyName, JSValuePtr value, PutPropertySlot& slot)
{
    lookupPut<JSSVGElement, Base>(exec, propertyName, value, &JSSVGElementTable, this, slot);
}

void setJSSVGElementId(ExecState* exec, JSObject* thisObject, JSValuePtr value)
{
    SVGElement* imp = static_cast<SVGElement*>(static_cast<JSSVGElement*>(thisObject)->impl());
    ExceptionCode ec = 0;
    imp->setId(valueToStringWithNullCheck(exec, value), ec);
    setDOMException(exec, ec);
}

void setJSSVGElementXmlbase(ExecState* exec, JSObject* thisObject, JSValuePtr value)
{
    SVGElement* imp = static_cast<SVGElement*>(static_cast<JSSVGElement*>(thisObject)->impl());
    ExceptionCode ec = 0;
    imp->setXmlbase(valueToStringWithNullCheck(exec, value), ec);
    setDOMException(exec, ec);
}

SVGElement* toSVGElement(JSC::JSValuePtr value)
{
    return value->isObject(&JSSVGElement::s_info) ? static_cast<JSSVGElement*>(asObject(value))->impl() : 0;
}

}

#endif // ENABLE(SVG)
