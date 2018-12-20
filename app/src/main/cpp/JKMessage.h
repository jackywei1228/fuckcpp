//
// Created by android on 18-12-12.
//

#ifndef FUCKCPP_JKMESSAGE_H
#define FUCKCPP_JKMESSAGE_H

class JKMessageListener {
public:
    virtual int onRecive(int type,unsigned char bytes[],int len) = 0;
};

class JKMessage {
public:
    int addMessage(int type,unsigned char bytes[],int len);
    int addJKMessageListener(int type,JKMessageListener messageListener);
};



#endif //FUCKCPP_JKMESSAGE_H
