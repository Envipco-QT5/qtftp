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

#include "JSHTMLFormElement.h"

#include <wtf/GetPtr.h>

#include <runtime/PropertyNameArray.h>
#include "AtomicString.h"
#include "HTMLCollection.h"
#include "HTMLFormElement.h"
#include "JSHTMLCollection.h"
#include "KURL.h"

#include <runtime/Error.h>
#include <runtime/JSNumberCell.h>
#include <runtime/JSString.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSHTMLFormElement)

/* Hash table */

static const HashTableValue JSHTMLFormElementTableValues[11] =
{
    { "elements", DontDelete|ReadOnly, (intptr_t)jsHTMLFormElementElements, (intptr_t)0 },
    { "length", DontDelete|ReadOnly, (intptr_t)jsHTMLFormElementLength, (intptr_t)0 },
    { "name", DontDelete, (intptr_t)jsHTMLFormElementName, (intptr_t)setJSHTMLFormElementName },
    { "acceptCharset", DontDelete, (intptr_t)jsHTMLFormElementAcceptCharset, (intptr_t)setJSHTMLFormElementAcceptCharset },
    { "action", DontDelete, (intptr_t)jsHTMLFormElementAction, (intptr_t)setJSHTMLFormElementAction },
    { "encoding", DontDelete, (intptr_t)jsHTMLFormElementEncoding, (intptr_t)setJSHTMLFormElementEncoding },
    { "enctype", DontDelete, (intptr_t)jsHTMLFormElementEnctype, (intptr_t)setJSHTMLFormElementEnctype },
    { "method", DontDelete, (intptr_t)jsHTMLFormElementMethod, (intptr_t)setJSHTMLFormElementMethod },
    { "target", DontDelete, (intptr_t)jsHTMLFormElementTarget, (intptr_t)setJSHTMLFormElementTarget },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsHTMLFormElementConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLFormElementTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 4095, JSHTMLFormElementTableValues, 0 };
#else
    { 34, 31, JSHTMLFormElementTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSHTMLFormElementConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLFormElementConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSHTMLFormElementConstructorTableValues, 0 };
#else
    { 1, 0, JSHTMLFormElementConstructorTableValues, 0 };
#endif

class JSHTMLFormElementConstructor : public DOMObject {
public:
    JSHTMLFormElementConstructor(ExecState* exec)
        : DOMObject(JSHTMLFormElementConstructor::createStructure(exec->lexicalGlobalObject()->objectPrototype()))
    {
        putDirect(exec->propertyNames().prototype, JSHTMLFormElementPrototype::self(exec), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValuePtr proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, ImplementsHasInstance)); 
    }
};

const ClassInfo JSHTMLFormElementConstructor::s_info = { "HTMLFormElementConstructor", 0, &JSHTMLFormElementConstructorTable, 0 };

bool JSHTMLFormElementConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSHTMLFormElementConstructor, DOMObject>(exec, &JSHTMLFormElementConstructorTable, this, propertyName, slot);
}

/* Hash table for prototype */

static const HashTableValue JSHTMLFormElementPrototypeTableValues[3] =
{
    { "submit", DontDelete|Function, (intptr_t)jsHTMLFormElementPrototypeFunctionSubmit, (intptr_t)0 },
    { "reset", DontDelete|Function, (intptr_t)jsHTMLFormElementPrototypeFunctionReset, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSHTMLFormElementPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 3, JSHTMLFormElementPrototypeTableValues, 0 };
#else
    { 4, 3, JSHTMLFormElementPrototypeTableValues, 0 };
#endif

const ClassInfo JSHTMLFormElementPrototype::s_info = { "HTMLFormElementPrototype", 0, &JSHTMLFormElementPrototypeTable, 0 };

JSObject* JSHTMLFormElementPrototype::self(ExecState* exec)
{
    return getDOMPrototype<JSHTMLFormElement>(exec);
}

bool JSHTMLFormElementPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticFunctionSlot<JSObject>(exec, &JSHTMLFormElementPrototypeTable, this, propertyName, slot);
}

