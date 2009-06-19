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

#include "JSNotation.h"

#include <wtf/GetPtr.h>

#include "KURL.h"
#include "Notation.h"

#include <runtime/JSNumberCell.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSNotation)

/* Hash table */

static const HashTableValue JSNotationTableValues[4] =
{
    { "publicId", DontDelete|ReadOnly, (intptr_t)jsNotationPublicId, (intptr_t)0 },
    { "systemId", DontDelete|ReadOnly, (intptr_t)jsNotationSystemId, (intptr_t)0 },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsNotationConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSNotationTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 15, JSNotationTableValues, 0 };
#else
    { 9, 7, JSNotationTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSNotationConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSNotationConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSNotationConstructorTableValues, 0 };
#else
    { 1, 0, JSNotationConstructorTableValues, 0 };
#endif

class JSNotationConstructor : public DOMObject {
public:
    JSNotationConstructor(ExecState* exec)
        : DOMObject(JSNotationConstructor::createStructure(exec->lexicalGlobalObject()->objectPrototype()))
    {
        putDirect(exec->propertyNames().prototype, JSNotationPrototype::self(exec, exec->lexicalGlobalObject()), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValuePtr proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, ImplementsHasInstance)); 
    }
};

const ClassInfo JSNotationConstructor::s_info = { "NotationConstructor", 0, &JSNotationConstructorTable, 0 };

bool JSNotationConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSNotationConstructor, DOMObject>(exec, &JSNotationConstructorTable, this, propertyName, slot);
}

/* Hash table for prototype */

static const HashTableValue JSNotationPrototypeTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSNotationPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSNotationPrototypeTableValues, 0 };
#else
    { 1, 0, JSNotationPrototypeTableValues, 0 };
#endif

const ClassInfo JSNotationPrototype::s_info = { "NotationPrototype", 0, &JSNotationPrototypeTable, 0 };

JSObject* JSNotationPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSNotation>(exec, globalObject);
}

const ClassInfo JSNotation::s_info = { "Notation", &JSNode::s_info, &JSNotationTable, 0 };

JSNotation::JSNotation(PassRefPtr<Structure> structure, PassRefPtr<Notation> impl)
    : JSNode(structure, impl)
{
}

JSObject* JSNotation::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSNotationPrototype(JSNotationPrototype::createStructure(JSNodePrototype::self(exec, globalObject)));
}

bool JSNotation::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSNotation, Base>(exec, &JSNotationTable, this, propertyName, slot);
}

JSValuePtr jsNotationPublicId(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    Notation* imp = static_cast<Notation*>(static_cast<JSNotation*>(asObject(slot.slotBase()))->impl());
    return jsStringOrNull(exec, imp->publicId());
}

JSValuePtr jsNotationSystemId(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    Notation* imp = static_cast<Notation*>(static_cast<JSNotation*>(asObject(slot.slotBase()))->impl());
    return jsStringOrNull(exec, imp->systemId());
}

JSValuePtr jsNotationConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    return static_cast<JSNotation*>(asObject(slot.slotBase()))->getConstructor(exec);
}
JSValuePtr JSNotation::getConstructor(ExecState* exec)
{
    return getDOMConstructor<JSNotationConstructor>(exec);
}


}
