#include <iostream>
#include "HazelcastClient.hpp"
#include "ClientConfig.hpp"
#include "../Connection/Connection.hpp"
#include "../Connection/SocketException.h"
#include <vector>

using std::string;
//-----------------------------------------------------------------------------------
bool HazelcastClient::partitions(string flag,std::vector<string>& pid,std::vector<string>& adress){
	if(connection.is_valid()==true )
	{
	  connection.send("PARTITIONS "+flag+" #1"+endOfLine);
	  string tempToParse;
                                                                      //   parse edip pid ve adress lere basılacak...
		  connection.recv(tempToParse);
	  size_t place;
	  place=tempToParse.find("OK "+flag);
	  if(-1 != (int)place )
		  return true;
	  else
		  return false;
	}
	else throw SocketException("\nconnection is not valid, connection died.");
}
//-----------------------------------------------------------------------------------
bool HazelcastClient::partitions(string flag,string key,string& pid,string& adress){
	if(connection.is_valid()==true )
	{
	  connection.send("PARTITIONS "+flag+" #1");
	  connection.send( endOfLine );

	  if(key!=""){
		  	 key.size(); string g;
		  connection.send( g+endOfLine);
		  connection.send( key +endOfLine);
	 }
	  string tempToParse;

                                                                 //   parse edip pid ve adress lere eşlenecek...

		  connection.recv(tempToParse);
	  size_t place;
	  place=tempToParse.find("OK "+flag);
	  if(-1 != (int)place )
		  return true;
	  else
		  return false;
	}
	else throw SocketException("\nconnection is not valid, connection died.");


/*
*
*The key is optional. If if it provided server will return only the partition that the key falls.
*Otherwise it will return all partitions as a pair of partition id and member address that owns the partition.
*
*Return value:
*
*If key is provided:
*OK <flag> <pid> <address>
*If key is not provided to command:
*OK <flag> <pid1> <address1> ... <pid271> <address271>
*Note that 271 is the default partition count which can be changed on server configuration.
* */
}
//-----------------------------------------------------------------------------------
bool HazelcastClient::clustertime(string flag,string& time){
	if(connection.is_valid()==true )
	{
	  connection.send("MEMBERS "+flag+endOfLine);
	  connection.recv(time);
	  size_t place;
	  place=time.find("OK "+flag);
	  if(-1 != (int)place )
		  return true;
	  else
		  return false;
	}
	else throw SocketException("\nconnection is not valid, connection died.");
}
//-----------------------------------------------------------------------------------
bool HazelcastClient::ping(string flag){
	if(connection.is_valid()==true )
	{
	  connection.send("PING "+flag+endOfLine);
	  std::string reply;
	  connection.recv(reply);

	  if(reply=="OK "+flag)
		  return true;
	  else
		  return false;
	}
	else throw SocketException("\nconnection is not valid, connection died.");
}
//-----------------------------------------------------------------------------------
bool HazelcastClient::members(string flag,std::vector<string>& members){
	if(connection.is_valid()==true )
	{
	  connection.send("MEMBERS "+flag+endOfLine);
	  string mmbrs;                                            // members parse edilip vectore basılacak
	  connection.recv(mmbrs);
	  size_t place;
	  place=mmbrs.find("OK "+flag);
	  if(-1 != (int)place ){
		// boşluk sayısı-1 kadar elemanı olacak bunun
		  // ush back yapılacak
		  return true;
	  }
	  else
		  return false;
	}
	else throw SocketException("\nconnection is not valid, connection died.");
}
//-----------------------------------------------------------------------------------
bool HazelcastClient::instances(string flag,std::vector<string>& type,std::vector<string>& instance ){
	if(connection.is_valid()==true )
	{
	  connection.send("INSTANCES "+flag+endOfLine);
	  string reply;
	  connection.recv(reply);                                           //reply parse edilip vectore basılacak
	  size_t place;
	  place=reply.find("OK "+flag);
	  if(-1 != (int)place )
		  return true;
	  else
		  return false;
	}
	else throw SocketException("\nconnection is not valid, connection died.");
/*Returns all queue, map, set, list, topic, lock, multimap instances created by Hazelcast.
 * */
}
//-----------------------------------------------------------------------------------
bool HazelcastClient::trxrollback(string flag){

	if(connection.is_valid()==true )
	{
	  connection.send("TRXROLLBACK "+flag+endOfLine);
	  std::string reply;
	  connection.recv(reply);

	  if(reply=="OK "+flag)
		  return true;
	  else
		  return false;
	}
	else throw SocketException("\nconnection is not valid, connection died.");
}
//-----------------------------------------------------------------------------------
bool HazelcastClient::trxcommit(string flag){

	if(connection.is_valid()==true )
	{
	  connection.send("TRXCOMMIT "+flag+endOfLine);
	  std::string reply;
	  connection.recv(reply);

	  if(reply=="OK "+flag)
		  return true;
	  else
		  return false;
	}
	else throw SocketException("\nconnection is not valid, connection died.");
}
//-----------------------------------------------------------------------------------
bool HazelcastClient::trxbegin(string flag){

	if(connection.is_valid()==true )
	{
	  connection.send("TRXBEGIN "+flag+endOfLine);
	  std::string reply;
	  connection.recv(reply);

	  if(reply=="OK "+flag)
		  return true;
	  else
		  return false;
	}
	else throw SocketException("\nconnection is not valid, connection died.");
}
//-----------------------------------------------------------------------------------
bool HazelcastClient::destroy(string flag,string type,string name){

/*		type can be: map, queue, list, set, atomic_number, topic, lock, multimap,
 *                   idgen, semaphore, count_down_latch    */

	if(connection.is_valid()==true )
	{
	  connection.send("DESTROY "+flag+" "+type+" "+name+endOfLine );
	  std::string reply;
	  connection.recv(reply);

	  if(reply=="OK "+flag)
		  return true;
	  else
		  return false;

	}
	else throw SocketException("\nconnection is not valid, connection died.");
}
//-----------------------------------------------------------------------------------
void HazelcastClient::auth(ClientConfig& clientconfig){

			  	  /* LOOK     client.set_non_blocking(true);*/

	              connection.send(clientconfig.groupconfig.getProtocolType()+endOfLine );
		/*    	  std::cout<<"Protocol Type :  "
		    			   <<clientconfig.groupconfig.getProtocolType();

		    	  std::cout<<"\nUsername: "<<clientconfig.groupconfig.getName()
		    			  <<"\nPassword: "<<clientconfig.groupconfig.getPassword();
*/
		    	  std::string login="AUTH "+clientconfig.groupconfig.getLoginFlag()+" "+
		    			  	  	  	  	  clientconfig.groupconfig.getName()+" "+clientconfig.groupconfig.getPassword();

		    	  connection.send(login+endOfLine );

		    	  std::string reply;
		    	  connection.recv(reply);
		    	 // std::cout<<std::endl<<reply;
}
//-----------------------------------------------------------------------------------
HazelcastClient::HazelcastClient(ClientConfig& clntcnfg){

	endOfLine="\r\n";
	try
	{
	  if(!connection.create())
		  throw SocketException ( "Could not create connection." );

	  if(!connection.connectPort( clntcnfg.getAdress(0) ,clntcnfg.getPort(0) ))
	  	  throw SocketException ( "Could not connect port." );
	}
	  catch (SocketException& e) {
		  std::cout << "Exception was caught:" << e.description() << "\n";
	}


	this->auth(clntcnfg);
}
//-----------------------------------------------------------------------------------
HazelcastClient::~HazelcastClient(){
	/*	delete all  */
	//std::cout<<"\nHzClient deconstructor is running....";
}
//-----------------------------------------------------------------------------------
