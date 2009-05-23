/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain
** additional rights. These rights are described in the Nokia Qt LGPL
** Exception version 1.0, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

// Most of the code here was originally written by Hans Petter Bieker,
// and is included in Qt with the author's permission, and the grateful
// thanks of the Trolltech team.

#include "qtsciicodec_p.h"
#include "qlist.h"

#ifndef QT_NO_CODECS

QT_BEGIN_NAMESPACE

static unsigned char qt_UnicodeToTSCII(ushort u1, ushort u2, ushort u3);
static unsigned int qt_TSCIIToUnicode(unsigned int code, uint *s);

#define IsTSCIIChar(c)        (((c) >= 0x80) && ((c) <= 0xfd))

/*! \class QTsciiCodec
    \reentrant
    \internal
*/

/*!
    Destroys the text codec object.
*/
QTsciiCodec::~QTsciiCodec()
{
}

/*!
    Converts the first \a len characters in \a uc from Unicode to this
    encoding, and returns the result in a byte array. The \a state contains
    some conversion flags, and is used by the codec to maintain state
    information.
*/
QByteArray QTsciiCodec::convertFromUnicode(const QChar *uc, int len, ConverterState *state) const
{
    char replacement = '?';
    if (state) {
        if (state->flags & ConvertInvalidToNull)
            replacement = 0;
    }
    int invalid = 0;

    QByteArray rstr;
    rstr.resize(len);
    uchar* cursor = (uchar*)rstr.data();
    for (int i = 0; i < len; i++) {
        QChar ch = uc[i];
        uchar j;
        if (ch.row() == 0x00 && ch.cell() < 0x80) {
            // ASCII
            j = ch.cell();
        } else if ((j = qt_UnicodeToTSCII(uc[i].unicode(),
                                          uc[i + 1].unicode(),
                                          uc[i + 2].unicode()))) {
            // We have to check the combined chars first!
            i += 2;
        } else if ((j = qt_UnicodeToTSCII(uc[i].unicode(),
                                          uc[i + 1].unicode(), 0))) {
            i++;
        } else if ((j = qt_UnicodeToTSCII(uc[i].unicode(), 0, 0))) {
        } else {
            // Error
            j = replacement;
            ++invalid;
        }
        *cursor++ = j;
    }
    rstr.resize(cursor - (const uchar*)rstr.constData());

    if (state) {
        state->invalidChars += invalid;
    }
    return rstr;
}

/*!
    Converts the first \a len characters in \a chars from this encoding
    to Unicode, and returns the result in a QString. The \a state contains
    some conversion flags, and is used by the codec to maintain state
    information.
*/
QString QTsciiCodec::convertToUnicode(const char* chars, int len, ConverterState *state) const
{
    QChar replacement = QChar::ReplacementCharacter;
    if (state) {
        if (state->flags & ConvertInvalidToNull)
            replacement = QChar::Null;
    }
    int invalid = 0;

    QString result;
    for (int i = 0; i < len; i++) {
        uchar ch = chars[i];
        if (ch < 0x80) {
            // ASCII
            result += QLatin1Char(ch);
        } else if (IsTSCIIChar(ch)) {
            // TSCII
            uint s[3];
            uint u = qt_TSCIIToUnicode(ch, s);
            uint *p = s;
            while (u--) {
                uint c = *p++;
                if (c)
                    result += QChar(c);
                else {
                    result += replacement;
                    ++invalid;
                }
            }
        } else {
            // Invalid
            result += replacement;
            ++invalid;
        }
    }

    if (state) {
        state->invalidChars += invalid;
    }
    return result;
}

/*!
    Returns the official name for the encoding that is handled by the codec.

    \sa QTextCodec::name()
*/
QByteArray QTsciiCodec::name() const
{
    return "TSCII";
}

/*!
    Returns the MIB enum for the encoding.

    \sa QTextCodec::mibEnum()
*/
int QTsciiCodec::mibEnum() const
{
  return 2107;
}

