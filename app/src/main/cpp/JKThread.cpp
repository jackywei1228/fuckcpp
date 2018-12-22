//
// Created by 25810 on 2018/12/17.
//

#include "JKThread.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <string.h>

using jkframework::JKMutex;
typedef void *threadFun( void *ptr );

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*android_thread_func_t)(void*);

#ifdef __cplusplus
}
#endif

typedef android_thread_func_t thread_func_t;
typedef void* (*android_pthread_entry)(void*);

struct thread_data_t {
    thread_func_t   entryFunction;
    void*           userData;
    int             priority;
    char *          threadName;

    // we use this trampoline when we need to set the priority with
    // nice/setpriority, and name with prctl.
    static int trampoline(const thread_data_t* t) {
        thread_func_t f = t->entryFunction;
        void* u = t->userData;
        int prio = t->priority;
        char * name = t->threadName;
        delete t;
        if (name) {
            free(name);
        }
        return f(u);
    }
};

int JKThread::join() {
    JKMutex::Autolock _l(mLock);
    if(mThread == 0){
        return -1;
    }
    pthread_join(mThread, NULL);
}

bool JKThread::isRunning() {
    JKMutex::Autolock _l(mLock);
    return mRunning;
}

JKThread::JKThread(string name) :
        mLock("Thread::mLock"),
        mThread(0),
        mRunning(false),
        mName(name){

}

JKThread::JKThread():
        mLock("Thread::mLock"),
        mThread(0),
        mRunning(false),
        mName("JKThread"){

}

void JKThread::start() {
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    JKMutex::Autolock _l(mLock);
    pthread_create(&mThread, &attr, (android_pthread_entry)_threadLoop,(void*)this);
}

int JKThread::_threadLoop(void* user){
    JKThread* myInstane = (JKThread*)user;
    myInstane->mRunning = true;
    myInstane->run();
    myInstane->mRunning = false;
}

