//
// Created by android on 18-12-24.
//

#ifndef FUCKCPP_JKPACK_H
#define FUCKCPP_JKPACK_H

#include "JKTypes.h"

class JKPack {
public:
    JKPack(char* buf,jk_uint32 length);
    JKPack(JKPack& jkpack);
    int resetWorkPoint();
    int getLength();

    int readInt32(jk_int32* parg);
    int readUint32(jk_uint32* parg);
    int readint16(jk_int16* parg);
    int readUint16(jk_uint16* parg);
    int readint8(jk_int8* parg);
    int readUint8(jk_uint8* parg);
    int readChar(char* parg);
    int readChar(char* parg,int pargLen,int readLen);


    int writeInt32(jk_int32 arg);
    int writeUint32(jk_uint32 arg);
    int writeint16(jk_int16 arg);
    int writeUint16(jk_uint16 arg);
    int writeint8(jk_int8 arg);
    int writeUint8(jk_uint8 arg);
    int writeChar(char arg);
    int writeChar(char* arg);
    int writeChar(char* arg,int len);

private:
    int isEnoughToWrite(int len);
    int isEnoughDataToRead(int len);
    int expandSpace();
    int mLength;
    char* pData;
    char* pCurrPoint;
};


#endif //FUCKCPP_JKPACK_H
