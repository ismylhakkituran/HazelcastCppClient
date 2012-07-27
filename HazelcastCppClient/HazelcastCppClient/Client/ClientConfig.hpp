// Definition of the ClientConfig class

#ifndef ClientConfig_class
#define ClientConfig_class

#include "GroupConfig.hpp"
#include <vector>

class ClientConfig // : private Socket
{
 public:

  ClientConfig ( );
  ~ClientConfig( );

  int getAdressCount();

  std::string getAdress (int);
  int         getPort   (int);

  bool addAddress(std::string IP );

  std::string protocolType;
  GroupConfig  groupconfig;
 private:
  int defaultPort;
  std::vector<std::string> adresses;
  std::vector<int> ports;
};
#endif
