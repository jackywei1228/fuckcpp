//
// Created by android on 18-12-20.
//

#ifndef FUCKCPP_JKLIST_H
#define FUCKCPP_JKLIST_H

struct listnode;
struct listnode {
    listnode* pPre;
    listnode* pNext;
    void* item;
};

class JKList {
public:
    JKList();
    int push(void* item);
    void* pop();

private:
    listnode* mPlistnodeHead;
    listnode* mPlistnodeTail;
};


#endif //FUCKCPP_JKLIST_H
