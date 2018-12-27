//
// Created by android on 18-12-27.
//

#include "JKTypes.h"
#include "JKPack.h"
#include "JKRecvPack.h"







#if 0
int JKRecvPack::writeInt32(jk_int32 arg) {
    return 0;
}

int JKRecvPack::writeUint32(jk_uint32 arg) {
    return JKPack::writeUint32(arg);
}

int JKRecvPack::writeint16(jk_int16 arg) {
    return JKPack::writeint16(arg);
}

int JKRecvPack::writeUint16(jk_uint16 arg) {
    return JKPack::writeUint16(arg);
}

int JKRecvPack::writeint8(jk_int8 arg) {
    return JKPack::writeint8(arg);
}

int JKRecvPack::writeUint8(jk_uint8 arg) {
    return JKPack::writeUint8(arg);
}

int JKRecvPack::writeChar(char arg) {
    return JKPack::writeChar(arg);
}

int JKRecvPack::writeChar(char *arg) {
    return JKPack::writeChar(arg);
}

int JKRecvPack::writeChar(char *arg, int len) {
    return JKPack::writeChar(arg, len);
}

#endif //1

JKRecvPack::JKRecvPack(char *buf, jk_uint32 length) : JKPack(buf, length) {

}
