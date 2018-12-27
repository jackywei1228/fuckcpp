#include <string>
#include "JKMessageManager.h"
#ifndef FUCKCPP_JKPASER_H
#define FUCKCPP_JKPASER_H
using std::string;

class JKPaser : public JKMessageManager::JKMessageListener
{
public:
    JKPaser(string name);
    virtual int onRecive(int type,void* args);
protected:
private:
    int printPkg(char* pContent,unsigned int len);
    string mName;
};
#endif //FUCKCPP_JKPASER_H