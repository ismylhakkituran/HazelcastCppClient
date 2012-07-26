#include <iostream>
#include "HazelcastClient.hpp"
#include "ClientConfig.hpp"

int main(int argc,char* argv[])
{

	ClientConfig clientConfig = new ClientConfig();
	clientConfig.groupconfig.Name = "dev";
	clientConfig.groupconfig.Password = "dev-pass";
	clientConfig.addAddress("127.0.0.1");
	HazelcastClient client = new HazelcastClient(clientConfig );


	//Almost all cluster operations that you can do with ordinary HazelcastInstance
	//Note that the Customer class must have Serializable attribute or implement Hazelcast.IO.DataSerializable
	//IMap<String, Customer> mapCustomers = client.getMap("customers");


	return 0;
}
