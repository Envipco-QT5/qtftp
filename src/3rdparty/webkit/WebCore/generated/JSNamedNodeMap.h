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

#ifndef JSNamedNodeMap_h
#define JSNamedNodeMap_h

#include "JSDOMBinding.h"
#include <runtime/JSGlobalObject.h>
#include <runtime/ObjectPrototype.h>

namespace WebCore {

class NamedNodeMap;

class JSNamedNodeMap : public DOMObject {
    typedef DOMObject Base;
public:
    JSNamedNodeMap(PassRefPtr<JSC::Structure>, PassRefPtr<NamedNodeMap>);
    virtual ~JSNamedNodeMap();
    static JSC::JSObject* createPrototype(JSC::ExecState*, JSC::JSGlobalObject*);
    virtual bool getOwnPropertySlot(JSC::ExecState*, const JSC::Identifier& propertyName, JSC::PropertySlot&);
    virtual bool getOwnPropertySlot(JSC::ExecState*, unsigned propertyName, JSC::PropertySlot&);
    virtual const JSC::ClassInfo* classInfo() const { return &s_info; }
    static const JSC::ClassInfo s_info;

    static PassRefPtr<JSC::Structure> createStructure(JSC::JSValuePtr prototype)
    {
        return JSC::Structure::create(prototype, JSC::TypeInfo(JSC::ObjectType));
    }

    virtual void getPropertyNames(JSC::ExecState*, JSC::PropertyNameArray&);
    static JSC::JSValuePtr getConstructor(JSC::ExecState*);
    NamedNodeMap* impl() const { return m_impl.get(); }

private:
    RefPtr<NamedNodeMap> m_impl;
    static JSC::JSValuePtr indexGetter(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
private:
    static bool canGetItemsForName(JSC::ExecState*, NamedNodeMap*, const JSC::Identifier&);
    static JSC::JSValuePtr nameGetter(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
};

JSC::JSValuePtr toJS(JSC::ExecState*, NamedNodeMap*);
NamedNodeMap* toNamedNodeMap(JSC::JSValuePtr);

class JSNamedNodeMapPrototype : public JSC::JSObject {
public:
    static JSC::JSObject* self(JSC::ExecState*, JSC::JSGlobalObject*);
    virtual const JSC::ClassInfo* classInfo() const { return &s_info; }
    static const JSC::ClassInfo s_info;
    virtual bool getOwnPropertySlot(JSC::ExecState*, const JSC::Identifier&, JSC::PropertySlot&);
    static PassRefPtr<JSC::Structure> createStructure(JSC::JSValuePtr prototype)
    {
        return JSC::Structure::create(prototype, JSC::TypeInfo(JSC::ObjectType));
    }
    JSNamedNodeMapPrototype(PassRefPtr<JSC::Structure> structure) : JSC::JSObject(structure) { }
};

// Functions

JSC::JSValuePtr jsNamedNodeMapPrototypeFunctionGetNamedItem(JSC::ExecState*, JSC::JSObject*, JSC::JSValuePtr, const JSC::ArgList&);
JSC::JSValuePtr jsNamedNodeMapPrototypeFunctionSetNamedItem(JSC::ExecState*, JSC::JSObject*, JSC::JSValuePtr, const JSC::ArgList&);
JSC::JSValuePtr jsNamedNodeMapPrototypeFunctionRemoveNamedItem(JSC::ExecState*, JSC::JSObject*, JSC::JSValuePtr, const JSC::ArgList&);
JSC::JSValuePtr jsNamedNodeMapPrototypeFunctionItem(JSC::ExecState*, JSC::JSObject*, JSC::JSValuePtr, const JSC::ArgList&);
JSC::JSValuePtr jsNamedNodeMapPrototypeFunctionGetNamedItemNS(JSC::ExecState*, JSC::JSObject*, JSC::JSValuePtr, const JSC::ArgList&);
JSC::JSValuePtr jsNamedNodeMapPrototypeFunctionSetNamedItemNS(JSC::ExecState*, JSC::JSObject*, JSC::JSValuePtr, const JSC::ArgList&);
JSC::JSValuePtr jsNamedNodeMapPrototypeFunctionRemoveNamedItemNS(JSC::ExecState*, JSC::JSObject*, JSC::JSValuePtr, const JSC::ArgList&);
// Attributes

JSC::JSValuePtr jsNamedNodeMapLength(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
JSC::JSValuePtr jsNamedNodeMapConstructor(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);

} // namespace WebCore

#endif
