#include "JKPaser.hpp"
#include "JKClient.hpp"
#include "JKTypes.h"


JKPaser::JKPaser(string name) : mName(name) {
    JKMessageManager::GetInstance()->addJKMessageListener(JKMessageManager::MSG_RECEIVE_NETWORK_PACK,this);
}

int JKPaser::onRecive(int type, void *args) {
    if(type == JKMessageManager::MSG_RECEIVE_NETWORK_PACK){
        JKClient::PackageInfo* pPkg = (JKClient::PackageInfo*)args;
        printPkg(pPkg->pContent,pPkg->len);
    }
    return 0;
}

int JKPaser::printPkg(unsigned char *pContent, unsigned int len) {
    int rowNum = 16;
    int row = len / rowNum;
    int lastRowContent = len % 16;
    int offset = 0;
    char buf[60];
    int bufOffset = 0;
    memset(buf,0x00,60);

    if(row != 0){
        for(int i = 0; i < row; i++){
            memset(buf,0x00,60);
            bufOffset = 0;
            for (int y = 0;y < rowNum; y++){
                snprintf(buf + bufOffset,3 ,"%02x ",*(pContent + offset));
                bufOffset += 3;
                offset++;
            }
            LOGD("%s",buf);
        }
    }

    if(lastRowContent != 0){
        memset(buf,0x00,60);
        for (int i = 0;i < lastRowContent; i++){
            snprintf(buf + bufOffset,3 ,"%02x ",*(pContent + offset));
            bufOffset += 3;
            offset++;
        }
        LOGD("%s",buf);
    }

    return 0;
}

