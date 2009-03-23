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

#ifndef JSEntity_h
#define JSEntity_h

#include "JSNode.h"

namespace WebCore {

class Entity;

class JSEntity : public JSNode {
    typedef JSNode Base;
public:
    JSEntity(PassRefPtr<JSC::Structure>, PassRefPtr<Entity>);
    static JSC::JSObject* createPrototype(JSC::ExecState*);
    virtual bool getOwnPropertySlot(JSC::ExecState*, const JSC::Identifier& propertyName, JSC::PropertySlot&);
    virtual const JSC::ClassInfo* classInfo() const { return &s_info; }
    static const JSC::ClassInfo s_info;

    static PassRefPtr<JSC::Structure> createStructure(JSC::JSValuePtr prototype)
    {
        return JSC::Structure::create(prototype, JSC::TypeInfo(JSC::ObjectType));
    }

    static JSC::JSValuePtr getConstructor(JSC::ExecState*);
};


class JSEntityPrototype : public JSC::JSObject {
public:
    static JSC::JSObject* self(JSC::ExecState*);
    virtual const JSC::ClassInfo* classInfo() const { return &s_info; }
    static const JSC::ClassInfo s_info;
    JSEntityPrototype(PassRefPtr<JSC::Structure> structure) : JSC::JSObject(structure) { }
};

// Attributes

JSC::JSValuePtr jsEntityPublicId(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
JSC::JSValuePtr jsEntitySystemId(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
JSC::JSValuePtr jsEntityNotationName(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
JSC::JSValuePtr jsEntityConstructor(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);

} // namespace WebCore

#endif
