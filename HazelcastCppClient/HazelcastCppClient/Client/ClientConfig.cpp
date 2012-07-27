#include "GroupConfig.hpp"
#include "ClientConfig.hpp"

// -----------------------------------------------------
bool ClientConfig::addAddress(std::string IP){

	adresses.push_back(IP);
	return true;
}
// -----------------------------------------------------
int ClientConfig::getAdressCount(){

	return adresses.size();
}
// -----------------------------------------------------
std::string ClientConfig::getAdress(int index){

	return adresses[index];
}
// -----------------------------------------------------
int ClientConfig::getPort(int index){

	return ports[index];
}
// -----------------------------------------------------
ClientConfig::ClientConfig(){

	defaultPort=5701;

	for(int i=0; i<5; i++)
	ports.push_back(defaultPort+i);

}
// -----------------------------------------------------

ClientConfig::~ClientConfig(){

	//*/asdf9sdf465sd41vsd
}
