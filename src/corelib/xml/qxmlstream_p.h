/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the either Technology Preview License Agreement or the
** Beta Release License Agreement.
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
** contact the sales department at http://qt.nokia.com/contact.
** $QT_END_LICENSE$
**
****************************************************************************/

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of other Qt classes.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#ifndef QXMLSTREAM_P_H
#define QXMLSTREAM_P_H

class QXmlStreamReader_Table
{
public:
  enum {
    EOF_SYMBOL = 0,
    AMPERSAND = 5,
    ANY = 41,
    ATTLIST = 31,
    BANG = 25,
    CDATA = 47,
    CDATA_START = 28,
    COLON = 17,
    COMMA = 19,
    DASH = 20,
    DBLQUOTE = 8,
    DIGIT = 27,
    DOCTYPE = 29,
    DOT = 23,
    ELEMENT = 30,
    EMPTY = 40,
    ENTITIES = 51,
    ENTITY = 32,
    ENTITY_DONE = 45,
    EQ = 14,
    ERROR = 43,
    FIXED = 39,
    HASH = 6,
    ID = 48,
    IDREF = 49,
    IDREFS = 50,
    IMPLIED = 38,
    LANGLE = 3,
    LBRACK = 9,
    LETTER = 26,
    LPAREN = 11,
    NDATA = 36,
    NMTOKEN = 52,
    NMTOKENS = 53,
    NOTATION = 33,
    NOTOKEN = 1,
    PARSE_ENTITY = 44,
    PCDATA = 42,
    PERCENT = 15,
    PIPE = 13,
    PLUS = 21,
    PUBLIC = 35,
    QUESTIONMARK = 24,
    QUOTE = 7,
    RANGLE = 4,
    RBRACK = 10,
    REQUIRED = 37,
    RPAREN = 12,
    SEMICOLON = 18,
    SHIFT_THERE = 56,
    SLASH = 16,
    SPACE = 2,
    STAR = 22,
    SYSTEM = 34,
    UNRESOLVED_ENTITY = 46,
    VERSION = 55,
    XML = 54,

    ACCEPT_STATE = 416,
    RULE_COUNT = 269,
    STATE_COUNT = 427,
    TERMINAL_COUNT = 57,
    NON_TERMINAL_COUNT = 84,

    GOTO_INDEX_OFFSET = 427,
    GOTO_INFO_OFFSET = 1017,
    GOTO_CHECK_OFFSET = 1017
  };

  static const char  *const spell [];
  static const int            lhs [];
  static const int            rhs [];
  static const int   goto_default [];
  static const int action_default [];
  static const int   action_index [];
  static const int    action_info [];
  static const int   action_check [];

  static inline int nt_action (int state, int nt)
  {
    const int *const goto_index = &action_index [GOTO_INDEX_OFFSET];
    const int *const goto_check = &action_check [GOTO_CHECK_OFFSET];

    const int yyn = goto_index [state] + nt;

    if (yyn < 0 || goto_check [yyn] != nt)
      return goto_default [nt];

    const int *const goto_info = &action_info [GOTO_INFO_OFFSET];
    return goto_info [yyn];
  }

  static inline int t_action (int state, int token)
  {
    const int yyn = action_index [state] + token;

    if (yyn < 0 || action_check [yyn] != token)
      return - action_default [state];

    return action_info [yyn];
  }
};


const char *const QXmlStreamReader_Table::spell [] = {
  "end of file", 0, " ", "<", ">", "&", "#", "\'", "\"", "[", 
  "]", "(", ")", "|", "=", "%", "/", ":", ";", ",", 
  "-", "+", "*", ".", "?", "!", "[a-zA-Z]", "[0-9]", "[CDATA[", "DOCTYPE", 
  "ELEMENT", "ATTLIST", "ENTITY", "NOTATION", "SYSTEM", "PUBLIC", "NDATA", "REQUIRED", "IMPLIED", "FIXED", 
  "EMPTY", "ANY", "PCDATA", 0, 0, 0, 0, "CDATA", "ID", "IDREF", 
  "IDREFS", "ENTITIES", "NMTOKEN", "NMTOKENS", "<?xml", "version", 0};

const int QXmlStreamReader_Table::lhs [] = {
  57, 57, 59, 59, 59, 59, 59, 59, 59, 59, 
  67, 68, 64, 72, 72, 72, 75, 66, 66, 66, 
  66, 79, 78, 80, 80, 80, 80, 80, 80, 81, 
  81, 81, 81, 81, 81, 81, 87, 83, 88, 88, 
  88, 88, 91, 92, 93, 93, 93, 93, 94, 94, 
  96, 96, 96, 97, 97, 98, 98, 99, 99, 100, 
  100, 89, 89, 95, 90, 101, 101, 103, 103, 103, 
  103, 103, 103, 103, 103, 103, 103, 104, 105, 105, 
  105, 105, 107, 108, 109, 109, 84, 84, 110, 110, 
  112, 112, 85, 85, 85, 65, 65, 76, 114, 63, 
  115, 116, 86, 86, 86, 117, 117, 117, 117, 117, 
  117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 
  117, 117, 117, 117, 117, 117, 117, 117, 118, 118, 
  119, 119, 119, 119, 119, 119, 119, 119, 122, 70, 
  70, 70, 70, 123, 124, 123, 124, 123, 124, 123, 
  124, 126, 126, 126, 126, 126, 126, 126, 126, 126, 
  126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 
  126, 126, 126, 125, 73, 113, 113, 113, 113, 127, 
  128, 127, 128, 127, 128, 127, 128, 129, 129, 129, 
  129, 129, 129, 129, 129, 129, 129, 129, 129, 129, 
  129, 129, 129, 129, 129, 129, 129, 129, 129, 129, 
  129, 129, 106, 106, 106, 106, 131, 132, 131, 132, 
  131, 131, 132, 132, 133, 133, 133, 133, 135, 71, 
  71, 71, 136, 136, 137, 62, 60, 61, 138, 121, 
  82, 130, 134, 120, 139, 139, 139, 139, 58, 58, 
  58, 58, 58, 58, 58, 58, 58, 58, 74, 69, 
  69, 77, 111, 102, 102, 102, 102, 102, 140};

const int QXmlStreamReader_Table:: rhs[] = {
  2, 1, 4, 2, 2, 2, 2, 2, 2, 0, 
  1, 1, 9, 2, 4, 0, 4, 4, 6, 6, 
  4, 1, 3, 1, 1, 1, 2, 2, 2, 1, 
  1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 
  1, 1, 1, 2, 1, 1, 1, 0, 2, 2, 
  2, 6, 6, 1, 5, 1, 5, 3, 5, 0, 
  1, 6, 8, 4, 2, 1, 5, 1, 1, 1, 
  1, 1, 1, 1, 1, 6, 7, 1, 2, 2, 
  1, 4, 3, 3, 1, 2, 5, 6, 4, 6, 
  3, 5, 5, 3, 4, 4, 5, 2, 3, 2, 
  2, 4, 5, 5, 7, 1, 1, 1, 1, 1, 
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
  2, 2, 2, 2, 1, 1, 1, 1, 1, 2, 
  2, 3, 3, 2, 2, 2, 2, 1, 1, 1, 
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
  1, 1, 1, 1, 1, 2, 2, 3, 3, 2, 
  2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
  1, 1, 2, 2, 3, 3, 2, 2, 2, 2, 
  1, 1, 1, 1, 1, 1, 1, 1, 5, 0, 
  1, 3, 1, 3, 2, 4, 3, 5, 1, 3, 
  3, 3, 3, 4, 1, 1, 2, 2, 2, 4, 
  2, 2, 2, 2, 2, 2, 2, 0, 1, 0, 
  1, 1, 1, 1, 1, 1, 1, 1, 2};

