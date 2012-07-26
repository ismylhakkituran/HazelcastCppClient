// Definition of the ClientConfig class

#ifndef HazelcastClient_class
#define HazelcastClient_class

#include "ClientConfig.hpp"
#include "HazelcastClient.hpp"

class HazelcastClient// : private Socket
{
 public:

	HazelcastClient (ClientConfig clientconfig );
	~HazelcastClient();
    HazelcastClient newHazelcastClient(ClientConfig clientconfig );

};

/*
 *
 * 	ClientConfig clientConfig = new ClientConfig();
	clientConfig.GroupConfig.Name = "dev";
	clientConfig.GroupConfig.Password = "dev-pass";
	clientConfig.addAddress("10.90.0.1");
	HazelcastClient client = HazelcastClient.newHazelcastClient(clientConfig);*/
#endif
