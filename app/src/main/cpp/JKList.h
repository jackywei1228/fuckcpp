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
    class Iterator{
    public:
        Iterator(listnode* current);
        void* next();
    private:
        listnode* mCurrent;
    };
    JKList();
    int push(void* item);
    void* pop();
    Iterator* getIterator();
    bool isEmpty();
private:
    listnode* mPlistnodeHead;
    listnode* mPlistnodeTail;
};


#endif //FUCKCPP_JKLIST_H
