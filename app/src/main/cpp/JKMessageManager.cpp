//
// Created by android on 18-12-20.
//

#include <clocale>
#include "JKMessageManager.h"

typedef struct __MsgData {
  int type;
  void* args;
} MsgData;

typedef struct __ListenerStr {
    int type;
    JKMessageManager::JKMessageListener* messageListener;
} ListenerStr;

JKMessageManager* JKMessageManager::mJKMessageManager = NULL;

int JKMessageManager::addMessage(int type, void *args) {
    bool notifyFlag = mJKList.isEmpty();
    MsgData* pitemdata = new MsgData();
    pitemdata->type = type;
    pitemdata->args = args;
    mJKList.push((void*)pitemdata);
    if(notifyFlag){
        pthread_cond_signal(&mCv);
    }
    return 0;
}

int JKMessageManager::addJKMessageListener(int type,
                                           JKMessageManager::JKMessageListener* messageListener) {
    if(NULL == messageListener){
        return JK_ERROR;
    }
    ListenerStr* mylister = new ListenerStr();
    mylister->type = type;
    mylister->messageListener = messageListener;
    mJKListenerList.push(mylister);
    return JK_OK;
}

int JKMessageManager::delJKMessageListener(int type,
                                           JKMessageManager::JKMessageListener* messageListener){

    return JK_OK;
}

JKMessageManager *JKMessageManager::GetInstance() {
    if(mJKMessageManager == NULL){
        mJKMessageManager = new JKMessageManager();
    }
    return mJKMessageManager;
}

JKMessageManager::JKMessageManager() : mJKList(),mJKListenerList(){

}

void JKMessageManager::run() {
    for(;;){
        void* item = mJKList.pop();
        if(NULL == item){
            pthread_mutex_lock(&mlock);
            pthread_cond_wait(&mCv, &mlock);
            pthread_mutex_unlock(&mlock);
            continue;
        } else {
            MsgData* pMsg = (MsgData*)item;
            JKList::Iterator* it = mJKListenerList.getIterator();
            void* listenerStrTmp = NULL;
            while((listenerStrTmp = it->next()) != NULL){
                ListenerStr* listenerStrInstance = (ListenerStr*)listenerStrTmp;
                if(listenerStrInstance->type == pMsg->type){
                    listenerStrInstance->messageListener->onRecive(pMsg->type,pMsg->args);
                }
            }
        }
    }
}