const int QXmlStreamReader_Table::action_default [] = {
  10, 258, 0, 2, 1, 0, 124, 116, 118, 119, 
  126, 128, 122, 11, 113, 107, 0, 108, 127, 110, 
  114, 112, 120, 123, 125, 106, 109, 111, 117, 115, 
  130, 121, 239, 12, 253, 135, 249, 252, 0, 129, 
  139, 256, 16, 251, 137, 136, 0, 255, 138, 258, 
  230, 257, 254, 0, 0, 263, 0, 246, 245, 0, 
  248, 247, 244, 240, 98, 262, 0, 235, 0, 0, 
  259, 96, 97, 100, 0, 131, 133, 132, 134, 0, 
  0, 260, 0, 0, 175, 0, 172, 164, 166, 167, 
  141, 153, 170, 161, 155, 156, 152, 158, 162, 160, 
  168, 171, 151, 154, 157, 159, 165, 163, 173, 169, 
  149, 174, 0, 143, 147, 145, 150, 140, 148, 0, 
  146, 142, 144, 0, 15, 14, 261, 0, 22, 21, 
  260, 0, 0, 20, 0, 0, 31, 36, 30, 0, 
  32, 260, 0, 33, 0, 24, 0, 34, 0, 26, 
  35, 25, 0, 241, 40, 39, 260, 42, 48, 260, 
  41, 0, 43, 260, 48, 260, 0, 260, 0, 48, 
  0, 47, 45, 46, 50, 51, 260, 260, 0, 56, 
  260, 53, 260, 0, 57, 0, 54, 260, 52, 260, 
  0, 55, 64, 0, 260, 60, 260, 0, 58, 61, 
  62, 0, 260, 0, 0, 59, 63, 44, 49, 65, 
  0, 38, 0, 0, 260, 0, 93, 94, 0, 0, 
  0, 0, 260, 0, 209, 200, 202, 204, 177, 189, 
  207, 198, 192, 190, 193, 188, 195, 197, 205, 208, 
  187, 191, 194, 196, 201, 199, 203, 206, 210, 212, 
  211, 185, 0, 0, 242, 179, 183, 181, 0, 0, 
  92, 186, 176, 184, 0, 182, 178, 180, 91, 0, 
  95, 0, 0, 0, 0, 0, 260, 85, 260, 0, 
  261, 0, 86, 0, 88, 68, 73, 72, 69, 70, 
  71, 260, 74, 75, 0, 0, 0, 268, 267, 265, 
  266, 264, 66, 260, 0, 260, 0, 0, 67, 76, 
  260, 0, 260, 0, 0, 77, 0, 78, 0, 81, 
  84, 0, 0, 214, 224, 223, 0, 226, 228, 227, 
  225, 0, 243, 216, 220, 218, 222, 213, 221, 0, 
  219, 215, 217, 0, 80, 79, 0, 82, 0, 83, 
  87, 99, 0, 37, 0, 0, 0, 0, 90, 89, 
  0, 102, 23, 27, 29, 28, 0, 0, 260, 261, 
  0, 260, 0, 105, 104, 260, 0, 103, 101, 0, 
  0, 18, 260, 17, 0, 19, 0, 0, 250, 0, 
  260, 0, 238, 0, 231, 237, 0, 236, 233, 260, 
  260, 261, 232, 234, 0, 260, 0, 229, 260, 0, 
  260, 0, 230, 0, 0, 13, 269, 9, 5, 8, 
  4, 0, 7, 258, 6, 0, 3};

const int QXmlStreamReader_Table::goto_default [] = {
  2, 4, 3, 49, 388, 43, 37, 52, 47, 41, 
  249, 53, 127, 84, 393, 81, 85, 126, 42, 46, 
  169, 130, 131, 146, 145, 149, 138, 136, 140, 147, 
  139, 159, 160, 157, 168, 167, 209, 165, 164, 166, 
  187, 180, 196, 200, 303, 302, 295, 321, 320, 319, 
  279, 277, 278, 142, 56, 141, 222, 38, 34, 148, 
  39, 48, 40, 248, 45, 36, 119, 112, 330, 111, 
  264, 252, 251, 250, 339, 326, 325, 329, 398, 399, 
  50, 51, 59, 0};

const int QXmlStreamReader_Table::action_index [] = {
  -21, -57, 33, 119, 960, 70, -57, -57, -57, -57, 
  -57, -57, -57, -57, -57, -57, 105, -57, -57, -57, 
  -57, -57, -57, -57, -57, -57, -57, -57, -57, -57, 
  -57, -57, -57, -57, -57, -57, -57, -57, 40, -57, 
  795, -57, 47, -57, -57, -57, 107, -57, -57, -57, 
  84, -57, -57, -38, 80, -57, 12, -57, -57, 97, 
  -57, -57, -57, -57, -57, -57, 13, -57, 56, 34, 
  -57, -57, -57, -57, 51, -57, -57, -57, -57, 53, 
  57, 84, 300, 255, -57, 84, -57, -57, -57, -57, 
  -57, -57, -57, -57, -57, -57, -57, -57, -57, -57, 
  -57, -57, -57, -57, -57, -57, -57, -57, -57, -57, 
  -57, -57, 355, -57, -57, -57, -57, -57, -57, 326, 
  -57, -57, -57, 48, -57, -57, -57, 50, -57, -57, 
  84, 155, 32, -57, 38, 22, -57, -57, -57, 115, 
  -57, 35, 156, -57, 173, -57, 245, -57, 44, -57, 
  -57, -57, 16, -57, -57, -57, 29, -57, 116, 29, 
  -57, 133, -57, 29, 129, 84, 15, 29, -22, 121, 
  74, -57, -57, -57, -57, 82, 29, 29, 88, -57, 
  29, 7, 29, 86, -57, 83, -57, 27, 19, 26, 
  94, -57, -57, 106, 29, 3, 29, -8, -57, -57, 
  -57, 104, 29, -6, -7, -57, -57, -57, -57, -57, 
  17, -57, -2, 11, 29, 18, -57, -57, 850, 65, 
  465, 67, 84, 135, -57, -57, -57, -57, -57, -57, 
  -57, -57, -57, -57, -57, -57, -57, -57, -57, -57, 
  -57, -57, -57, -57, -57, -57, -57, -57, -57, -57, 
  -57, -57, 630, 24, -57, -57, -57, -57, 84, 76, 
  -57, -57, -57, -57, 740, -57, -57, -57, -57, 39, 
  -57, 23, 21, 14, 78, 22, 84, -57, 84, 184, 
  20, 31, -57, 41, -57, -57, -57, -57, -57, -57, 
  -57, 84, -57, -57, 36, 126, 162, -57, -57, -57, 
  -57, -57, -57, 29, 79, 29, 29, 160, -57, -57, 
  29, 145, 29, 75, 29, -57, 575, -57, 410, -57, 
  -57, 110, 64, -57, -57, -57, 685, -57, -57, -57, 
  -57, -17, -57, -57, -57, -57, -57, -57, -57, 520, 
  -57, -57, -57, 29, -57, -57, 61, -57, 29, -57, 
  -57, -57, 29, -57, 29, 29, -15, 29, -57, -57, 
  29, -57, -57, -57, -57, -57, 95, 43, 29, 45, 
  9, 29, 10, -57, -57, 29, 2, -57, -57, -24, 
  190, -57, 29, -57, 1, -57, 905, 150, -57, -26, 
  29, 0, -57, 109, -26, -57, 8, -57, -57, 29, 
  29, -19, -57, -57, -11, 29, 59, -57, 29, -5, 
  29, 103, 29, -16, 6, -57, -57, -57, -57, -57, 
  -57, 69, -57, -57, -57, 905, -57, 

  -84, -84, -84, 204, 75, -84, -84, -84, -84, -84, 
  -84, -84, -84, -84, -84, -84, 7, -84, -84, -84, 
  -84, -84, -84, -84, -84, -84, -84, -84, -84, -84, 
  -84, -84, -84, -84, -84, -84, -84, -84, -84, -84, 
  101, -84, -84, -84, -84, -84, -84, -84, -84, 64, 
  54, -84, -84, -84, -84, -84, -84, -84, -84, -84, 
  -84, -84, -84, -84, -84, -84, 68, -84, 30, -84, 
  -84, -84, -84, -84, -84, -84, -84, -84, -84, -84, 
  32, -84, -16, -7, -84, 42, -84, -84, -84, -84, 
  -84, -84, -84, -84, -84, -84, -84, -84, -84, -84, 
  -84, -84, -84, -84, -84, -84, -84, -84, -84, -84, 
  -84, -84, 45, -84, -84, -84, -84, -84, -84, 44, 
  -84, -84, -84, 33, -84, -84, -84, -84, -84, -84, 
  36, 108, -84, -84, -84, 69, -84, -84, -84, 62, 
  -84, 63, -84, -84, -84, -84, 118, -84, -84, -84, 
  -84, -84, -84, -84, -84, -84, -2, -84, -84, -10, 
  -84, -84, -84, 25, -21, 11, -84, 20, -84, -25, 
  -84, -84, -84, -84, -84, -84, 1, 2, -36, -84, 
  -9, -84, 5, -13, -84, -8, -84, 6, -84, 8, 
  12, -84, -84, -84, 23, -84, 4, -1, -84, -84, 
  -84, -84, 0, -84, -14, -84, -84, -84, -84, -84, 
  -84, -84, 55, -84, 58, -84, -84, -84, -84, 53, 
  47, 123, 67, 66, -84, -84, -84, -84, -84, -84, 
  -84, -84, -84, -84, -84, -84, -84, -84, -84, -84, 
  -84, -84, -84, -84, -84, -84, -84, -84, -84, -84, 
  -84, -84, -15, -84, -84, -84, -84, -84, 41, 40, 
  -84, -84, -84, -84, -46, -84, -84, -84, -84, -84, 
  -84, 35, -84, 34, 37, 18, 70, -84, 89, -84, 
  43, -84, -84, -84, -84, -84, -84, -84, -84, -84, 
  -84, 48, -84, -84, -84, -84, -84, -84, -84, -84, 
  -84, -84, -84, 31, -84, 29, 27, 17, -84, -84, 
  38, 24, 39, -84, 49, -84, 71, -84, 93, -84, 
  -84, -84, -12, -84, -84, -84, 94, -84, -84, -84, 
  -84, -84, -84, -84, -84, -84, -84, -84, -84, 78, 
  -84, -84, -84, 50, -84, -84, 46, -84, 56, -84, 
  -84, -84, 60, -84, 61, 59, 51, 57, -84, -84, 
  14, -84, -84, -84, -84, -84, -11, -6, 72, -5, 
  -84, -3, -84, -84, -84, 52, -84, -84, -84, -20, 
  77, -84, 21, -84, -84, -84, 76, 16, -84, 19, 
  26, -84, -84, -84, 10, -84, -84, -84, -84, 80, 
  13, 73, -84, -84, -84, 22, -27, -84, 9, -84, 
  28, 15, 82, -84, -84, -84, -84, -84, -84, -84, 
  -84, -84, -84, 3, -84, 98, -84};