static const int UnToTsLast = 124; // 125 items -- so the last will be 124
static const ushort UnToTs [][4] = {
    // *Sorted* list of TSCII maping for unicode chars
    //FIRST  SECOND  THIRD   TSCII
    {0x00A0, 0x0000, 0x0000, 0xA0},
    {0x00A9, 0x0000, 0x0000, 0xA9},
    {0x0B83, 0x0000, 0x0000, 0xB7},
    {0x0B85, 0x0000, 0x0000, 0xAB},
    {0x0B86, 0x0000, 0x0000, 0xAC},
    {0x0B87, 0x0000, 0x0000, 0xAD},
    {0x0B88, 0x0000, 0x0000, 0xAE},
    {0x0B89, 0x0000, 0x0000, 0xAF},
    {0x0B8A, 0x0000, 0x0000, 0xB0},
    {0x0B8E, 0x0000, 0x0000, 0xB1},
    {0x0B8F, 0x0000, 0x0000, 0xB2},
    {0x0B90, 0x0000, 0x0000, 0xB3},
    {0x0B92, 0x0000, 0x0000, 0xB4},
    {0x0B93, 0x0000, 0x0000, 0xB5},
    {0x0B94, 0x0000, 0x0000, 0xB6},
    {0x0B95, 0x0000, 0x0000, 0xB8},
    {0x0B95, 0x0B82, 0x0000, 0xEC},
    {0x0B95, 0x0BC1, 0x0000, 0xCC},
    {0x0B95, 0x0BC2, 0x0000, 0xDC},
    {0x0B99, 0x0000, 0x0000, 0xB9},
    {0x0B99, 0x0B82, 0x0000, 0xED},
    {0x0B99, 0x0BC1, 0x0000, 0x99},
    {0x0B99, 0x0BC2, 0x0000, 0x9B},
    {0x0B9A, 0x0000, 0x0000, 0xBA},
    {0x0B9A, 0x0B82, 0x0000, 0xEE},
    {0x0B9A, 0x0BC1, 0x0000, 0xCD},
    {0x0B9A, 0x0BC2, 0x0000, 0xDD},
    {0x0B9C, 0x0000, 0x0000, 0x83},
    {0x0B9C, 0x0B82, 0x0000, 0x88},
    {0x0B9E, 0x0000, 0x0000, 0xBB},
    {0x0B9E, 0x0B82, 0x0000, 0xEF},
    {0x0B9E, 0x0BC1, 0x0000, 0x9A},
    {0x0B9E, 0x0BC2, 0x0000, 0x9C},
    {0x0B9F, 0x0000, 0x0000, 0xBC},
    {0x0B9F, 0x0B82, 0x0000, 0xF0},
    {0x0B9F, 0x0BBF, 0x0000, 0xCA},
    {0x0B9F, 0x0BC0, 0x0000, 0xCB},
    {0x0B9F, 0x0BC1, 0x0000, 0xCE},
    {0x0B9F, 0x0BC2, 0x0000, 0xDE},
    {0x0BA1, 0x0B82, 0x0000, 0xF2},
    {0x0BA3, 0x0000, 0x0000, 0xBD},
    {0x0BA3, 0x0B82, 0x0000, 0xF1},
    {0x0BA3, 0x0BC1, 0x0000, 0xCF},
    {0x0BA3, 0x0BC2, 0x0000, 0xDF},
    {0x0BA4, 0x0000, 0x0000, 0xBE},
    {0x0BA4, 0x0BC1, 0x0000, 0xD0},
    {0x0BA4, 0x0BC2, 0x0000, 0xE0},
    {0x0BA8, 0x0000, 0x0000, 0xBF},
    {0x0BA8, 0x0B82, 0x0000, 0xF3},
    {0x0BA8, 0x0BC1, 0x0000, 0xD1},
    {0x0BA8, 0x0BC2, 0x0000, 0xE1},
    {0x0BA9, 0x0000, 0x0000, 0xC9},
    {0x0BA9, 0x0B82, 0x0000, 0xFD},
    {0x0BA9, 0x0BC1, 0x0000, 0xDB},
    {0x0BA9, 0x0BC2, 0x0000, 0xEB},
    {0x0BAA, 0x0000, 0x0000, 0xC0},
    {0x0BAA, 0x0B82, 0x0000, 0xF4},
    {0x0BAA, 0x0BC1, 0x0000, 0xD2},
    {0x0BAA, 0x0BC2, 0x0000, 0xE2},
    {0x0BAE, 0x0000, 0x0000, 0xC1},
    {0x0BAE, 0x0B82, 0x0000, 0xF5},
    {0x0BAE, 0x0BC1, 0x0000, 0xD3},
    {0x0BAE, 0x0BC2, 0x0000, 0xE3},
    {0x0BAF, 0x0000, 0x0000, 0xC2},
    {0x0BAF, 0x0B82, 0x0000, 0xF6},
    {0x0BAF, 0x0BC1, 0x0000, 0xD4},
    {0x0BAF, 0x0BC2, 0x0000, 0xE4},
    {0x0BB0, 0x0000, 0x0000, 0xC3},
    {0x0BB0, 0x0B82, 0x0000, 0xF7},
    {0x0BB0, 0x0BC1, 0x0000, 0xD5},
    {0x0BB0, 0x0BC2, 0x0000, 0xE5},
    {0x0BB1, 0x0000, 0x0000, 0xC8},
    {0x0BB1, 0x0B82, 0x0000, 0xFC},
    {0x0BB1, 0x0BC1, 0x0000, 0xDA},
    {0x0BB1, 0x0BC2, 0x0000, 0xEA},
    {0x0BB2, 0x0000, 0x0000, 0xC4},
    {0x0BB2, 0x0B82, 0x0000, 0xF8},
    {0x0BB2, 0x0BC1, 0x0000, 0xD6},
    {0x0BB2, 0x0BC2, 0x0000, 0xE6},
    {0x0BB3, 0x0000, 0x0000, 0xC7},
    {0x0BB3, 0x0B82, 0x0000, 0xFB},
    {0x0BB3, 0x0BC1, 0x0000, 0xD9},
    {0x0BB3, 0x0BC2, 0x0000, 0xE9},
    {0x0BB4, 0x0000, 0x0000, 0xC6},
    {0x0BB4, 0x0B82, 0x0000, 0xFA},
    {0x0BB4, 0x0BC1, 0x0000, 0xD8},
    {0x0BB4, 0x0BC2, 0x0000, 0xE8},
    {0x0BB5, 0x0000, 0x0000, 0xC5},
    {0x0BB5, 0x0B82, 0x0000, 0xF9},
    {0x0BB5, 0x0BC1, 0x0000, 0xD7},
    {0x0BB5, 0x0BC2, 0x0000, 0xE7},
    {0x0BB7, 0x0000, 0x0000, 0x84},
    {0x0BB7, 0x0B82, 0x0000, 0x89},
    {0x0BB8, 0x0000, 0x0000, 0x85},
    {0x0BB8, 0x0B82, 0x0000, 0x8A},
    {0x0BB9, 0x0000, 0x0000, 0x86},
    {0x0BB9, 0x0B82, 0x0000, 0x8B},
    {0x0BBE, 0x0000, 0x0000, 0xA1},
    {0x0BBF, 0x0000, 0x0000, 0xA2},
    {0x0BC0, 0x0000, 0x0000, 0xA3},
    {0x0BC1, 0x0000, 0x0000, 0xA4},
    {0x0BC2, 0x0000, 0x0000, 0xA5},
    {0x0BC6, 0x0000, 0x0000, 0xA6},
    {0x0BC7, 0x0000, 0x0000, 0xA7},
    {0x0BC8, 0x0000, 0x0000, 0xA8},
    {0x0BCC, 0x0000, 0x0000, 0xAA},
    {0x0BE6, 0x0000, 0x0000, 0x80},
    {0x0BE7, 0x0000, 0x0000, 0x81},
    {0x0BE7, 0x0BB7, 0x0000, 0x87},
    {0x0BE7, 0x0BB7, 0x0B82, 0x8C},
    {0x0BE8, 0x0000, 0x0000, 0x8D},
    {0x0BE9, 0x0000, 0x0000, 0x8E},
    {0x0BEA, 0x0000, 0x0000, 0x8F},
    {0x0BEB, 0x0000, 0x0000, 0x90},
    {0x0BEC, 0x0000, 0x0000, 0x95},
    {0x0BED, 0x0000, 0x0000, 0x96},
    {0x0BEE, 0x0000, 0x0000, 0x97},
    {0x0BEF, 0x0000, 0x0000, 0x98},
    {0x0BF0, 0x0000, 0x0000, 0x9D},
    {0x0BF1, 0x0000, 0x0000, 0x9E},
    {0x0BF2, 0x0000, 0x0000, 0x9F},
    {0x2018, 0x0000, 0x0000, 0x91},
    {0x2019, 0x0000, 0x0000, 0x92},
    {0x201C, 0x0000, 0x0000, 0x93},
    {0x201C, 0x0000, 0x0000, 0x94}
};

