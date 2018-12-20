//
// Created by android on 18-12-20.
//

#ifndef FUCKCPP_JKMESSAGEMANAGER_H
#define FUCKCPP_JKMESSAGEMANAGER_H

#include "JKList.h"

class JKMessageManager {
    class JKMessageListener {
    public:
        virtual int onRecive(int type,unsigned char bytes[],int len) = 0;
    };
public:
    int addMessage(int type,unsigned char bytes[],int len);
    int addJKMessageListener(int type,JKMessageListener messageListener);
    JKMessageManager* GetInstance();

private:
    JKMessageManager();
    void broadcast();
    JKList mJKList;
    JKMessageManager* mJKMessageManager;
};


#endif //FUCKCPP_JKMESSAGEMANAGER_H