const int QXmlStreamReader_Table::action_info [] = {
  65, 332, 65, 405, 392, 385, 377, 65, 414, 410, 
  415, 55, 397, 374, 373, 217, 206, 408, 65, 65, 
  207, 211, 216, 1, 55, 199, 182, 192, 70, 70, 
  63, 70, 189, 416, 153, 350, 133, 70, 72, 55, 
  65, 351, 254, 270, 73, 284, 65, 310, 55, 65, 
  83, 82, 83, 82, 129, 83, 82, 54, 70, 128, 
  83, 82, 66, 64, 83, 82, 318, 316, 318, 316, 
  54, 212, 83, 82, 83, 82, 54, 55, 367, 366, 
  69, 80, 79, 83, 82, 163, 70, 314, 305, 272, 
  55, 306, 305, 354, 163, 177, 55, 163, 379, 163, 
  65, 176, 83, 82, 55, 163, 58, 57, 0, 65, 
  83, 82, 65, 395, 65, 62, 203, 202, 195, 194, 
  65, 417, 16, 61, 60, 396, 156, 272, 0, 66, 
  64, 65, 317, 318, 316, 378, 379, 171, 173, 162, 
  172, 54, 171, 173, 163, 172, 0, 345, 344, 343, 
  171, 173, 0, 172, 0, 155, 154, 70, 134, 65, 
  0, 55, 297, 220, 218, 298, 389, 0, 300, 0, 
  135, 301, 299, 33, 66, 64, 65, 297, 0, 297, 
  298, 0, 298, 300, 0, 300, 301, 299, 301, 299, 
  221, 219, 70, 272, 381, 291, 0, 0, 0, 128, 
  13, 0, 0, 273, 271, 274, 275, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 287, 294, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 285, 288, 289, 290, 286, 292, 293, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 70, 134, 0, 
  0, 0, 0, 0, 0, 362, 0, 108, 0, 103, 
  135, 94, 117, 116, 95, 104, 97, 105, 99, 93, 
  98, 107, 87, 106, 88, 89, 100, 109, 92, 101, 
  86, 96, 91, 0, 0, 0, 0, 0, 0, 0, 
  13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 108, 0, 103, 0, 94, 102, 90, 95, 
  104, 97, 105, 99, 93, 98, 107, 87, 106, 88, 
  89, 100, 109, 92, 101, 86, 96, 91, 108, 0, 
  103, 0, 94, 121, 120, 95, 104, 97, 105, 99, 
  93, 98, 107, 87, 106, 88, 89, 100, 109, 92, 
  101, 86, 96, 91, 0, 0, 0, 108, 0, 103, 
  0, 94, 114, 113, 95, 104, 97, 105, 99, 93, 
  98, 107, 87, 106, 88, 89, 100, 109, 92, 101, 
  86, 96, 91, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 108, 0, 103, 322, 94, 337, 336, 95, 
  104, 97, 105, 99, 93, 98, 107, 87, 106, 88, 
  89, 100, 109, 92, 101, 86, 96, 91, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 13, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 246, 233, 241, 
  223, 232, 262, 261, 234, 242, 236, 243, 237, 231, 
  0, 245, 225, 244, 226, 227, 238, 247, 230, 239, 
  224, 235, 229, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 108, 0, 103, 322, 94, 341, 340, 95, 
  104, 97, 105, 99, 93, 98, 107, 87, 106, 88, 
  89, 100, 109, 92, 101, 86, 96, 91, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 13, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 108, 0, 103, 
  322, 94, 324, 323, 95, 104, 97, 105, 99, 93, 
  98, 107, 87, 106, 88, 89, 100, 109, 92, 101, 
  86, 96, 91, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 246, 233, 241, 223, 232, 256, 255, 234, 
  242, 236, 243, 237, 231, 0, 245, 225, 244, 226, 
  227, 238, 247, 230, 239, 224, 235, 229, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 13, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 108, 0, 103, 
  322, 94, 334, 333, 95, 104, 97, 105, 99, 93, 
  98, 107, 87, 106, 88, 89, 100, 109, 92, 101, 
  86, 96, 91, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 246, 233, 241, 223, 232, 266, 265, 234, 
  242, 236, 243, 237, 231, 0, 245, 225, 244, 226, 
  227, 238, 247, 230, 239, 224, 235, 229, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 13, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 30, 0, 25, 
  74, 15, 24, 10, 17, 26, 19, 27, 21, 14, 
  20, 29, 7, 28, 8, 9, 22, 31, 12, 23, 
  6, 18, 11, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 246, 233, 241, 223, 232, 240, 228, 234, 
  242, 236, 243, 237, 231, 0, 245, 225, 244, 226, 
  227, 238, 247, 230, 239, 224, 235, 229, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 13, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 30, 387, 25, 
  5, 15, 24, 10, 17, 26, 19, 27, 21, 14, 
  20, 29, 7, 28, 8, 9, 22, 31, 12, 23, 
  6, 18, 11, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  13, 32, 0, 0, 0, 0, 0, 0, 0, 33, 
  0, 0, 30, 16, 25, 5, 15, 24, 10, 17, 
  26, 19, 27, 21, 14, 20, 29, 7, 28, 8, 
  9, 22, 31, 12, 23, 6, 18, 11, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 13, 32, 0, 0, 0, 
  0, 0, 0, 0, 33, 0, 0, 

  380, 179, 210, 181, 425, 368, 205, 375, 371, 372, 
  161, 208, 204, 178, 185, 174, 201, 183, 188, 198, 
  190, 409, 407, 175, 184, 404, 267, 67, 412, 186, 
  400, 361, 193, 384, 406, 197, 67, 170, 391, 390, 
  411, 307, 331, 304, 309, 125, 124, 71, 132, 191, 
  311, 313, 110, 260, 352, 276, 0, 257, 259, 123, 
  296, 118, 308, 348, 376, 386, 315, 346, 312, 258, 
  215, 394, 360, 349, 358, 213, 359, 353, 356, 269, 
  0, 328, 281, 0, 370, 44, 44, 280, 328, 369, 
  0, 355, 402, 400, 383, 347, 413, 401, 382, 394, 
  158, 283, 426, 328, 328, 357, 280, 0, 44, 214, 
  0, 76, 122, 115, 137, 0, 150, 0, 143, 263, 
  253, 0, 68, 152, 137, 151, 150, 144, 143, 0, 
  0, 0, 0, 0, 327, 365, 268, 144, 35, 35, 
  282, 327, 363, 364, 0, 0, 0, 0, 0, 0, 
  0, 403, 0, 0, 342, 0, 327, 327, 0, 0, 
  0, 35, 78, 0, 75, 77, 0, 0, 0, 338, 
  335, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 423, 0, 420, 
  418, 424, 422, 419, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 421, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0};

