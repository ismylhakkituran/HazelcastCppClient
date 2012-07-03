// Definition of the ClientConfig class

#ifndef ClientConfig_class
#define ClientConfig_class

#include "GroupConfig.hpp"


class ClientConfig // : private Socket
{
 public:

  ClientConfig ( );
  ~ClientConfig( );

  ClientConfig addAddress(std::string IP );
  GroupConfig  groupconfig;

};

/*
 *
 * 	ClientConfig clientConfig = new ClientConfig();
	clientConfig.GroupConfig.Name = "dev";
	clientConfig.GroupConfig.Password = "dev-pass";
	clientConfig.addAddress("10.90.0.1");
	HazelcastClient client = HazelcastClient.newHazelcastClient(clientConfig);*/
#endif
