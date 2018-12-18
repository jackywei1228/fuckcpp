//
// Created by 25810 on 2018/12/17.
//

#include "JKThread.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "JKMutex.h"
#include <string.h>

using jkframework::JKMutex;

int JKThread::join() {
//    JKMutex::Autolock _l(mLock);
}

bool JKThread::isRunning() const {
//    JKMutex::Autolock _l(mLock);
    return mRunning;
}

JKThread::JKThread(string name) {

}

void JKThread::start() {

}