const int QXmlStreamReader_Table::action_check [] = {
  26, 18, 26, 14, 4, 4, 4, 26, 24, 14, 
  4, 26, 4, 4, 4, 4, 22, 55, 26, 26, 
  42, 4, 4, 44, 26, 22, 19, 12, 2, 2, 
  18, 2, 13, 0, 18, 4, 4, 2, 4, 26, 
  26, 20, 18, 4, 4, 4, 26, 11, 26, 26, 
  7, 8, 7, 8, 4, 7, 8, 6, 2, 9, 
  7, 8, 24, 25, 7, 8, 7, 8, 7, 8, 
  6, 36, 7, 8, 7, 8, 6, 26, 34, 35, 
  24, 34, 35, 7, 8, 11, 2, 12, 13, 20, 
  26, 12, 13, 15, 11, 13, 26, 11, 29, 11, 
  26, 19, 7, 8, 26, 11, 26, 27, -1, 26, 
  7, 8, 26, 4, 26, 18, 12, 13, 12, 13, 
  26, 2, 3, 26, 27, 16, 11, 20, -1, 24, 
  25, 26, 6, 7, 8, 28, 29, 21, 22, 6, 
  24, 6, 21, 22, 11, 24, -1, 37, 38, 39, 
  21, 22, -1, 24, -1, 40, 41, 2, 3, 26, 
  -1, 26, 17, 7, 8, 20, 16, -1, 23, -1, 
  15, 26, 27, 54, 24, 25, 26, 17, -1, 17, 
  20, -1, 20, 23, -1, 23, 26, 27, 26, 27, 
  34, 35, 2, 20, 4, 11, -1, -1, -1, 9, 
  45, -1, -1, 30, 31, 32, 33, -1, -1, -1, 
  -1, -1, -1, -1, -1, -1, 32, 33, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
  -1, 47, 48, 49, 50, 51, 52, 53, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, 2, 3, -1, 
  -1, -1, -1, -1, -1, 10, -1, 2, -1, 4, 
  15, 6, 7, 8, 9, 10, 11, 12, 13, 14, 
  15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 
  25, 26, 27, -1, -1, -1, -1, -1, -1, -1, 
  45, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
  -1, -1, 2, -1, 4, -1, 6, 7, 8, 9, 
  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 
  20, 21, 22, 23, 24, 25, 26, 27, 2, -1, 
  4, -1, 6, 7, 8, 9, 10, 11, 12, 13, 
  14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 
  24, 25, 26, 27, -1, -1, -1, 2, -1, 4, 
  -1, 6, 7, 8, 9, 10, 11, 12, 13, 14, 
  15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 
  25, 26, 27, -1, -1, -1, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
  -1, -1, 2, -1, 4, 5, 6, 7, 8, 9, 
  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 
  20, 21, 22, 23, 24, 25, 26, 27, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, 45, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, 2, 3, 4, 
  5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 
  -1, 16, 17, 18, 19, 20, 21, 22, 23, 24, 
  25, 26, 27, -1, -1, -1, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
  45, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
  -1, -1, 2, -1, 4, 5, 6, 7, 8, 9, 
  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 
  20, 21, 22, 23, 24, 25, 26, 27, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, 45, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, 2, -1, 4, 
  5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 
  15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 
  25, 26, 27, -1, -1, -1, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
  45, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
  -1, -1, 2, 3, 4, 5, 6, 7, 8, 9, 
  10, 11, 12, 13, 14, -1, 16, 17, 18, 19, 
  20, 21, 22, 23, 24, 25, 26, 27, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, 45, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, 2, -1, 4, 
  5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 
  15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 
  25, 26, 27, -1, -1, -1, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
  45, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
  -1, -1, 2, 3, 4, 5, 6, 7, 8, 9, 
  10, 11, 12, 13, 14, -1, 16, 17, 18, 19, 
  20, 21, 22, 23, 24, 25, 26, 27, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, 45, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, 2, -1, 4, 
  5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 
  15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 
  25, 26, 27, -1, -1, -1, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
  45, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
  -1, -1, 2, 3, 4, 5, 6, 7, 8, 9, 
  10, 11, 12, 13, 14, -1, 16, 17, 18, 19, 
  20, 21, 22, 23, 24, 25, 26, 27, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, 45, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, 2, 3, 4, 
  5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 
  15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 
  25, 26, 27, -1, -1, -1, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
  45, 46, -1, -1, -1, -1, -1, -1, -1, 54, 
  -1, -1, 2, 3, 4, 5, 6, 7, 8, 9, 
  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 
  20, 21, 22, 23, 24, 25, 26, 27, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, 45, 46, -1, -1, -1, 
  -1, -1, -1, -1, 54, -1, -1, 

  20, 37, 12, 12, 1, 16, 20, 13, 13, 12, 
  12, 36, 12, 12, 12, 36, 12, 12, 12, 20, 
  12, 12, 49, 12, 37, 12, 72, 20, 13, 37, 
  20, 17, 12, 12, 12, 12, 20, 12, 12, 20, 
  12, 12, 54, 12, 17, 13, 13, 17, 12, 37, 
  12, 12, 68, 13, 20, 20, -1, 72, 17, 17, 
  12, 68, 45, 20, 12, 1, 17, 17, 44, 16, 
  12, 17, 54, 17, 17, 12, 17, 17, 17, 12, 
  -1, 10, 12, -1, 12, 10, 10, 17, 10, 17, 
  -1, 54, 12, 20, 17, 49, 14, 17, 21, 17, 
  38, 12, 4, 10, 10, 54, 17, -1, 10, 54, 
  -1, 10, 68, 68, 6, -1, 8, -1, 10, 72, 
  54, -1, 54, 54, 6, 17, 8, 19, 10, -1, 
  -1, -1, -1, -1, 63, 17, 13, 19, 63, 63, 
  51, 63, 24, 25, -1, -1, -1, -1, -1, -1, 
  -1, 78, -1, -1, 76, -1, 63, 63, -1, -1, 
  -1, 63, 61, -1, 63, 64, -1, -1, -1, 76, 
  76, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, 3, -1, 5, 
  6, 7, 8, 9, -1, -1, -1, -1, -1, -1, 
  -1, -1, -1, 19, -1, -1, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, -1};


template <typename T> class QXmlStreamSimpleStack {
    T *data;
    int tos, cap;
public:
    inline QXmlStreamSimpleStack():data(0), tos(-1), cap(0){}
    inline ~QXmlStreamSimpleStack(){ if (data) qFree(data); }

    inline void reserve(int extraCapacity) {
        if (tos + extraCapacity + 1 > cap) {
            cap = qMax(tos + extraCapacity + 1, cap << 1 );
            data = reinterpret_cast<T *>(qRealloc(data, cap * sizeof(T)));
        }
    }

    inline T &push() { reserve(1); return data[++tos]; }
    inline T &rawPush() { return data[++tos]; }
    inline const T &top() const { return data[tos]; }
    inline T &top() { return data[tos]; }
    inline T &pop() { return data[tos--]; }
    inline T &operator[](int index) { return data[index]; }
    inline const T &at(int index) const { return data[index]; }
    inline int size() const { return tos + 1; }
    inline void resize(int s) { tos = s - 1; }
    inline bool isEmpty() const { return tos < 0; }
    inline void clear() { tos = -1; }
};


class QXmlStream
{
    Q_DECLARE_TR_FUNCTIONS(QXmlStream)
};

class QXmlStreamPrivateTagStack {
public:
    struct NamespaceDeclaration
    {
        QStringRef prefix;
        QStringRef namespaceUri;
    };

    struct Tag
    {
        QStringRef name;
        QStringRef qualifiedName;
        NamespaceDeclaration namespaceDeclaration;
        int tagStackStringStorageSize;
        int namespaceDeclarationsSize;
    };


    QXmlStreamPrivateTagStack();
    QXmlStreamSimpleStack<NamespaceDeclaration> namespaceDeclarations;
    QString tagStackStringStorage;
    int tagStackStringStorageSize;
    bool tagsDone;

    inline QStringRef addToStringStorage(const QStringRef &s) {
        int pos = tagStackStringStorageSize;
	int sz = s.size();
	if (pos != tagStackStringStorage.size())
	    tagStackStringStorage.resize(pos);
        tagStackStringStorage.insert(pos, s.unicode(), sz);
        tagStackStringStorageSize += sz;
        return QStringRef(&tagStackStringStorage, pos, sz);
    }
    inline QStringRef addToStringStorage(const QString &s) {
        int pos = tagStackStringStorageSize;
	int sz = s.size();
	if (pos != tagStackStringStorage.size())
	    tagStackStringStorage.resize(pos);
        tagStackStringStorage.insert(pos, s.unicode(), sz);
        tagStackStringStorageSize += sz;
        return QStringRef(&tagStackStringStorage, pos, sz);
    }

    QXmlStreamSimpleStack<Tag> tagStack;


    inline Tag &tagStack_pop() {
        Tag& tag = tagStack.pop();
        tagStackStringStorageSize = tag.tagStackStringStorageSize;
        namespaceDeclarations.resize(tag.namespaceDeclarationsSize);
        tagsDone = tagStack.isEmpty();
        return tag;
    }
    inline Tag &tagStack_push() {
        Tag &tag = tagStack.push();
        tag.tagStackStringStorageSize = tagStackStringStorageSize;
        tag.namespaceDeclarationsSize = namespaceDeclarations.size();
        return tag;
    }
};


