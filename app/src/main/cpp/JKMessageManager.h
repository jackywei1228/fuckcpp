//
// Created by android on 18-12-20.
//

#ifndef FUCKCPP_JKMESSAGEMANAGER_H
#define FUCKCPP_JKMESSAGEMANAGER_H

#include "JKList.h"
#include "JKThread.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>
#include "JKTypes.h"

class JKMessageManager : public JKThread {
public:
    static const int MSG_RECEIVE_NETWORK_PACK = 0;
    static const int MSG_SEND_NETWORK_PACK = 1;
    class JKMessageListener {
    public:
        virtual int onRecive(int type,void* args) = 0;
    };
    int addMessage(int type,void* args);
    int addJKMessageListener(int type,JKMessageListener* messageListener);
    int delJKMessageListener(int type, JKMessageListener *messageListener);
    static JKMessageManager* GetInstance();

private:
    JKMessageManager();
    void broadcast();
    virtual void run();
    JKList mJKList;
    JKList mJKListenerList;
    static JKMessageManager* mJKMessageManager;
    pthread_cond_t mCv = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t mlock = PTHREAD_MUTEX_INITIALIZER;
};


#endif //FUCKCPP_JKMESSAGEMANAGER_H
