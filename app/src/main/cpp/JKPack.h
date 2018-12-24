//
// Created by android on 18-12-24.
//

#ifndef FUCKCPP_JKPACK_H
#define FUCKCPP_JKPACK_H

#include "JKTypes.h"

class JKPack {
public:
    JKPack(char* buf,jk_uint32 length);
    jk_int32 readInt32();
    jk_uint32 readUint32();
    jk_int16 readint16();
    jk_uint16 readUint16();
    jk_int8 readint8();
    jk_uint8 readUint8();
    char readChar();


    int writeInt32(jk_int32 arg);
    int writeUint32(jk_uint32 arg);
    int writeint16(jk_int16 arg);
    int writeUint16(jk_uint16 arg);
    int writeint8(jk_int8 arg);
    int writeUint8(jk_uint8 arg);
    char writeChar(char arg);
};


#endif //FUCKCPP_JKPACK_H