class QXmlStreamEntityResolver;

class QXmlStreamReaderPrivate : public QXmlStreamReader_Table, public QXmlStreamPrivateTagStack{
    QXmlStreamReader *q_ptr;
    Q_DECLARE_PUBLIC(QXmlStreamReader)
public:
    QXmlStreamReaderPrivate(QXmlStreamReader *q);
    ~QXmlStreamReaderPrivate();
    void init();

    QByteArray rawReadBuffer;
    QByteArray dataBuffer;
    uchar firstByte;
    qint64 nbytesread;
    QString readBuffer;
    int readBufferPos;
    QXmlStreamSimpleStack<uint> putStack;
    struct Entity {
        Entity(const QString& str = QString())
            :value(str), external(false), unparsed(false), literal(false),
             hasBeenParsed(false), isCurrentlyReferenced(false){}
        static inline Entity createLiteral(const QString &entity)
            { Entity result(entity); result.literal = result.hasBeenParsed = true; return result; }
        QString value;
        uint external : 1;
        uint unparsed : 1;
        uint literal : 1;
        uint hasBeenParsed : 1;
        uint isCurrentlyReferenced : 1;
    };
    QHash<QString, Entity> entityHash;
    QHash<QString, Entity> parameterEntityHash;
    QXmlStreamSimpleStack<Entity *>entityReferenceStack;
    inline bool referenceEntity(Entity &entity) {
        if (entity.isCurrentlyReferenced) {
            raiseWellFormedError(QXmlStream::tr("Recursive entity detected."));
            return false;
        }
        entity.isCurrentlyReferenced = true;
        entityReferenceStack.push() = &entity;
        injectToken(ENTITY_DONE);
        return true;
    }


    QIODevice *device;
    bool deleteDevice;
#ifndef QT_NO_TEXTCODEC
    QTextCodec *codec;
    QTextDecoder *decoder;
#endif
    bool atEnd;

    /*!
      \sa setType()
     */
    QXmlStreamReader::TokenType type;
    QXmlStreamReader::Error error;
    QString errorString;
    QString unresolvedEntity;

    qint64 lineNumber, lastLineStart, characterOffset;


    void write(const QString &);
    void write(const char *);


    QXmlStreamAttributes attributes;
    QStringRef namespaceForPrefix(const QStringRef &prefix);
    void resolveTag();
    void resolvePublicNamespaces();
    void resolveDtd();
    uint resolveCharRef(int symbolIndex);
    bool checkStartDocument();
    void startDocument();
    void parseError();
    void checkPublicLiteral(const QStringRef &publicId);

    bool scanDtd;
    QStringRef lastAttributeValue;
    bool lastAttributeIsCData;
    struct DtdAttribute {
        QStringRef tagName;
        QStringRef attributeQualifiedName;
        QStringRef attributePrefix;
        QStringRef attributeName;
        QStringRef defaultValue;
        bool isCDATA;
        bool isNamespaceAttribute;
    };
    QXmlStreamSimpleStack<DtdAttribute> dtdAttributes;
    struct NotationDeclaration {
        QStringRef name;
        QStringRef publicId;
        QStringRef systemId;
    };
    QXmlStreamSimpleStack<NotationDeclaration> notationDeclarations;
    QXmlStreamNotationDeclarations publicNotationDeclarations;
    QXmlStreamNamespaceDeclarations publicNamespaceDeclarations;

    struct EntityDeclaration {
        QStringRef name;
        QStringRef notationName;
        QStringRef publicId;
        QStringRef systemId;
        QStringRef value;
        bool parameter;
        bool external;
        inline void clear() {
            name.clear();
            notationName.clear();
            publicId.clear();
            systemId.clear();
            value.clear();
            parameter = external = false;
        }
    };
    QXmlStreamSimpleStack<EntityDeclaration> entityDeclarations;
    QXmlStreamEntityDeclarations publicEntityDeclarations;

    QStringRef text;

    QStringRef prefix, namespaceUri, qualifiedName, name;
    QStringRef processingInstructionTarget, processingInstructionData;
    QStringRef dtdName, dtdPublicId, dtdSystemId;
    QStringRef documentVersion, documentEncoding;
    uint isEmptyElement : 1;
    uint isWhitespace : 1;
    uint isCDATA : 1;
    uint standalone : 1;
    uint hasCheckedStartDocument : 1;
    uint normalizeLiterals : 1;
    uint hasSeenTag : 1;
    uint inParseEntity : 1;
    uint referenceToUnparsedEntityDetected : 1;
    uint referenceToParameterEntityDetected : 1;
    uint hasExternalDtdSubset : 1;
    uint lockEncoding : 1;
    uint namespaceProcessing : 1;

    int resumeReduction;
    void resume(int rule);

    inline bool entitiesMustBeDeclared() const {
        return (!inParseEntity
                && (standalone
                    || (!referenceToUnparsedEntityDetected
                        && !referenceToParameterEntityDetected // Errata 13 as of 2006-04-25
                        && !hasExternalDtdSubset)));
    }

    // qlalr parser
    int tos;
    int stack_size;
    struct Value {
        int pos;
        int len;
        int prefix;
        ushort c;
    };

    Value *sym_stack;
    int *state_stack;
    inline void reallocateStack();
    inline Value &sym(int index) const
    { return sym_stack[tos + index - 1]; }
    QString textBuffer;
    inline void clearTextBuffer() {
        if (!scanDtd) {
            textBuffer.resize(0);
            textBuffer.reserve(256);
        }
    }
    struct Attribute {
        Value key;
        Value value;
    };
    QXmlStreamSimpleStack<Attribute> attributeStack;

    inline QStringRef symString(int index) {
        const Value &symbol = sym(index);
        return QStringRef(&textBuffer, symbol.pos + symbol.prefix, symbol.len - symbol.prefix);
    }
    inline QStringRef symName(int index) {
        const Value &symbol = sym(index);
        return QStringRef(&textBuffer, symbol.pos, symbol.len);
    }
    inline QStringRef symString(int index, int offset) {
        const Value &symbol = sym(index);
        return QStringRef(&textBuffer, symbol.pos + symbol.prefix + offset, symbol.len - symbol.prefix -  offset);
    }
    inline QStringRef symPrefix(int index) {
        const Value &symbol = sym(index);
        if (symbol.prefix)
            return QStringRef(&textBuffer, symbol.pos, symbol.prefix - 1);
        return QStringRef();
    }
    inline QStringRef symString(const Value &symbol) {
        return QStringRef(&textBuffer, symbol.pos + symbol.prefix, symbol.len - symbol.prefix);
    }
    inline QStringRef symName(const Value &symbol) {
        return QStringRef(&textBuffer, symbol.pos, symbol.len);
    }
    inline QStringRef symPrefix(const Value &symbol) {
        if (symbol.prefix)
            return QStringRef(&textBuffer, symbol.pos, symbol.prefix - 1);
        return QStringRef();
    }

    inline void clearSym() { Value &val = sym(1); val.pos = textBuffer.size(); val.len = 0; }


    short token;
    ushort token_char;

    uint filterCarriageReturn();
    inline uint getChar();
    inline uint peekChar();
    inline void putChar(uint c) { putStack.push() = c; }
    inline void putChar(QChar c) { putStack.push() =  c.unicode(); }
    void putString(const QString &s, int from = 0);
    void putStringLiteral(const QString &s);
    void putReplacement(const QString &s);
    void putReplacementInAttributeValue(const QString &s);
    ushort getChar_helper();

    bool scanUntil(const char *str, short tokenToInject = -1);
    bool scanString(const char *str, short tokenToInject, bool requireSpace = true);
    inline void injectToken(ushort tokenToInject) {
        putChar(int(tokenToInject) << 16);
    }

    QString resolveUndeclaredEntity(const QString &name);
    void parseEntity(const QString &value);
    QXmlStreamReaderPrivate *entityParser;

    bool scanAfterLangleBang();
    bool scanPublicOrSystem();
    bool scanNData();
    bool scanAfterDefaultDecl();
    bool scanAttType();


    // scan optimization functions. Not strictly necessary but LALR is
    // not very well suited for scanning fast
    int fastScanLiteralContent();
    int fastScanSpace();
    int fastScanContentCharList();
    int fastScanName(int *prefix = 0);
    inline int fastScanNMTOKEN();


    bool parse();
    inline void consumeRule(int);

    void raiseError(QXmlStreamReader::Error error, const QString& message = QString());
    void raiseWellFormedError(const QString &message);

