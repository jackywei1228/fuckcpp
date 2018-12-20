//
// Created by android on 18-12-20.
//

#include <clocale>
#include "JKMessageManager.h"

typedef struct __itemData {
  int len;
  unsigned char *bytes;
} itemData;

int JKMessageManager::addMessage(int type, unsigned char *bytes, int len) {
    itemData* pitemdata = new itemData();
    pitemdata->bytes = bytes;
    pitemdata->len = len;
    mJKList.push((void*)pitemdata);
    return 0;
}

int JKMessageManager::addJKMessageListener(int type,
                                           JKMessageManager::JKMessageListener messageListener) {
    return 0;
}

JKMessageManager *JKMessageManager::GetInstance() {
    if(mJKMessageManager == NULL){
        mJKMessageManager = new JKMessageManager();
    }
    return mJKMessageManager;
}

JKMessageManager::JKMessageManager() : mJKList(){

}
