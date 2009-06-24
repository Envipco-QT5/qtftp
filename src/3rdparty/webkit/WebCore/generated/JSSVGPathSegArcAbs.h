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

#ifndef JSSVGPathSegArcAbs_h
#define JSSVGPathSegArcAbs_h


#if ENABLE(SVG)

#include "JSSVGPathSeg.h"

namespace WebCore {

class SVGPathSegArcAbs;

class JSSVGPathSegArcAbs : public JSSVGPathSeg {
    typedef JSSVGPathSeg Base;
public:
    JSSVGPathSegArcAbs(PassRefPtr<JSC::Structure>, PassRefPtr<SVGPathSegArcAbs>, SVGElement* context);
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


class JSSVGPathSegArcAbsPrototype : public JSC::JSObject {
public:
    static JSC::JSObject* self(JSC::ExecState*, JSC::JSGlobalObject*);
    virtual const JSC::ClassInfo* classInfo() const { return &s_info; }
    static const JSC::ClassInfo s_info;
    JSSVGPathSegArcAbsPrototype(PassRefPtr<JSC::Structure> structure) : JSC::JSObject(structure) { }
};

// Attributes

JSC::JSValuePtr jsSVGPathSegArcAbsX(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
void setJSSVGPathSegArcAbsX(JSC::ExecState*, JSC::JSObject*, JSC::JSValuePtr);
JSC::JSValuePtr jsSVGPathSegArcAbsY(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
void setJSSVGPathSegArcAbsY(JSC::ExecState*, JSC::JSObject*, JSC::JSValuePtr);
JSC::JSValuePtr jsSVGPathSegArcAbsR1(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
void setJSSVGPathSegArcAbsR1(JSC::ExecState*, JSC::JSObject*, JSC::JSValuePtr);
JSC::JSValuePtr jsSVGPathSegArcAbsR2(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
void setJSSVGPathSegArcAbsR2(JSC::ExecState*, JSC::JSObject*, JSC::JSValuePtr);
JSC::JSValuePtr jsSVGPathSegArcAbsAngle(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
void setJSSVGPathSegArcAbsAngle(JSC::ExecState*, JSC::JSObject*, JSC::JSValuePtr);
JSC::JSValuePtr jsSVGPathSegArcAbsLargeArcFlag(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
void setJSSVGPathSegArcAbsLargeArcFlag(JSC::ExecState*, JSC::JSObject*, JSC::JSValuePtr);
JSC::JSValuePtr jsSVGPathSegArcAbsSweepFlag(JSC::ExecState*, const JSC::Identifier&, const JSC::PropertySlot&);
void setJSSVGPathSegArcAbsSweepFlag(JSC::ExecState*, JSC::JSObject*, JSC::JSValuePtr);

} // namespace WebCore

#endif // ENABLE(SVG)

#endif