const ClassInfo JSHTMLFormElement::s_info = { "HTMLFormElement", &JSHTMLElement::s_info, &JSHTMLFormElementTable, 0 };

JSHTMLFormElement::JSHTMLFormElement(PassRefPtr<Structure> structure, PassRefPtr<HTMLFormElement> impl)
    : JSHTMLElement(structure, impl)
{
}

JSObject* JSHTMLFormElement::createPrototype(ExecState* exec)
{
    return new (exec) JSHTMLFormElementPrototype(JSHTMLFormElementPrototype::createStructure(JSHTMLElementPrototype::self(exec)));
}

bool JSHTMLFormElement::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    if (canGetItemsForName(exec, static_cast<HTMLFormElement*>(impl()), propertyName)) {
        slot.setCustom(this, nameGetter);
        return true;
    }
    const HashEntry* entry = JSHTMLFormElementTable.entry(exec, propertyName);
    if (entry) {
        slot.setCustom(this, entry->propertyGetter());
        return true;
    }
    bool ok;
    unsigned index = propertyName.toUInt32(&ok, false);
    if (ok && index < static_cast<HTMLFormElement*>(impl())->length()) {
        slot.setCustomIndex(this, index, indexGetter);
        return true;
    }
    return getStaticValueSlot<JSHTMLFormElement, Base>(exec, &JSHTMLFormElementTable, this, propertyName, slot);
}

JSValuePtr jsHTMLFormElementElements(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    HTMLFormElement* imp = static_cast<HTMLFormElement*>(static_cast<JSHTMLFormElement*>(asObject(slot.slotBase()))->impl());
    return toJS(exec, WTF::getPtr(imp->elements()));
}

JSValuePtr jsHTMLFormElementLength(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    HTMLFormElement* imp = static_cast<HTMLFormElement*>(static_cast<JSHTMLFormElement*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->length());
}

JSValuePtr jsHTMLFormElementName(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    HTMLFormElement* imp = static_cast<HTMLFormElement*>(static_cast<JSHTMLFormElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->name());
}

JSValuePtr jsHTMLFormElementAcceptCharset(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    HTMLFormElement* imp = static_cast<HTMLFormElement*>(static_cast<JSHTMLFormElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->acceptCharset());
}

JSValuePtr jsHTMLFormElementAction(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    HTMLFormElement* imp = static_cast<HTMLFormElement*>(static_cast<JSHTMLFormElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->action());
}

JSValuePtr jsHTMLFormElementEncoding(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    HTMLFormElement* imp = static_cast<HTMLFormElement*>(static_cast<JSHTMLFormElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->encoding());
}

JSValuePtr jsHTMLFormElementEnctype(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    HTMLFormElement* imp = static_cast<HTMLFormElement*>(static_cast<JSHTMLFormElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->enctype());
}

JSValuePtr jsHTMLFormElementMethod(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    HTMLFormElement* imp = static_cast<HTMLFormElement*>(static_cast<JSHTMLFormElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->method());
}

JSValuePtr jsHTMLFormElementTarget(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    HTMLFormElement* imp = static_cast<HTMLFormElement*>(static_cast<JSHTMLFormElement*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->target());
}

JSValuePtr jsHTMLFormElementConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    return static_cast<JSHTMLFormElement*>(asObject(slot.slotBase()))->getConstructor(exec);
}
void JSHTMLFormElement::put(ExecState* exec, const Identifier& propertyName, JSValuePtr value, PutPropertySlot& slot)
{
    lookupPut<JSHTMLFormElement, Base>(exec, propertyName, value, &JSHTMLFormElementTable, this, slot);
}

void setJSHTMLFormElementName(ExecState* exec, JSObject* thisObject, JSValuePtr value)
{
    HTMLFormElement* imp = static_cast<HTMLFormElement*>(static_cast<JSHTMLFormElement*>(thisObject)->impl());
    imp->setName(valueToStringWithNullCheck(exec, value));
}

