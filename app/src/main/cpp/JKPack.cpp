//
// Created by android on 18-12-24.
//

#include "JKPack.h"
#include "JKTypes.h"
#include <stdlib.h>
#include <string.h>

#define DEFAULT_LENGHT 4096

int JKPack::readInt32(jk_int32* parg) {
    if(!isEnoughDataToRead(sizeof(jk_int32))){
        return JK_ERROR_NO_SPACE;
    }
    *parg = *(jk_int32*)pCurrPoint;
    pCurrPoint += sizeof(jk_int32);
    return JK_OK;
}

int JKPack::readUint32(jk_uint32* parg) {
    if(!isEnoughDataToRead(sizeof(jk_uint32))){
        return JK_ERROR_NO_SPACE;
    }
    *parg = *(jk_uint32*)pCurrPoint;
    pCurrPoint += sizeof(jk_uint32);
    return JK_OK;
}

int JKPack::readint16(jk_int16* parg) {
    if(!isEnoughDataToRead(sizeof(jk_int16))){
        return JK_ERROR_NO_SPACE;
    }
    *parg = *(jk_uint16*)pCurrPoint;
    pCurrPoint += sizeof(jk_int16);
    return JK_OK;
}

int JKPack::readUint16(jk_uint16* parg) {
    if(!isEnoughDataToRead(sizeof(jk_uint16))){
        return JK_ERROR_NO_SPACE;
    }
    *parg = *(jk_uint16*)pCurrPoint;
    pCurrPoint += sizeof(jk_uint16);
    return JK_OK;
}

int JKPack::readint8(jk_int8* parg) {
    if(!isEnoughDataToRead(sizeof(jk_int8))){
        return JK_ERROR_NO_SPACE;
    }
    *parg = *(jk_int8*)pCurrPoint;
    pCurrPoint += sizeof(jk_int8);
    return JK_OK;
}

int JKPack::readUint8(jk_uint8* parg) {
    if(!isEnoughDataToRead(sizeof(jk_uint8))){
        return JK_ERROR_NO_SPACE;
    }
    *parg = *(jk_uint8*)pCurrPoint;
    pCurrPoint += sizeof(jk_uint8);
    return JK_OK;
}

int JKPack::readChar(char* parg) {
    if(!isEnoughDataToRead(sizeof(char))){
        return JK_ERROR_NO_SPACE;
    }
    *parg = *(char*)pCurrPoint;
    pCurrPoint += sizeof(char);
    return JK_OK;
}

int JKPack::readChar(char* parg,int pargLen,int readLen) {
    if(((mLength - readLen - (pCurrPoint - pData)) < 0)
       || (readLen <= 0)
       || (readLen > pargLen)){
        return JK_ERROR_NO_SPACE;
    }
    memcpy(parg,pCurrPoint,readLen);
    pCurrPoint += readLen;
    return JK_OK;
}

int JKPack::isEnoughDataToRead(int len) {
    if((mLength - len - (pCurrPoint - pData)) < 0){
        return JK_FALSE;
    } else {
        return JK_TRUE;
    }
}


//--------------------------------------------------------------------------------

int JKPack::writeInt32(jk_int32 arg) {
    if(! isEnoughToWrite(sizeof(jk_int32))){
        expandSpace();
    }
    memcpy(pCurrPoint,&arg,sizeof(jk_int32));
    pCurrPoint += sizeof(jk_int32);
    return JK_OK;
}

int JKPack::writeUint32(jk_uint32 arg) {
    if(! isEnoughToWrite(sizeof(jk_uint32))){
        expandSpace();
    }
    memcpy(pCurrPoint,&arg,sizeof(jk_uint32));
    pCurrPoint += sizeof(jk_uint32);
    return JK_OK;
}

int JKPack::writeint16(jk_int16 arg) {
    if(! isEnoughToWrite(sizeof(jk_int16))){
        expandSpace();
    }
    memcpy(pCurrPoint,&arg,sizeof(jk_int16));
    pCurrPoint += sizeof(jk_int16);
    return JK_OK;
}

