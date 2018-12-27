//
// Created by 25810 on 2018/12/22.
//

#include "JKRoAi.h"
#include "JKClient.hpp"
#include "JKTypes.h"
#include <stdlib.h>
#include <string.h>
#include "JKPack.h"

void JKRoAi::login() {
    JKClient* client = new JKClient("47.107.137.224","6900");
    if(client->connect() == JK_OK){
        LOGD("connect success!");
        client->listen();
#if 0
        char* bytes = (char*)malloc(55);
        int offset = 0;
        memset(bytes,0x00,55);
        //sprintf(bytes,"%d",);
        *(unsigned short int *)bytes = 0x64;
        offset += 2;
        *(unsigned int *)(bytes + offset) = 4;
        offset += 4;
        snprintf(bytes + offset,24,"%s","test");
        offset += 24;
        snprintf(bytes + offset,24,"%s","123456");
        offset += 24;
        *(unsigned char *)(bytes + offset) = 35;
        client->SendBytes(bytes,55);
#endif //0
        JKPack* jkPack = new JKPack();
        jkPack->writeUint16(0x64);
        jkPack->writeUint32(4);
        jkPack->writeChar("test",24);
        jkPack->writeChar("123456",24);
        jkPack->writeUint8(35);
        client->SendBytes(jkPack->getBuffer(),55);
    } else {
        LOGD("connect error!!!!");
    }
}
