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
        mPlistnodeTail = mPlistnodeTail->pNext;
        mPlistnodeTail->item = item;
    }
    return 0;
}

void *JKList::pop() {
    if(mPlistnodeHead == NULL || mPlistnodeTail == NULL){
        return NULL;
    } else {
        listnode* tmp = mPlistnodeTail;
        void *item = tmp->item;
        mPlistnodeTail = mPlistnodeTail->pPre;
        free(tmp);
        return item;
    }
}