int JKPack::writeUint16(jk_uint16 arg) {
    if(! isEnoughToWrite(sizeof(jk_uint16))){
        expandSpace();
    }
    memcpy(pCurrPoint,&arg,sizeof(jk_uint16));
    pCurrPoint += sizeof(jk_uint16);
    return JK_OK;
}

int JKPack::writeint8(jk_int8 arg) {
    if(! isEnoughToWrite(sizeof(jk_int8))){
        expandSpace();
    }
    memcpy(pCurrPoint,&arg,sizeof(jk_int8));
    pCurrPoint += sizeof(jk_int8);
    return JK_OK;
}

int JKPack::writeUint8(jk_uint8 arg) {
    if(! isEnoughToWrite(sizeof(jk_uint8))){
        expandSpace();
    }
    memcpy(pCurrPoint,&arg,sizeof(jk_uint8));
    pCurrPoint += sizeof(jk_uint8);
    return JK_OK;
}

int JKPack::writeChar(char arg) {
    if(! isEnoughToWrite(sizeof(char))){
        expandSpace();
    }
    memcpy(pCurrPoint,&arg,sizeof(char));
    pCurrPoint += sizeof(char);
    return JK_OK;
}


int JKPack::writeChar(char* arg) {
    int len = 0;
    if(arg == NULL){
        return JK_ERROR;
    }
    len =  strlen(arg);
    if(! isEnoughToWrite(len)){
        expandSpace();
    }
    memcpy(pCurrPoint,arg,len);
    pCurrPoint += len;
    return JK_OK;
}

int JKPack::writeChar(char *arg, int len) {
    int myStrlen = 0;
    char* tmpCurr = pCurrPoint;
    if(arg == NULL){
        return JK_ERROR;
    }
    if(! isEnoughToWrite(len)){
        expandSpace();
    }

    myStrlen = strlen(arg);

    if(myStrlen > len){
        return JK_ERROR;
    } else {
        writeChar(arg);
        int wreatenDataLen = pCurrPoint - tmpCurr;
        if(wreatenDataLen < len){
            pCurrPoint += (len - wreatenDataLen);
        }
    }
    return JK_OK;
}

int JKPack::isEnoughToWrite(int len){
    if(((pCurrPoint - pData) + len) > mLength){
        return JK_FALSE;
    }
    return JK_TRUE;
}

int JKPack::expandSpace() {
    char* tmpData = (char*)malloc(mLength*2);
    if(tmpData != NULL){
        int CurrOffset = pCurrPoint - pData;
        memset(tmpData,0x00,mLength*2);
        memcpy(tmpData,pData,mLength);
        free(pData);
        pData = tmpData;
        pCurrPoint = pData + CurrOffset;
        mLength = mLength*2;
    } else {
        return JK_ERROR_NO_SPACE;
    }
    return JK_OK;
}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------

JKPack::JKPack(char *buf, jk_uint32 length) {
    if(buf == NULL){
        mLength = DEFAULT_LENGHT;
        pData = (char*)malloc(mLength);
    } else {
        mLength = length * 2;
        pData = (char*)malloc(mLength);
    }
    memset(pData,0x00,mLength);
    pCurrPoint = pData;
}

JKPack::JKPack(JKPack& jkpack) {
    char* tmppData = NULL;
    mLength = jkpack.mLength;
    tmppData = (char*)malloc(jkpack.mLength);
    //the risk is malloc function return NULL value. So we make the exception to indicate.
    if(tmppData == NULL){
        *tmppData = 0xFFFFFF;
    }
    memset(tmppData,0x00,jkpack.mLength);
    memcpy(tmppData,jkpack.pData,jkpack.mLength);
    mLength = jkpack.mLength;
    pData = tmppData;
    pCurrPoint = pData;
    pCurrPoint += (jkpack.pCurrPoint - jkpack.pData);
}

int JKPack::resetWorkPoint() {
    pCurrPoint = pData;
    return 0;
}

int JKPack::getLength() {
    return mLength;
}



