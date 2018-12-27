#include "JKPaser.hpp"
#include "JKClient.hpp"
#include "JKTypes.h"
#include "JKRecvPack.h"


JKPaser::JKPaser(string name) : mName(name) {
    JKMessageManager::GetInstance()->addJKMessageListener(JKMessageManager::MSG_RECEIVE_NETWORK_PACK,this);
}

int JKPaser::onRecive(int type, void *args) {
    if(type == JKMessageManager::MSG_RECEIVE_NETWORK_PACK){
        JKClient::PackageInfo* pPkg = (JKClient::PackageInfo*)args;
        printPkg(pPkg->pContent,pPkg->len);
        JKRecvPack* pJKRecvPack = new JKRecvPack(pPkg->pContent,pPkg->len);
        jk_uint16 temp = 0;
        if(pJKRecvPack->readUint16(&temp) == JK_OK){
            LOGD("The JKRecvPack head is : %04X",(jk_uint16)temp);
        } else {
            LOGD("The JKRecvPack readUint16 read error");
        }
    }
    return 0;
}
#define LOG_BUF_LEN 256
int JKPaser::printPkg(char *pContent, unsigned int len) {
    int rowNum = 16;
    int row = len / rowNum;
    int lastRowContent = len % 16;
    int offset = 0;
    int bufOffset = 0;
    char buf[LOG_BUF_LEN];
    memset(buf,0x00,LOG_BUF_LEN);

    if(row != 0){
        LOGD("The row is %d",row);
        for(int i = 0; i < row; i++){
            memset(buf,0x00,LOG_BUF_LEN);
            bufOffset = 0;
            char* fmt = "%02d>";
            sprintf(buf,fmt,i*rowNum);
            memset(buf + strlen(buf),0x20,1);
            bufOffset = strlen(buf);
            for (int y = 0;y < rowNum; y++){
                snprintf(buf + bufOffset,3 ,"%02X",*(pContent + offset));
                bufOffset += 3;
                memset(buf + bufOffset - 1,0x20,1);
                offset++;
//                LOGD("str len : %d,bufOffset = %d",y*3,bufOffset);
            }
            buf[LOG_BUF_LEN-1]  = '\0';
            LOGD("%s",buf);
        }
    }

//    LOGD("the tail of data : %d",lastRowContent);

    if(lastRowContent != 0){
        memset(buf,0x00,LOG_BUF_LEN);
        bufOffset = 0;
        for (int i = 0;i < lastRowContent; i++){
            snprintf(buf + bufOffset,3 ,"%02x",*(pContent + offset));
            bufOffset += 3;
            memset(buf + bufOffset - 1,0x20,1);
            offset++;
            LOGD("lastRowContent len : %d",lastRowContent);
        }
        buf[LOG_BUF_LEN-1]  = '\n';
        LOGD("%s",buf);
    }

    return 0;
}