static const ushort TsToUn [][3] = {
    // Starting at 0x80
    {0x0BE6, 0x0000, 0x0000},
    {0x0BE7, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000}, // unknown
    {0x0B9C, 0x0000, 0x0000},
    {0x0BB7, 0x0000, 0x0000},
    {0x0BB8, 0x0000, 0x0000},
    {0x0BB9, 0x0000, 0x0000},
    {0x0BE7, 0x0BB7, 0x0000},
    {0x0B9C, 0x0B82, 0x0000},
    {0x0BB7, 0x0B82, 0x0000},
    {0x0BB8, 0x0B82, 0x0000},
    {0x0BB9, 0x0B82, 0x0000},
    {0x0BE7, 0x0BB7, 0x0B82},
    {0x0BE8, 0x0000, 0x0000},
    {0x0BE9, 0x0000, 0x0000},
    {0x0BEA, 0x0000, 0x0000},
    {0x0BEB, 0x0000, 0x0000},
    {0x2018, 0x0000, 0x0000},
    {0x2019, 0x0000, 0x0000},
    {0x201C, 0x0000, 0x0000},
    {0x201C, 0x0000, 0x0000}, // two of the same??
    {0x0BEC, 0x0000, 0x0000},
    {0x0BED, 0x0000, 0x0000},
    {0x0BEE, 0x0000, 0x0000},
    {0x0BEF, 0x0000, 0x0000},
    {0x0B99, 0x0BC1, 0x0000},
    {0x0B9E, 0x0BC1, 0x0000},
    {0x0B99, 0x0BC2, 0x0000},
    {0x0B9E, 0x0BC2, 0x0000},
    {0x0BF0, 0x0000, 0x0000},
    {0x0BF1, 0x0000, 0x0000},
    {0x0BF2, 0x0000, 0x0000},
    {0x00A0, 0x0000, 0x0000},
    {0x0BBE, 0x0000, 0x0000},
    {0x0BBF, 0x0000, 0x0000},
    {0x0BC0, 0x0000, 0x0000},
    {0x0BC1, 0x0000, 0x0000},
    {0x0BC2, 0x0000, 0x0000},
    {0x0BC6, 0x0000, 0x0000},
    {0x0BC7, 0x0000, 0x0000},
    {0x0BC8, 0x0000, 0x0000},
    {0x00A9, 0x0000, 0x0000},
    {0x0BCC, 0x0000, 0x0000},
    {0x0B85, 0x0000, 0x0000},
    {0x0B86, 0x0000, 0x0000},
    {0x0B87, 0x0000, 0x0000},
    {0x0B88, 0x0000, 0x0000},
    {0x0B89, 0x0000, 0x0000},
    {0x0B8A, 0x0000, 0x0000},
    {0x0B8E, 0x0000, 0x0000},
    {0x0B8F, 0x0000, 0x0000},
    {0x0B90, 0x0000, 0x0000},
    {0x0B92, 0x0000, 0x0000},
    {0x0B93, 0x0000, 0x0000},
    {0x0B94, 0x0000, 0x0000},
    {0x0B83, 0x0000, 0x0000},
    {0x0B95, 0x0000, 0x0000},
    {0x0B99, 0x0000, 0x0000},
    {0x0B9A, 0x0000, 0x0000},
    {0x0B9E, 0x0000, 0x0000},
    {0x0B9F, 0x0000, 0x0000},
    {0x0BA3, 0x0000, 0x0000},
    {0x0BA4, 0x0000, 0x0000},
    {0x0BA8, 0x0000, 0x0000},
    {0x0BAA, 0x0000, 0x0000},
    {0x0BAE, 0x0000, 0x0000},
    {0x0BAF, 0x0000, 0x0000},
    {0x0BB0, 0x0000, 0x0000},
    {0x0BB2, 0x0000, 0x0000},
    {0x0BB5, 0x0000, 0x0000},
    {0x0BB4, 0x0000, 0x0000},
    {0x0BB3, 0x0000, 0x0000},
    {0x0BB1, 0x0000, 0x0000},
    {0x0BA9, 0x0000, 0x0000},
    {0x0B9F, 0x0BBF, 0x0000},
    {0x0B9F, 0x0BC0, 0x0000},
    {0x0B95, 0x0BC1, 0x0000},
    {0x0B9A, 0x0BC1, 0x0000},
    {0x0B9F, 0x0BC1, 0x0000},
    {0x0BA3, 0x0BC1, 0x0000},
    {0x0BA4, 0x0BC1, 0x0000},
    {0x0BA8, 0x0BC1, 0x0000},
    {0x0BAA, 0x0BC1, 0x0000},
    {0x0BAE, 0x0BC1, 0x0000},
    {0x0BAF, 0x0BC1, 0x0000},
    {0x0BB0, 0x0BC1, 0x0000},
    {0x0BB2, 0x0BC1, 0x0000},
    {0x0BB5, 0x0BC1, 0x0000},
    {0x0BB4, 0x0BC1, 0x0000},
    {0x0BB3, 0x0BC1, 0x0000},
    {0x0BB1, 0x0BC1, 0x0000},
    {0x0BA9, 0x0BC1, 0x0000},
    {0x0B95, 0x0BC2, 0x0000},
    {0x0B9A, 0x0BC2, 0x0000},
    {0x0B9F, 0x0BC2, 0x0000},
    {0x0BA3, 0x0BC2, 0x0000},
    {0x0BA4, 0x0BC2, 0x0000},
    {0x0BA8, 0x0BC2, 0x0000},
    {0x0BAA, 0x0BC2, 0x0000},
    {0x0BAE, 0x0BC2, 0x0000},
    {0x0BAF, 0x0BC2, 0x0000},
    {0x0BB0, 0x0BC2, 0x0000},
    {0x0BB2, 0x0BC2, 0x0000},
    {0x0BB5, 0x0BC2, 0x0000},
    {0x0BB4, 0x0BC2, 0x0000},
    {0x0BB3, 0x0BC2, 0x0000},
    {0x0BB1, 0x0BC2, 0x0000},
    {0x0BA9, 0x0BC2, 0x0000},
    {0x0B95, 0x0B82, 0x0000},
    {0x0B99, 0x0B82, 0x0000},
    {0x0B9A, 0x0B82, 0x0000},
    {0x0B9E, 0x0B82, 0x0000},
    {0x0B9F, 0x0B82, 0x0000},
    {0x0BA3, 0x0B82, 0x0000},
    {0x0BA1, 0x0B82, 0x0000},
    {0x0BA8, 0x0B82, 0x0000},
    {0x0BAA, 0x0B82, 0x0000},
    {0x0BAE, 0x0B82, 0x0000},
    {0x0BAF, 0x0B82, 0x0000},
    {0x0BB0, 0x0B82, 0x0000},
    {0x0BB2, 0x0B82, 0x0000},
    {0x0BB5, 0x0B82, 0x0000},
    {0x0BB4, 0x0B82, 0x0000},
    {0x0BB3, 0x0B82, 0x0000},
    {0x0BB1, 0x0B82, 0x0000},
    {0x0BA9, 0x0B82, 0x0000}
};

static int cmp(const ushort *s1, const ushort *s2, size_t len)
{
    int diff = 0;

    while (len-- && (diff = *s1++ - *s2++) == 0)
        ;

    return diff;
}

static unsigned char qt_UnicodeToTSCII(ushort u1, ushort u2, ushort u3)
{
    ushort s[3];
    s[0] = u1;
    s[1] = u2;
    s[2] = u3;

    int a = 0;  // start pos
    int b = UnToTsLast; // end pos

    // do a binary search for the composed unicode in the list
    while (a <= b) {
        int w = (a + b) / 2;
        int j = cmp(UnToTs[w], s, 3);

        if (j == 0)
            // found it
            return UnToTs[w][3];

        if (j < 0)
            a = w + 1;
        else
            b = w - 1;
    }

    return 0;
}

static unsigned int qt_TSCIIToUnicode(uint code, uint *s)
{
    int len = 0;
    for (int i = 0; i < 3; i++) {
        uint u = TsToUn[code & 0x7f][i];
        s[i] = u;
        if (s[i]) len = i + 1;
    }

    return len;
}

QT_END_NAMESPACE

#endif // QT_NO_CODECS
