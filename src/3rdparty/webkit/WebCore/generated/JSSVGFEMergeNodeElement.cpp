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
#include "JSSVGFEMergeNodeElement.h"

#include <wtf/GetPtr.h>

#include "JSSVGAnimatedString.h"
#include "SVGFEMergeNodeElement.h"


using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGFEMergeNodeElement)

/* Hash table */

static const HashTableValue JSSVGFEMergeNodeElementTableValues[2] =
{
    { "in1", DontDelete|ReadOnly, (intptr_t)jsSVGFEMergeNodeElementIn1, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGFEMergeNodeElementTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGFEMergeNodeElementTableValues, 0 };
#else
    { 2, 1, JSSVGFEMergeNodeElementTableValues, 0 };
#endif

/* Hash table for prototype */

static const HashTableValue JSSVGFEMergeNodeElementPrototypeTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSSVGFEMergeNodeElementPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSSVGFEMergeNodeElementPrototypeTableValues, 0 };
#else
    { 1, 0, JSSVGFEMergeNodeElementPrototypeTableValues, 0 };
#endif

const ClassInfo JSSVGFEMergeNodeElementPrototype::s_info = { "SVGFEMergeNodeElementPrototype", 0, &JSSVGFEMergeNodeElementPrototypeTable, 0 };

JSObject* JSSVGFEMergeNodeElementPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSSVGFEMergeNodeElement>(exec, globalObject);
}

const ClassInfo JSSVGFEMergeNodeElement::s_info = { "SVGFEMergeNodeElement", &JSSVGElement::s_info, &JSSVGFEMergeNodeElementTable, 0 };

JSSVGFEMergeNodeElement::JSSVGFEMergeNodeElement(PassRefPtr<Structure> structure, PassRefPtr<SVGFEMergeNodeElement> impl)
    : JSSVGElement(structure, impl)
{
}

JSObject* JSSVGFEMergeNodeElement::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSSVGFEMergeNodeElementPrototype(JSSVGFEMergeNodeElementPrototype::createStructure(JSSVGElementPrototype::self(exec, globalObject)));
}

bool JSSVGFEMergeNodeElement::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGFEMergeNodeElement, Base>(exec, &JSSVGFEMergeNodeElementTable, this, propertyName, slot);
}

JSValuePtr jsSVGFEMergeNodeElementIn1(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    SVGFEMergeNodeElement* imp = static_cast<SVGFEMergeNodeElement*>(static_cast<JSSVGFEMergeNodeElement*>(asObject(slot.slotBase()))->impl());
    RefPtr<SVGAnimatedString> obj = imp->in1Animated();
    return toJS(exec, obj.get(), imp);
}


}

#endif // ENABLE(SVG) && ENABLE(SVG_FILTERS)
