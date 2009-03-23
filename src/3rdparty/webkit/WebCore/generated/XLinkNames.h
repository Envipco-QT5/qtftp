/*
 * THIS FILE IS AUTOMATICALLY GENERATED, DO NOT EDIT.
 *
 *
 * Copyright (C) 2005 Apple Computer, Inc.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */


#ifndef DOM_XLinkNAMES_H
#define DOM_XLinkNAMES_H

#include "QualifiedName.h"

namespace WebCore {

 namespace XLinkNames {

#ifndef DOM_XLinkNAMES_HIDE_GLOBALS
// Namespace
extern const WebCore::AtomicString xlinkNamespaceURI;

// Attributes
extern const WebCore::QualifiedName actuateAttr;
extern char actuateAttrString[];
extern const WebCore::QualifiedName arcroleAttr;
extern char arcroleAttrString[];
extern const WebCore::QualifiedName hrefAttr;
extern char hrefAttrString[];
extern const WebCore::QualifiedName roleAttr;
extern char roleAttrString[];
extern const WebCore::QualifiedName showAttr;
extern char showAttrString[];
extern const WebCore::QualifiedName titleAttr;
extern char titleAttrString[];
extern const WebCore::QualifiedName typeAttr;
extern char typeAttrString[];


WebCore::QualifiedName** getXLinkAttr(size_t* size);
#endif

void init();

} }

#endif