void setJSHTMLFormElementAcceptCharset(ExecState* exec, JSObject* thisObject, JSValuePtr value)
{
    HTMLFormElement* imp = static_cast<HTMLFormElement*>(static_cast<JSHTMLFormElement*>(thisObject)->impl());
    imp->setAcceptCharset(valueToStringWithNullCheck(exec, value));
}

void setJSHTMLFormElementAction(ExecState* exec, JSObject* thisObject, JSValuePtr value)
{
    HTMLFormElement* imp = static_cast<HTMLFormElement*>(static_cast<JSHTMLFormElement*>(thisObject)->impl());
    imp->setAction(valueToStringWithNullCheck(exec, value));
}

void setJSHTMLFormElementEncoding(ExecState* exec, JSObject* thisObject, JSValuePtr value)
{
    HTMLFormElement* imp = static_cast<HTMLFormElement*>(static_cast<JSHTMLFormElement*>(thisObject)->impl());
    imp->setEncoding(valueToStringWithNullCheck(exec, value));
}

void setJSHTMLFormElementEnctype(ExecState* exec, JSObject* thisObject, JSValuePtr value)
{
    HTMLFormElement* imp = static_cast<HTMLFormElement*>(static_cast<JSHTMLFormElement*>(thisObject)->impl());
    imp->setEnctype(valueToStringWithNullCheck(exec, value));
}

void setJSHTMLFormElementMethod(ExecState* exec, JSObject* thisObject, JSValuePtr value)
{
    HTMLFormElement* imp = static_cast<HTMLFormElement*>(static_cast<JSHTMLFormElement*>(thisObject)->impl());
    imp->setMethod(valueToStringWithNullCheck(exec, value));
}

void setJSHTMLFormElementTarget(ExecState* exec, JSObject* thisObject, JSValuePtr value)
{
    HTMLFormElement* imp = static_cast<HTMLFormElement*>(static_cast<JSHTMLFormElement*>(thisObject)->impl());
    imp->setTarget(valueToStringWithNullCheck(exec, value));
}

void JSHTMLFormElement::getPropertyNames(ExecState* exec, PropertyNameArray& propertyNames)
{
    for (unsigned i = 0; i < static_cast<HTMLFormElement*>(impl())->length(); ++i)
        propertyNames.add(Identifier::from(exec, i));
     Base::getPropertyNames(exec, propertyNames);
}

JSValuePtr JSHTMLFormElement::getConstructor(ExecState* exec)
{
    return getDOMConstructor<JSHTMLFormElementConstructor>(exec);
}

JSValuePtr jsHTMLFormElementPrototypeFunctionSubmit(ExecState* exec, JSObject*, JSValuePtr thisValue, const ArgList& args)
{
    if (!thisValue->isObject(&JSHTMLFormElement::s_info))
        return throwError(exec, TypeError);
    JSHTMLFormElement* castedThisObj = static_cast<JSHTMLFormElement*>(asObject(thisValue));
    HTMLFormElement* imp = static_cast<HTMLFormElement*>(castedThisObj->impl());

    imp->submit();
    return jsUndefined();
}

JSValuePtr jsHTMLFormElementPrototypeFunctionReset(ExecState* exec, JSObject*, JSValuePtr thisValue, const ArgList& args)
{
    if (!thisValue->isObject(&JSHTMLFormElement::s_info))
        return throwError(exec, TypeError);
    JSHTMLFormElement* castedThisObj = static_cast<JSHTMLFormElement*>(asObject(thisValue));
    HTMLFormElement* imp = static_cast<HTMLFormElement*>(castedThisObj->impl());

    imp->reset();
    return jsUndefined();
}


JSValuePtr JSHTMLFormElement::indexGetter(ExecState* exec, const Identifier& propertyName, const PropertySlot& slot)
{
    JSHTMLFormElement* thisObj = static_cast<JSHTMLFormElement*>(asObject(slot.slotBase()));
    return toJS(exec, static_cast<HTMLFormElement*>(thisObj->impl())->item(slot.index()));
}

}
