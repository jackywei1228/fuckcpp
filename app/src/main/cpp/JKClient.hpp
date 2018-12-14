#include <string>
#include "JKPaser.hpp"

class JKClient
{
  public:
    JKClient(std::string ipName);
    int SetPaser(JKPaser paser);
    int SendBytes();
    int SendCommand();
  protected:
  private:
};
