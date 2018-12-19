//
// Created by 25810 on 2018/12/17.
//

#ifndef FUCKCPP_JKTHREAD_H
#define FUCKCPP_JKTHREAD_H

#include <string>
#include <sys/types.h>
#include <stdint.h>
#include "JKMutex.h"

using std::string;
using jkframework::JKMutex;

class JKThread {
public:
    JKThread();
    JKThread(string name);
    void start();
    bool isRunning();
    virtual void run() = 0;
    int join();

private:
    JKMutex mLock;
    volatile bool mRunning;
    pthread_t mThread;
    string mName;
    static int _threadLoop(void* user);
};


#endif //FUCKCPP_JKTHREAD_H
