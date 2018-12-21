#include <string>
#include "JKPaser.hpp"
#include "JKThread.h"
class JKClient
{
  public:
    JKClient(std::string ipName);

    JKClient(char *ipName);

    JKClient(char *ipName, char *port);

    int SetPaser(JKPaser paser);
    int SendBytes();
    int SendCommand();
    virtual void run();
  protected:
  private:
    std::string mIpName;
    std::string mIpPort;
};
