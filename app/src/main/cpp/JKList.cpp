//
// Created by android on 18-12-20.
//

#include <clocale>
#include "JKList.h"
#include "stdio.h"
#include "stdlib.h"




JKList::JKList() {

}

int JKList::push(void *item) {
    if(mPlistnodeHead == NULL){
        mPlistnodeHead = new listnode();
        mPlistnodeHead->pNext = NULL;
        mPlistnodeHead->pPre = NULL;
        mPlistnodeHead->item = item;
        mPlistnodeTail = mPlistnodeHead;
    } else {
        mPlistnodeTail->pNext = new listnode();
        mPlistnodeTail->pNext->pPre = mPlistnodeTail;
        //new tail
        mPlistnodeTail = mPlistnodeTail->pNext;
        mPlistnodeTail->item = item;
        mPlistnodeTail->pNext = NULL;
    }
    return 0;
}

void *JKList::pop() {
    if(mPlistnodeHead == NULL || mPlistnodeTail == NULL){
        return NULL;
    }

    listnode* tmp = mPlistnodeTail;
    void *item = tmp->item;
    //tmp->pPre == NULL indicate this is the last item in list;
    if(tmp->pPre == NULL){
        mPlistnodeHead = NULL;
        mPlistnodeTail = NULL;
    } else {
        mPlistnodeTail = tmp->pPre;
        mPlistnodeTail->pNext = NULL;
    }

    free(tmp);
    return item;

}

JKList::Iterator *JKList::getIterator() {
    Iterator * it = new Iterator(mPlistnodeHead);
    return it;
}

bool JKList::isEmpty() {
    return mPlistnodeHead == NULL ? true : false;
}

JKList::Iterator::Iterator(listnode *current) {
    mCurrent = current;
}

void *JKList::Iterator::next() {
    void * item = NULL;
    if(NULL == mCurrent){
        return NULL;
    } else {
        item = mCurrent->item;
        mCurrent = mCurrent->pNext;
    }
    return item;
}
