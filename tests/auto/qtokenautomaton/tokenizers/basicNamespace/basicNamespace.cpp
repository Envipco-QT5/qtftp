/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the test suite of the Qt Toolkit.
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
** contact the sales department at qt-sales@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/
/* NOTE: This file is AUTO GENERATED by qtokenautomaton2cpp.xsl. */

#include "basicNamespace.h"

QT_BEGIN_NAMESPACE

using namespace BasicNamespace;

Basic::Token Basic::classifier3(const QChar *data)

        {
            if (data[0] == 100)


                    {
                    
                            static const unsigned short string[] =
                            {
                                101, 102
                            };
                            if(memcmp(&data[1], &string, sizeof(QChar) * 2) == 0)
                        

                return _111;
            
                    }

                else if (data[0] == 97)


                    {
                    
                            static const unsigned short string[] =
                            {
                                98, 99
                            };
                            if(memcmp(&data[1], &string, sizeof(QChar) * 2) == 0)
                        

                return _;
            
                    }

                else if (data[0] == 103)


                    {
                    
                            static const unsigned short string[] =
                            {
                                104, 105
                            };
                            if(memcmp(&data[1], &string, sizeof(QChar) * 2) == 0)
                        

                return wobbly;
            
                    }

                

            return NoKeyword;
        }
    Basic::Token Basic::classifier4(const QChar *data)

        {
            if (data[0] == 70)


                    {
                    if (data[1] == 70)


                    {
                    if (data[2] == 70)


                    {
                    if (data[3] == 70)


                    {
                    

                return FFFF;
            
                    }

                else if (data[3] == 71)


                    {
                    

                return FFFG;
            
                    }

                
                    }

                else if (data[2] == 71)


                    {
                    if (data[3] == 70)


                    {
                    

                return FFGF;
            
                    }

                else if (data[3] == 71)


                    {
                    

                return FFGG;
            
                    }

                
                    }

                else if (data[2] == 76)


                    {
                    
                            if(data[3] == 77)
                        

                return FFLM;
            
                    }

                
                    }

                
                    }

                

            return NoKeyword;
        }
    Basic::Token Basic::classifier14(const QChar *data)

        {
            
                            static const unsigned short string[] =
                            {
                                99, 111, 108, 111, 110, 58, 105, 110, 58, 110, 97, 109, 101, 58
                            };
                            if(memcmp(&data[0], &string, sizeof(QChar) * 14) == 0)
                        

                return ColonInName;
            

            return NoKeyword;
        }
    Basic::Token Basic::classifier44(const QChar *data)

        {
            
                            static const unsigned short string[] =
                            {
                                97, 82, 101, 97, 108, 108, 121, 76, 111, 110, 103, 84, 111, 107, 101, 110, 73, 70, 114, 101, 97, 107, 105, 110, 77, 101, 97, 110, 73, 116, 85, 75, 110, 111, 119, 85, 75, 110, 111, 119, 75, 110, 111, 119
                            };
                            if(memcmp(&data[0], &string, sizeof(QChar) * 44) == 0)
                        

                return AReallyLongTokenIFreakinMeanItUKnowUKnowKnow;
            

            return NoKeyword;
        }
    Basic::Token Basic::toToken(const QChar *data, int length)
            {
                switch(length)
                {
                    
                        case 3:
                            return classifier3(data);

                    
                        case 4:
                            return classifier4(data);

                    
                        case 14:
                            return classifier14(data);

                    
                        case 44:
                            return classifier44(data);

                    
                        default:
                            return NoKeyword;
                }
            }

            
                QString Basic::toString(Token token)
                {
                    const unsigned short *data = 0;
                    int length = 0;

                    switch(token)
                    {
                    
                        case AReallyLongTokenIFreakinMeanItUKnowUKnowKnow:
                        {
                            static const unsigned short staticallyStoredAReallyLongTokenIFreakinMeanItUKnowUKnowKnow[] =
                            {
                            97, 82, 101, 97, 108, 108, 121, 76, 111, 110, 103, 84, 111, 107, 101, 110, 73, 70, 114, 101, 97, 107, 105, 110, 77, 101, 97, 110, 73, 116, 85, 75, 110, 111, 119, 85, 75, 110, 111, 119, 75, 110, 111, 119, 0
                            };
                            data = staticallyStoredAReallyLongTokenIFreakinMeanItUKnowUKnowKnow;
                            length = 44;
                            break;
                        }
                    
                        case ColonInName:
                        {
                            static const unsigned short staticallyStoredColonInName[] =
                            {
                            99, 111, 108, 111, 110, 58, 105, 110, 58, 110, 97, 109, 101, 58, 0
                            };
                            data = staticallyStoredColonInName;
                            length = 14;
                            break;
                        }
                    
                        case FFFF:
                        {
                            static const unsigned short staticallyStoredFFFF[] =
                            {
                            70, 70, 70, 70, 0
                            };
                            data = staticallyStoredFFFF;
                            length = 4;
                            break;
                        }
                    
                        case FFFG:
                        {
                            static const unsigned short staticallyStoredFFFG[] =
                            {
                            70, 70, 70, 71, 0
                            };
                            data = staticallyStoredFFFG;
                            length = 4;
                            break;
                        }
                    
                        case FFGF:
                        {
                            static const unsigned short staticallyStoredFFGF[] =
                            {
                            70, 70, 71, 70, 0
                            };
                            data = staticallyStoredFFGF;
                            length = 4;
                            break;
                        }
                    
                        case FFGG:
                        {
                            static const unsigned short staticallyStoredFFGG[] =
                            {
                            70, 70, 71, 71, 0
                            };
                            data = staticallyStoredFFGG;
                            length = 4;
                            break;
                        }
                    
                        case FFLM:
                        {
                            static const unsigned short staticallyStoredFFLM[] =
                            {
                            70, 70, 76, 77, 0
                            };
                            data = staticallyStoredFFLM;
                            length = 4;
                            break;
                        }
                    
                        case _:
                        {
                            static const unsigned short staticallyStored_[] =
                            {
                            97, 98, 99, 0
                            };
                            data = staticallyStored_;
                            length = 3;
                            break;
                        }
                    
                        case _111:
                        {
                            static const unsigned short staticallyStored_111[] =
                            {
                            100, 101, 102, 0
                            };
                            data = staticallyStored_111;
                            length = 3;
                            break;
                        }
                    
                        case wobbly:
                        {
                            static const unsigned short staticallyStoredwobbly[] =
                            {
                            103, 104, 105, 0
                            };
                            data = staticallyStoredwobbly;
                            length = 3;
                            break;
                        }
                    
                        default:
                            /* It's either the default token, or an undefined enum
                             * value. We silence a compiler warning, and return the
                             * empty string. */
                            ;
                    }

                    union
                    {
                        const unsigned short *data;
                        const QChar *asQChar;
                    } converter;
                    converter.data = data;

                    return QString::fromRawData(converter.asQChar, length);
                }
            
QT_END_NAMESPACE

