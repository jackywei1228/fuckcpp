#include <string>
#include "JKPaser.hpp"
#include "JKThread.h"
class JKClient : public JKThread
{
  public:
    static const int UNCONNECTED = 0;
    static const int CONNECTED = 1;
    static const int LISTENING = 2;
    static const int EXITING = 3;

    JKClient(std::string ipName);

    JKClient(char *ipName);

    JKClient(char *ipName, char *port);

    int SendBytes(void *buf,int len);
    virtual void run();
    int connect();
    int listen();
    int disconnect();
    int getStatus();
    struct PackageInfo {
        unsigned int len;
        unsigned char* pContent;
    };
  protected:
  private:
    std::string mIpName;
    std::string mIpPort;
    int mSockfd;
    int mStatus;
};
