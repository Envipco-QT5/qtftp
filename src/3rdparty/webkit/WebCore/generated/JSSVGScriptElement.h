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

#ifndef JSSVGScriptElement_h
#define JSSVGScriptElement_h


#if ENABLE(SVG)

#include "JSSVGElement.h"

namespace WebCore {

class SVGScriptElement;

class JSSVGScriptElement : public JSSVGElement {
    typedef JSSVGElement Base;
public:
    JSSVGScriptElement(PassRefPtr<JSC::Structure>, PassRefPtr<SVGScriptElement>);
    static JSC::JSObject* createPrototype(JSC::ExecState*, JSC::JSGlobalObject*);
    virtual bool getOwnPropertySlot(JSC::ExecState*, const JSC::Identifier& propertyName, JSC::PropertySlot&);
    virtual void put(JSC::ExecState*, const JSC::Identifier& propertyName, JSC::JSValuePtr, JSC::PutPropertySlot&);
    virtual const JSC::ClassInfo* classInfo() const { return &s_info; }
    static const JSC::ClassInfo s_info;

    static PassRefPtr<JSC::Structure> createStructure(JSC::JSValuePtr prototype)
    {
        return JSC::Structure::create(prototype, JSC::TypeInfo(JSC::ObjectType));
    }

};


class JSSVGScriptElementPrototype : public JSC::JSObject {
public:
    static JSC::JSObject* self(JSC::ExecState*, JSC::JSGlobalObject*);
    virtual const JSC::ClassInfo* classInfo() const { return &s_info; }
    static const JSC::ClassInfo s_info;
    JSSVGScriptElementPrototype(PassRefPtr<JSC::Structure> structure) : JSC::JSObject(structure) { }
};

// Attributes

JSC::JSValuePtr jsSVGScriptElementType(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
void setJSSVGScriptElementType(JSC::ExecState*, JSC::JSObject*, JSC::JSValuePtr);
JSC::JSValuePtr jsSVGScriptElementHref(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
JSC::JSValuePtr jsSVGScriptElementExternalResourcesRequired(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);

} // namespace WebCore

#endif // ENABLE(SVG)

#endif