    QXmlStreamEntityResolver *entityResolver;

private:
    /*! \internal
       Never assign to variable type directly. Instead use this function.

       This prevents errors from being ignored.
     */
    inline void setType(const QXmlStreamReader::TokenType t)
    {
        if(type != QXmlStreamReader::Invalid)
            type = t;
    }
};

bool QXmlStreamReaderPrivate::parse()
{
    // cleanup currently reported token

    switch (type) {
    case QXmlStreamReader::StartElement:
        name.clear();
        prefix.clear();
	qualifiedName.clear();
        namespaceUri.clear();
        if (publicNamespaceDeclarations.size())
            publicNamespaceDeclarations.clear();
        if (attributes.size())
            attributes.resize(0);
        if (isEmptyElement) {
            setType(QXmlStreamReader::EndElement);
            Tag &tag = tagStack_pop();
            namespaceUri = tag.namespaceDeclaration.namespaceUri;
            name = tag.name;
	    qualifiedName = tag.qualifiedName;
            isEmptyElement = false;
            return true;
        }
        clearTextBuffer();
        break;
    case QXmlStreamReader::EndElement:
        name.clear();
        prefix.clear();
	qualifiedName.clear();
        namespaceUri.clear();
        clearTextBuffer();
        break;
    case QXmlStreamReader::DTD:
        publicNotationDeclarations.clear();
        publicEntityDeclarations.clear();
        dtdName.clear();
        dtdPublicId.clear();
        dtdSystemId.clear();
        // fall through
    case QXmlStreamReader::Comment:
    case QXmlStreamReader::Characters:
        isCDATA = false;
	isWhitespace = true;
        text.clear();
        clearTextBuffer();
        break;
    case QXmlStreamReader::EntityReference:
        text.clear();
        name.clear();
        clearTextBuffer();
        break;
    case QXmlStreamReader::ProcessingInstruction:
        processingInstructionTarget.clear();
        processingInstructionData.clear();
	clearTextBuffer();
        break;
    case QXmlStreamReader::NoToken:
    case QXmlStreamReader::Invalid:
        break;
    case QXmlStreamReader::StartDocument:
	lockEncoding = true;
        documentVersion.clear();
        documentEncoding.clear();
#ifndef QT_NO_TEXTCODEC
	if(decoder->hasFailure()) {
	    raiseWellFormedError(QXmlStream::tr("Encountered incorrectly encoded content."));
	    readBuffer.clear();
	    return false;
	}
#endif
        // fall through
    default:
        clearTextBuffer();
        ;
    }

    setType(QXmlStreamReader::NoToken);


    // the main parse loop
    int act, r;

    if (resumeReduction) {
        act = state_stack[tos-1];
        r = resumeReduction;
        resumeReduction = 0;
        goto ResumeReduction;
    }

    act = state_stack[tos];

    forever {
        if (token == -1 && - TERMINAL_COUNT != action_index[act]) {
            uint cu = getChar();
            token = NOTOKEN;
            token_char = cu;
            if (cu & 0xff0000) {
                token = cu >> 16;
            } else switch (token_char) {
            case 0xfffe:
            case 0xffff:
                token = ERROR;
                break;
            case '\r':
                token = SPACE;
                if (cu == '\r') {
                    if ((token_char = filterCarriageReturn())) {
                        ++lineNumber;
                        lastLineStart = characterOffset + readBufferPos;
                        break;
                    }
                } else {
                    break;
                }
                // fall through
            case '\0': {
                token = EOF_SYMBOL;
                if (!tagsDone && !inParseEntity) {
                    int a = t_action(act, token);
                    if (a < 0) {
                        raiseError(QXmlStreamReader::PrematureEndOfDocumentError);
                        return false;
                    }
                }

            } break;
            case '\n':
                ++lineNumber;
                lastLineStart = characterOffset + readBufferPos;
            case ' ':
            case '\t':
                token = SPACE;
                break;
            case '&':
                token = AMPERSAND;
                break;
            case '#':
                token = HASH;
                break;
            case '\'':
                token = QUOTE;
                break;
            case '\"':
                token = DBLQUOTE;
                break;
            case '<':
                token = LANGLE;
                break;
            case '>':
                token = RANGLE;
                break;
            case '[':
                token = LBRACK;
                break;
            case ']':
                token = RBRACK;
                break;
            case '(':
                token = LPAREN;
                break;
            case ')':
                token = RPAREN;
                break;
            case '|':
                token = PIPE;
                break;
            case '=':
                token = EQ;
                break;
            case '%':
                token = PERCENT;
                break;
            case '/':
                token = SLASH;
                break;
            case ':':
                token = COLON;
                break;
            case ';':
                token = SEMICOLON;
                break;
            case ',':
                token = COMMA;
                break;
            case '-':
                token = DASH;
                break;
            case '+':
                token = PLUS;
                break;
            case '*':
                token = STAR;
                break;
            case '.':
                token = DOT;
                break;
            case '?':
                token = QUESTIONMARK;
                break;
            case '!':
                token = BANG;
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                token = DIGIT;
                break;
            default:
                if (cu < 0x20)
                    token = NOTOKEN;
                else
                    token = LETTER;
                break;
            }
        }

        act = t_action (act, token);
        if (act == ACCEPT_STATE) {
            // reset the parser in case someone resumes (process instructions can follow a valid document)
            tos = 0;
            state_stack[tos++] = 0;
            state_stack[tos] = 0;
            return true;
        } else if (act > 0) {
            if (++tos == stack_size)
                reallocateStack();

            Value &val = sym_stack[tos];
            val.c = token_char;
            val.pos = textBuffer.size();
            val.prefix = 0;
            val.len = 1;
            if (token_char)
                textBuffer += QChar(token_char);

            state_stack[tos] = act;
            token = -1;


        } else if (act < 0) {
            r = - act - 1;

#if defined (QLALR_DEBUG)
            int ridx = rule_index[r];
            printf ("%3d) %s ::=", r + 1, spell[rule_info[ridx]]);
            ++ridx;
            for (int i = ridx; i < ridx + rhs[r]; ++i) {
                int symbol = rule_info[i];
                if (const char *name = spell[symbol])
                    printf (" %s", name);
                else
                    printf (" #%d", symbol);
            }
            printf ("\n");
#endif

            tos -= rhs[r];
            act = state_stack[tos++];
        ResumeReduction:
            switch (r) {

        case 0:
            setType(QXmlStreamReader::EndDocument);
        break;

        case 1:
            if (type != QXmlStreamReader::Invalid) {
                if (hasSeenTag || inParseEntity) {
                    setType(QXmlStreamReader::EndDocument);
                } else {
                    raiseError(QXmlStreamReader::NotWellFormedError, QXmlStream::tr("Start tag expected."));
                    // reset the parser
                    tos = 0;
                    state_stack[tos++] = 0;
                    state_stack[tos] = 0;
                    return false;
                }
            }
        break;

        case 10:
            entityReferenceStack.pop()->isCurrentlyReferenced = false;
            clearSym();
        break;

        case 11:
            if (!scanString(spell[VERSION], VERSION, false) && atEnd) {
                resume(11);
                return false;
            }
        break;

        case 12:
            setType(QXmlStreamReader::StartDocument);
            documentVersion = symString(6);
            startDocument();
        break;

        case 13:
            hasExternalDtdSubset = true;
            dtdSystemId = symString(2);
        break;

        case 14:
            checkPublicLiteral(symString(2));
            dtdPublicId = symString(2);
            dtdSystemId = symString(4);
            hasExternalDtdSubset = true;
        break;

        case 16:
            if (!scanPublicOrSystem() && atEnd) {
                resume(16);
                return false;
            }
            dtdName = symString(3);
        break;

        case 17:
        case 18:
            dtdName = symString(3);
            // fall through

        case 19:
        case 20:
            setType(QXmlStreamReader::DTD);
            text = &textBuffer;
        break;

        case 21:
            scanDtd = true;
        break;

        case 22:
            scanDtd = false;
        break;

        case 36:
            if (!scanString(spell[EMPTY], EMPTY, false)
                && !scanString(spell[ANY], ANY, false)
                && atEnd) {
                resume(36);
                return false;
            }
        break;

        case 42:
            if (!scanString(spell[PCDATA], PCDATA, false) && atEnd) {
                resume(42);
                return false;
            }
        break;

        case 67: {
            lastAttributeIsCData = true;
        } break;

        case 77:
            if (!scanAfterDefaultDecl() && atEnd) {
                resume(77);
                return false;
            }
        break;

        case 82:
                sym(1) = sym(2);
                lastAttributeValue.clear();
                lastAttributeIsCData = false;
                if (!scanAttType() && atEnd) {
                    resume(82);
                    return false;
                }
        break;

        case 83: {
            DtdAttribute &dtdAttribute = dtdAttributes.push();
            dtdAttribute.tagName.clear();
            dtdAttribute.isCDATA = lastAttributeIsCData;
            dtdAttribute.attributePrefix = addToStringStorage(symPrefix(1));
            dtdAttribute.attributeName = addToStringStorage(symString(1));
            dtdAttribute.attributeQualifiedName = addToStringStorage(symName(1));
            dtdAttribute.isNamespaceAttribute = (dtdAttribute.attributePrefix == QLatin1String("xmlns")
                                                 || (dtdAttribute.attributePrefix.isEmpty()
                                                     && dtdAttribute.attributeName == QLatin1String("xmlns")));
            if (lastAttributeValue.isNull()) {
                dtdAttribute.defaultValue.clear();
            } else {
                if (dtdAttribute.isCDATA)
                    dtdAttribute.defaultValue = addToStringStorage(lastAttributeValue);
                else
                    dtdAttribute.defaultValue = addToStringStorage(lastAttributeValue.toString().simplified());

            }
        } break;

        case 87: {
            if (referenceToUnparsedEntityDetected && !standalone)
                break;
            int n = dtdAttributes.size();
            QStringRef tagName = addToStringStorage(symName(3));
            while (n--) {
                DtdAttribute &dtdAttribute = dtdAttributes[n];
                if (!dtdAttribute.tagName.isNull())
                    break;
                dtdAttribute.tagName = tagName;
                for (int i = 0; i < n; ++i) {
                    if ((dtdAttributes[i].tagName.isNull() || dtdAttributes[i].tagName == tagName)
                        && dtdAttributes[i].attributeQualifiedName == dtdAttribute.attributeQualifiedName) {
                        dtdAttribute.attributeQualifiedName.clear(); // redefined, delete it
                        break;
                    }
                }
            }
        } break;

        case 88: {
            if (!scanPublicOrSystem() && atEnd) {
                resume(88);
                return false;
            }
            EntityDeclaration &entityDeclaration = entityDeclarations.push();
            entityDeclaration.clear();
            entityDeclaration.name = symString(3);
        } break;

        case 89: {
            if (!scanPublicOrSystem() && atEnd) {
                resume(89);
                return false;
            }
            EntityDeclaration &entityDeclaration = entityDeclarations.push();
            entityDeclaration.clear();
            entityDeclaration.name = symString(5);
            entityDeclaration.parameter = true;
        } break;

        case 90: {
            if (!scanNData() && atEnd) {
                resume(90);
                return false;
            }
            EntityDeclaration &entityDeclaration = entityDeclarations.top();
            entityDeclaration.systemId = symString(3);
            entityDeclaration.external = true;
        } break;

        case 91: {
            if (!scanNData() && atEnd) {
                resume(91);
                return false;
            }
            EntityDeclaration &entityDeclaration = entityDeclarations.top();
            checkPublicLiteral((entityDeclaration.publicId = symString(3)));
            entityDeclaration.systemId = symString(5);
            entityDeclaration.external = true;
        } break;

        case 92: {
            EntityDeclaration &entityDeclaration = entityDeclarations.top();
            entityDeclaration.notationName = symString(3);
            if (entityDeclaration.parameter)
                raiseWellFormedError(QXmlStream::tr("NDATA in parameter entity declaration."));
        }
        //fall through

        case 93:
        case 94: {
            if (referenceToUnparsedEntityDetected && !standalone) {
                entityDeclarations.pop();
                break;
            }
            EntityDeclaration &entityDeclaration = entityDeclarations.top();
            if (!entityDeclaration.external)
                entityDeclaration.value = symString(2);
            QString entityName = entityDeclaration.name.toString();
            QHash<QString, Entity> &hash = entityDeclaration.parameter ? parameterEntityHash : entityHash;
            if (!hash.contains(entityName)) {
                Entity entity(entityDeclaration.value.toString());
                entity.unparsed = (!entityDeclaration.notationName.isNull());
                entity.external = entityDeclaration.external;
                hash.insert(entityName, entity);
            }
        } break;

        case 95: {
            setType(QXmlStreamReader::ProcessingInstruction);
            int pos = sym(4).pos + sym(4).len;
            processingInstructionTarget = symString(3);
            if (scanUntil("?>")) {
                processingInstructionData = QStringRef(&textBuffer, pos, textBuffer.size() - pos - 2);
                const QString piTarget(processingInstructionTarget.toString());
                if (!piTarget.compare(QLatin1String("xml"), Qt::CaseInsensitive)) {
                    raiseWellFormedError(QXmlStream::tr("XML declaration not at start of document."));
                }
                else if(!QXmlUtils::isNCName(piTarget))
                    raiseWellFormedError(QXmlStream::tr("%1 is an invalid processing instruction name.").arg(piTarget));
            } else if (type != QXmlStreamReader::Invalid){
                resume(95);
                return false;
            }
        } break;

        case 96:
            setType(QXmlStreamReader::ProcessingInstruction);
            processingInstructionTarget = symString(3);
            if (!processingInstructionTarget.toString().compare(QLatin1String("xml"), Qt::CaseInsensitive))
                raiseWellFormedError(QXmlStream::tr("Invalid processing instruction name."));
        break;

        case 97:
            if (!scanAfterLangleBang() && atEnd) {
                resume(97);
                return false;
            }
        break;

        case 98:
            if (!scanUntil("--")) {
                resume(98);
                return false;
            }
        break;

        case 99: {
            setType(QXmlStreamReader::Comment);
            int pos = sym(1).pos + 4;
            text = QStringRef(&textBuffer, pos, textBuffer.size() - pos - 3);
        } break;

        case 100: {
            setType(QXmlStreamReader::Characters);
            isCDATA = true;
	    isWhitespace = false;
            int pos = sym(2).pos;
            if (scanUntil("]]>", -1)) {
                text = QStringRef(&textBuffer, pos, textBuffer.size() - pos - 3);
            } else {
                resume(100);
                return false;
            }
        } break;

        case 101: {
            if (!scanPublicOrSystem() && atEnd) {
                resume(101);
                return false;
            }
            NotationDeclaration &notationDeclaration = notationDeclarations.push();
            notationDeclaration.name = symString(3);
        } break;

        case 102: {
            NotationDeclaration &notationDeclaration = notationDeclarations.top();
            notationDeclaration.systemId = symString(3);
            notationDeclaration.publicId.clear();
        } break;

        case 103: {
            NotationDeclaration &notationDeclaration = notationDeclarations.top();
            notationDeclaration.systemId.clear();
            checkPublicLiteral((notationDeclaration.publicId = symString(3)));
        } break;

        case 104: {
            NotationDeclaration &notationDeclaration = notationDeclarations.top();
            checkPublicLiteral((notationDeclaration.publicId = symString(3)));
            notationDeclaration.systemId = symString(5);
        } break;

        case 128:
            isWhitespace = false;
            // fall through

        case 129:
            sym(1).len += fastScanContentCharList();
            if (atEnd && !inParseEntity) {
                resume(129);
                return false;
            }
	break;

        case 138:
	    if (!textBuffer.isEmpty()) {
                setType(QXmlStreamReader::Characters);
                text = &textBuffer;
	    }
	break;

        case 139:
        case 140:
            clearSym();
        break;

        case 141:
        case 142:
            sym(1) = sym(2);
        break;

        case 143:
        case 144:
        case 145:
        case 146:
            sym(1).len += sym(2).len;
        break;

        case 172:
	    if (normalizeLiterals)
                textBuffer.data()[textBuffer.size()-1] = QLatin1Char(' ');
        break;

        case 173:
            sym(1).len += fastScanLiteralContent();
            if (atEnd) {
                resume(173);
                return false;
            }
        break;

        case 174: {
            if (!QXmlUtils::isPublicID(symString(1).toString())) {
                raiseWellFormedError(QXmlStream::tr("%1 is an invalid PUBLIC identifier.").arg(symString(1).toString()));
                resume(174);
                return false;
            }
        } break;

        case 175:
        case 176:
            clearSym();
        break;

        case 177:
        case 178:
	    sym(1) = sym(2);
        break;

        case 179:
        case 180:
        case 181:
        case 182:
            sym(1).len += sym(2).len;
        break;

        case 212:
        case 213:
            clearSym();
        break;

        case 214:
        case 215:
            sym(1) = sym(2);
            lastAttributeValue = symString(1);
        break;

        case 216:
        case 217:
        case 218:
        case 219:
            sym(1).len += sym(2).len;
        break;

        case 228: {
            QStringRef prefix = symPrefix(1);
            if (prefix.isEmpty() && symString(1) == QLatin1String("xmlns") && namespaceProcessing) {
                NamespaceDeclaration &namespaceDeclaration = namespaceDeclarations.push();
                namespaceDeclaration.prefix.clear();

                const QStringRef ns(symString(5));
                if(ns == QLatin1String("http://www.w3.org/2000/xmlns/") ||
                   ns == QLatin1String("http://www.w3.org/XML/1998/namespace"))
                    raiseWellFormedError(QXmlStream::tr("Illegal namespace declaration."));
                else
                    namespaceDeclaration.namespaceUri = addToStringStorage(ns);
            } else {
                Attribute &attribute = attributeStack.push();
                attribute.key = sym(1);
                attribute.value = sym(5);

                QStringRef attributeQualifiedName = symName(1);
                bool normalize = false;
                for (int a = 0; a < dtdAttributes.size(); ++a) {
                    DtdAttribute &dtdAttribute = dtdAttributes[a];
                    if (!dtdAttribute.isCDATA
                        && dtdAttribute.tagName == qualifiedName
                        && dtdAttribute.attributeQualifiedName == attributeQualifiedName
                        ) {
                        normalize = true;
                        break;
                    }
                }
                if (normalize) {
                    // normalize attribute value (simplify and trim)
                    int pos = textBuffer.size();
                    int n = 0;
                    bool wasSpace = true;
                    for (int i = 0; i < attribute.value.len; ++i) {
                        QChar c = textBuffer.at(attribute.value.pos + i);
                        if (c.unicode() == ' ') {
                            if (wasSpace)
                                continue;
                            wasSpace = true;
                        } else {
                            wasSpace = false;
                        }
                        textBuffer += textBuffer.at(attribute.value.pos + i);
                        ++n;
                    }
                    if (wasSpace)
                        while (n && textBuffer.at(pos + n - 1).unicode() == ' ')
                            --n;
                    attribute.value.pos = pos;
                    attribute.value.len = n;
                }
                if (prefix == QLatin1String("xmlns") && namespaceProcessing) {
                    NamespaceDeclaration &namespaceDeclaration = namespaceDeclarations.push();
                    QStringRef namespacePrefix = symString(attribute.key);
                    QStringRef namespaceUri = symString(attribute.value);
                    attributeStack.pop();
                    if (((namespacePrefix == QLatin1String("xml"))
                         ^ (namespaceUri == QLatin1String("http://www.w3.org/XML/1998/namespace")))
                        || namespaceUri == QLatin1String("http://www.w3.org/2000/xmlns/")
                        || namespaceUri.isEmpty()
                        || namespacePrefix == QLatin1String("xmlns"))
                        raiseWellFormedError(QXmlStream::tr("Illegal namespace declaration."));

                    namespaceDeclaration.prefix = addToStringStorage(namespacePrefix);
                    namespaceDeclaration.namespaceUri = addToStringStorage(namespaceUri);
                }
            }
        } break;

        case 234: {
            normalizeLiterals = true;
            Tag &tag = tagStack_push();
            prefix = tag.namespaceDeclaration.prefix  = addToStringStorage(symPrefix(2));
            name = tag.name = addToStringStorage(symString(2));
            qualifiedName = tag.qualifiedName = addToStringStorage(symName(2));
            if ((!prefix.isEmpty() && !QXmlUtils::isNCName(prefix)) || !QXmlUtils::isNCName(name))
                raiseWellFormedError(QXmlStream::tr("Invalid XML name."));
        } break;

        case 235:
            isEmptyElement = true;
        // fall through

        case 236:
            setType(QXmlStreamReader::StartElement);
            resolveTag();
            if (tagStack.size() == 1 && hasSeenTag && !inParseEntity)
                raiseWellFormedError(QXmlStream::tr("Extra content at end of document."));
            hasSeenTag = true;
        break;

        case 237: {
            setType(QXmlStreamReader::EndElement);
            Tag &tag = tagStack_pop();

            namespaceUri = tag.namespaceDeclaration.namespaceUri;
            name = tag.name;
            qualifiedName = tag.qualifiedName;
            if (qualifiedName != symName(3))
                raiseWellFormedError(QXmlStream::tr("Opening and ending tag mismatch."));
        } break;

        case 238:
            if (entitiesMustBeDeclared()) {
                raiseWellFormedError(QXmlStream::tr("Entity '%1' not declared.").arg(unresolvedEntity));
                break;
            }
            setType(QXmlStreamReader::EntityReference);
            name = &unresolvedEntity;
	break;

        case 239: {
            sym(1).len += sym(2).len + 1;
            QString reference = symString(2).toString();
            if (entityHash.contains(reference)) {
                Entity &entity = entityHash[reference];
                if (entity.unparsed) {
                    raiseWellFormedError(QXmlStream::tr("Reference to unparsed entity '%1'.").arg(reference));
                } else {
                    if (!entity.hasBeenParsed) {
                        parseEntity(entity.value);
                        entity.hasBeenParsed = true;
                    }
                    if (entity.literal)
                        putStringLiteral(entity.value);
                    else if (referenceEntity(entity))
                        putReplacement(entity.value);
                    textBuffer.chop(2 + sym(2).len);
                    clearSym();
                }
                break;
            }

            if (entityResolver) {
                QString replacementText = resolveUndeclaredEntity(reference);
                if (!replacementText.isNull()) {
                    putReplacement(replacementText);
                    textBuffer.chop(2 + sym(2).len);
                    clearSym();
                    break;
                }
            }

	    injectToken(UNRESOLVED_ENTITY);
	    unresolvedEntity = symString(2).toString();
	    textBuffer.chop(2 + sym(2).len);
	    clearSym();

        } break;

        case 240: {
            sym(1).len += sym(2).len + 1;
            QString reference = symString(2).toString();
            if (parameterEntityHash.contains(reference)) {
                referenceToParameterEntityDetected = true;
                Entity &entity = parameterEntityHash[reference];
                if (entity.unparsed || entity.external) {
                    referenceToUnparsedEntityDetected = true;
                } else {
                    if (referenceEntity(entity))
                        putString(entity.value);
                    textBuffer.chop(2 + sym(2).len);
                    clearSym();
                }
            } else if (entitiesMustBeDeclared()) {
                raiseWellFormedError(QXmlStream::tr("Entity '%1' not declared.").arg(symString(2).toString()));
            }
        } break;

        case 241:
            sym(1).len += sym(2).len + 1;
        break;

        case 242: {
            sym(1).len += sym(2).len + 1;
            QString reference = symString(2).toString();
            if (entityHash.contains(reference)) {
                Entity &entity = entityHash[reference];
                if (entity.unparsed || entity.value.isNull()) {
                    raiseWellFormedError(QXmlStream::tr("Reference to external entity '%1' in attribute value.").arg(reference));
                    break;
                }
                if (!entity.hasBeenParsed) {
                    parseEntity(entity.value);
                    entity.hasBeenParsed = true;
                }
                if (entity.literal)
                    putStringLiteral(entity.value);
                else if (referenceEntity(entity))
                    putReplacementInAttributeValue(entity.value);
                textBuffer.chop(2 + sym(2).len);
                clearSym();
                break;
            }

            if (entityResolver) {
                QString replacementText = resolveUndeclaredEntity(reference);
                if (!replacementText.isNull()) {
                    putReplacement(replacementText);
                    textBuffer.chop(2 + sym(2).len);
                    clearSym();
                    break;
                }
            }
            if (entitiesMustBeDeclared()) {
                raiseWellFormedError(QXmlStream::tr("Entity '%1' not declared.").arg(reference));
            }
        } break;

        case 243: {
            if (uint s = resolveCharRef(3)) {
                if (s >= 0xffff)
                    putStringLiteral(QString::fromUcs4(&s, 1));
                else
                    putChar((LETTER << 16) | s);

                textBuffer.chop(3 + sym(3).len);
                clearSym();
            } else {
                raiseWellFormedError(QXmlStream::tr("Invalid character reference."));
            }
        } break;

        case 246:
        case 247:
            sym(1).len += sym(2).len;
        break;

        case 258:
            sym(1).len += fastScanSpace();
            if (atEnd) {
                resume(258);
                return false;
            }
        break;

        case 261: {
            sym(1).len += fastScanName(&sym(1).prefix);
            if (atEnd) {
                resume(261);
                return false;
            }
        } break;

        case 262:
            sym(1).len += fastScanName();
            if (atEnd) {
                resume(262);
                return false;
            }
        break;

        case 263:
        case 264:
        case 265:
        case 266:
        case 267:
            sym(1).len += fastScanNMTOKEN();
            if (atEnd) {
                resume(267);
                return false;
            }

        break;

    default:
        ;
    } // switch
            act = state_stack[tos] = nt_action (act, lhs[r] - TERMINAL_COUNT);
            if (type != QXmlStreamReader::NoToken)
                return true;
        } else {
            parseError();
            break;
        }
    }
    return false;
}

#endif // QXMLSTREAM_P_H

