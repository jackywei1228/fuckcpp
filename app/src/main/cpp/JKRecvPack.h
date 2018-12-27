//
// Created by android on 18-12-27.
//

#ifndef FUCKCPP_JKRECVPACK_H
#define FUCKCPP_JKRECVPACK_H

#include "JKPack.h"

class JKRecvPack : public JKPack {
public:
    JKRecvPack(char* buf,jk_uint32 length);
private:
    using  JKPack::writeInt32;
    using  JKPack::writeUint32;
    using  JKPack::writeint16;
    using  JKPack::writeUint16;
    using  JKPack::writeint8;
    using  JKPack::writeUint8;
    using  JKPack::writeChar;
};

#endif //FUCKCPP_JKRECVPACK_H
