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

#include "JSDOMCoreException.h"

#include <wtf/GetPtr.h>

#include "DOMCoreException.h"
#include "KURL.h"

#include <runtime/Error.h>
#include <runtime/JSNumberCell.h>
#include <runtime/JSString.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSDOMCoreException)

/* Hash table */

static const HashTableValue JSDOMCoreExceptionTableValues[5] =
{
    { "code", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionCode, (intptr_t)0 },
    { "name", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionName, (intptr_t)0 },
    { "message", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionMessage, (intptr_t)0 },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsDOMCoreExceptionConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSDOMCoreExceptionTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 127, JSDOMCoreExceptionTableValues, 0 };
#else
    { 10, 7, JSDOMCoreExceptionTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSDOMCoreExceptionConstructorTableValues[18] =
{
    { "INDEX_SIZE_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionINDEX_SIZE_ERR, (intptr_t)0 },
    { "DOMSTRING_SIZE_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionDOMSTRING_SIZE_ERR, (intptr_t)0 },
    { "HIERARCHY_REQUEST_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionHIERARCHY_REQUEST_ERR, (intptr_t)0 },
    { "WRONG_DOCUMENT_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionWRONG_DOCUMENT_ERR, (intptr_t)0 },
    { "INVALID_CHARACTER_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionINVALID_CHARACTER_ERR, (intptr_t)0 },
    { "NO_DATA_ALLOWED_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionNO_DATA_ALLOWED_ERR, (intptr_t)0 },
    { "NO_MODIFICATION_ALLOWED_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionNO_MODIFICATION_ALLOWED_ERR, (intptr_t)0 },
    { "NOT_FOUND_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionNOT_FOUND_ERR, (intptr_t)0 },
    { "NOT_SUPPORTED_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionNOT_SUPPORTED_ERR, (intptr_t)0 },
    { "INUSE_ATTRIBUTE_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionINUSE_ATTRIBUTE_ERR, (intptr_t)0 },
    { "INVALID_STATE_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionINVALID_STATE_ERR, (intptr_t)0 },
    { "SYNTAX_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionSYNTAX_ERR, (intptr_t)0 },
    { "INVALID_MODIFICATION_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionINVALID_MODIFICATION_ERR, (intptr_t)0 },
    { "NAMESPACE_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionNAMESPACE_ERR, (intptr_t)0 },
    { "INVALID_ACCESS_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionINVALID_ACCESS_ERR, (intptr_t)0 },
    { "VALIDATION_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionVALIDATION_ERR, (intptr_t)0 },
    { "TYPE_MISMATCH_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionTYPE_MISMATCH_ERR, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSDOMCoreExceptionConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 511, JSDOMCoreExceptionConstructorTableValues, 0 };
#else
    { 67, 63, JSDOMCoreExceptionConstructorTableValues, 0 };
#endif

class JSDOMCoreExceptionConstructor : public DOMObject {
public:
    JSDOMCoreExceptionConstructor(ExecState* exec)
        : DOMObject(JSDOMCoreExceptionConstructor::createStructure(exec->lexicalGlobalObject()->objectPrototype()))
    {
        putDirect(exec->propertyNames().prototype, JSDOMCoreExceptionPrototype::self(exec, exec->lexicalGlobalObject()), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValuePtr proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, ImplementsHasInstance)); 
    }
};

const ClassInfo JSDOMCoreExceptionConstructor::s_info = { "DOMExceptionConstructor", 0, &JSDOMCoreExceptionConstructorTable, 0 };

bool JSDOMCoreExceptionConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSDOMCoreExceptionConstructor, DOMObject>(exec, &JSDOMCoreExceptionConstructorTable, this, propertyName, slot);
}

/* Hash table for prototype */

static const HashTableValue JSDOMCoreExceptionPrototypeTableValues[19] =
{
    { "INDEX_SIZE_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionINDEX_SIZE_ERR, (intptr_t)0 },
    { "DOMSTRING_SIZE_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionDOMSTRING_SIZE_ERR, (intptr_t)0 },
    { "HIERARCHY_REQUEST_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionHIERARCHY_REQUEST_ERR, (intptr_t)0 },
    { "WRONG_DOCUMENT_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionWRONG_DOCUMENT_ERR, (intptr_t)0 },
    { "INVALID_CHARACTER_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionINVALID_CHARACTER_ERR, (intptr_t)0 },
    { "NO_DATA_ALLOWED_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionNO_DATA_ALLOWED_ERR, (intptr_t)0 },
    { "NO_MODIFICATION_ALLOWED_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionNO_MODIFICATION_ALLOWED_ERR, (intptr_t)0 },
    { "NOT_FOUND_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionNOT_FOUND_ERR, (intptr_t)0 },
    { "NOT_SUPPORTED_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionNOT_SUPPORTED_ERR, (intptr_t)0 },
    { "INUSE_ATTRIBUTE_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionINUSE_ATTRIBUTE_ERR, (intptr_t)0 },
    { "INVALID_STATE_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionINVALID_STATE_ERR, (intptr_t)0 },
    { "SYNTAX_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionSYNTAX_ERR, (intptr_t)0 },
    { "INVALID_MODIFICATION_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionINVALID_MODIFICATION_ERR, (intptr_t)0 },
    { "NAMESPACE_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionNAMESPACE_ERR, (intptr_t)0 },
    { "INVALID_ACCESS_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionINVALID_ACCESS_ERR, (intptr_t)0 },
    { "VALIDATION_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionVALIDATION_ERR, (intptr_t)0 },
    { "TYPE_MISMATCH_ERR", DontDelete|ReadOnly, (intptr_t)jsDOMCoreExceptionTYPE_MISMATCH_ERR, (intptr_t)0 },
    { "toString", DontDelete|DontEnum|Function, (intptr_t)jsDOMCoreExceptionPrototypeFunctionToString, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSDOMCoreExceptionPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 511, JSDOMCoreExceptionPrototypeTableValues, 0 };
#else
    { 67, 63, JSDOMCoreExceptionPrototypeTableValues, 0 };
#endif

const ClassInfo JSDOMCoreExceptionPrototype::s_info = { "DOMExceptionPrototype", 0, &JSDOMCoreExceptionPrototypeTable, 0 };

JSObject* JSDOMCoreExceptionPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSDOMCoreException>(exec, globalObject);
}

bool JSDOMCoreExceptionPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticPropertySlot<JSDOMCoreExceptionPrototype, JSObject>(exec, &JSDOMCoreExceptionPrototypeTable, this, propertyName, slot);
}

const ClassInfo JSDOMCoreException::s_info = { "DOMException", 0, &JSDOMCoreExceptionTable, 0 };

JSDOMCoreException::JSDOMCoreException(PassRefPtr<Structure> structure, PassRefPtr<DOMCoreException> impl)
    : DOMObject(structure)
    , m_impl(impl)
{
}

JSDOMCoreException::~JSDOMCoreException()
{
    forgetDOMObject(*Heap::heap(this)->globalData(), m_impl.get());

}

JSObject* JSDOMCoreException::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSDOMCoreExceptionPrototype(JSDOMCoreExceptionPrototype::createStructure(globalObject->objectPrototype()));
}

bool JSDOMCoreException::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSDOMCoreException, Base>(exec, &JSDOMCoreExceptionTable, this, propertyName, slot);
}

JSValuePtr jsDOMCoreExceptionCode(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    DOMCoreException* imp = static_cast<DOMCoreException*>(static_cast<JSDOMCoreException*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->code());
}

JSValuePtr jsDOMCoreExceptionName(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    DOMCoreException* imp = static_cast<DOMCoreException*>(static_cast<JSDOMCoreException*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->name());
}

JSValuePtr jsDOMCoreExceptionMessage(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    DOMCoreException* imp = static_cast<DOMCoreException*>(static_cast<JSDOMCoreException*>(asObject(slot.slotBase()))->impl());
    return jsString(exec, imp->message());
}

JSValuePtr jsDOMCoreExceptionConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    return static_cast<JSDOMCoreException*>(asObject(slot.slotBase()))->getConstructor(exec);
}
JSValuePtr JSDOMCoreException::getConstructor(ExecState* exec)
{
    return getDOMConstructor<JSDOMCoreExceptionConstructor>(exec);
}

JSValuePtr jsDOMCoreExceptionPrototypeFunctionToString(ExecState* exec, JSObject*, JSValuePtr thisValue, const ArgList& args)
{
    if (!thisValue->isObject(&JSDOMCoreException::s_info))
        return throwError(exec, TypeError);
    JSDOMCoreException* castedThisObj = static_cast<JSDOMCoreException*>(asObject(thisValue));
    DOMCoreException* imp = static_cast<DOMCoreException*>(castedThisObj->impl());


    JSC::JSValuePtr result = jsString(exec, imp->toString());
    return result;
}

// Constant getters

JSValuePtr jsDOMCoreExceptionINDEX_SIZE_ERR(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(1));
}

JSValuePtr jsDOMCoreExceptionDOMSTRING_SIZE_ERR(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(2));
}

JSValuePtr jsDOMCoreExceptionHIERARCHY_REQUEST_ERR(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(3));
}

JSValuePtr jsDOMCoreExceptionWRONG_DOCUMENT_ERR(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(4));
}

JSValuePtr jsDOMCoreExceptionINVALID_CHARACTER_ERR(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(5));
}

JSValuePtr jsDOMCoreExceptionNO_DATA_ALLOWED_ERR(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(6));
}

JSValuePtr jsDOMCoreExceptionNO_MODIFICATION_ALLOWED_ERR(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(7));
}

JSValuePtr jsDOMCoreExceptionNOT_FOUND_ERR(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(8));
}

JSValuePtr jsDOMCoreExceptionNOT_SUPPORTED_ERR(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(9));
}

JSValuePtr jsDOMCoreExceptionINUSE_ATTRIBUTE_ERR(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(10));
}

JSValuePtr jsDOMCoreExceptionINVALID_STATE_ERR(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(11));
}

JSValuePtr jsDOMCoreExceptionSYNTAX_ERR(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(12));
}

JSValuePtr jsDOMCoreExceptionINVALID_MODIFICATION_ERR(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(13));
}

JSValuePtr jsDOMCoreExceptionNAMESPACE_ERR(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(14));
}

JSValuePtr jsDOMCoreExceptionINVALID_ACCESS_ERR(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(15));
}

JSValuePtr jsDOMCoreExceptionVALIDATION_ERR(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(16));
}

JSValuePtr jsDOMCoreExceptionTYPE_MISMATCH_ERR(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(17));
}

JSC::JSValuePtr toJS(JSC::ExecState* exec, DOMCoreException* object)
{
    return getDOMObjectWrapper<JSDOMCoreException>(exec, object);
}
DOMCoreException* toDOMCoreException(JSC::JSValuePtr value)
{
    return value->isObject(&JSDOMCoreException::s_info) ? static_cast<JSDOMCoreException*>(asObject(value))->impl() : 0;
}

}
