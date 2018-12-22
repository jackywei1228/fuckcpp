#include <string>
#include "JKPaser.hpp"
#include "JKThread.h"
class JKClient : public JKThread
{
  public:
    JKClient(std::string ipName);

    JKClient(char *ipName);

    JKClient(char *ipName, char *port);

    int SetPaser(JKPaser paser);
    int SendBytes(void *buf,int len);
    int SendCommand();
    virtual void run();
    int connect();
    int listen();
    struct PackageInfo {
        unsigned int len;
        unsigned char* pContent;
    };
  protected:
  private:
    std::string mIpName;
    std::string mIpPort;
    int mSockfd;
};
