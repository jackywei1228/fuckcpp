//
// Created by 25810 on 2018/12/17.
//

#ifndef FUCKCPP_JKTHREAD_H
#define FUCKCPP_JKTHREAD_H

#include <string>
#include <sys/types.h>
#include <stdint.h>
using std::string;

class JKThread {
public:
    JKThread();
    JKThread(string name);
    void start();
    bool isRunning() const;
    virtual void run() = 0;

private:
    volatile bool mRunning;

    int join();
};


#endif //FUCKCPP_JKTHREAD_H
