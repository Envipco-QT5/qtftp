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

#ifndef JSSVGAnimatedNumber_h
#define JSSVGAnimatedNumber_h


#if ENABLE(SVG)

#include "JSDOMBinding.h"
#include <runtime/JSGlobalObject.h>
#include <runtime/ObjectPrototype.h>

namespace WebCore {

class JSSVGAnimatedNumber : public DOMObject {
    typedef DOMObject Base;
public:
    JSSVGAnimatedNumber(PassRefPtr<JSC::Structure>, PassRefPtr<SVGAnimatedNumber>, SVGElement* context);
    virtual ~JSSVGAnimatedNumber();
    static JSC::JSObject* createPrototype(JSC::ExecState*);
    virtual bool getOwnPropertySlot(JSC::ExecState*, const JSC::Identifier& propertyName, JSC::PropertySlot&);
    virtual void put(JSC::ExecState*, const JSC::Identifier& propertyName, JSC::JSValuePtr, JSC::PutPropertySlot&);
    virtual const JSC::ClassInfo* classInfo() const { return &s_info; }
    static const JSC::ClassInfo s_info;

    static PassRefPtr<JSC::Structure> createStructure(JSC::JSValuePtr prototype)
    {
        return JSC::Structure::create(prototype, JSC::TypeInfo(JSC::ObjectType));
    }

    SVGAnimatedNumber* impl() const { return m_impl.get(); }
    SVGElement* context() const { return m_context.get(); }

private:
    RefPtr<SVGElement> m_context;
    RefPtr<SVGAnimatedNumber > m_impl;
};

JSC::JSValuePtr toJS(JSC::ExecState*, SVGAnimatedNumber*, SVGElement* context);
SVGAnimatedNumber* toSVGAnimatedNumber(JSC::JSValuePtr);

class JSSVGAnimatedNumberPrototype : public JSC::JSObject {
public:
    static JSC::JSObject* self(JSC::ExecState*);
    virtual const JSC::ClassInfo* classInfo() const { return &s_info; }
    static const JSC::ClassInfo s_info;
    JSSVGAnimatedNumberPrototype(PassRefPtr<JSC::Structure> structure) : JSC::JSObject(structure) { }
};

// Attributes

JSC::JSValuePtr jsSVGAnimatedNumberBaseVal(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
void setJSSVGAnimatedNumberBaseVal(JSC::ExecState*, JSC::JSObject*, JSC::JSValuePtr);
JSC::JSValuePtr jsSVGAnimatedNumberAnimVal(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);

} // namespace WebCore

#endif // ENABLE(SVG)

#endif
