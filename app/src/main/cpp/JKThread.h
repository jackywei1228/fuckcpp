//
// Created by 25810 on 2018/12/17.
//

#ifndef FUCKCPP_JKTHREAD_H
#define FUCKCPP_JKTHREAD_H

#include <string>
using std::string;

class JKThread {
public:
    JKThread();
    JKThread(string name);
    void start();
    virtual void run() = 0;
};


#endif //FUCKCPP_JKTHREAD_H
