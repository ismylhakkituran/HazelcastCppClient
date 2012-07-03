#include "HazelcastClient.hpp"
#include "ClientConfig.hpp"
#include "ClientSocket.h"
#include "SocketException.h"

//-----------------------------------------------------------------------------------
HazelcastClient HazelcastClient::newHazelcastClient(ClientConfig clientconfig )
{
	  try
	    {

	      ClientSocket client_socket ( "localhost", 5701 );
	      std::string reply1,reply2;

	      try
		  {
	    	  client_socket << "P01  ";
	    	  client_socket >> reply1;
	    	  client_socket >> "AUTH 0 "+clientconfig.groupconfig.Name+" "+clientconfig.groupconfig.Password;
	    	  client_socket >> reply2;
		  }
	      catch ( SocketException& ) {}

	      std::cout << "Response.1 :\n" << reply1 << "\n\n"<<"Response.2 :\n"<<reply2 ;


	    }
	  catch ( SocketException& e )
	    {
	      std::cout << "Exception was caught:" << e.description() << "\n";
	    }

	return 0;
}
//-----------------------------------------------------------------------------------
HazelcastClient::HazelcastClient(ClientConfig clientconfig){

//	clientconfig;
}
//-----------------------------------------------------------------------------------
HazelcastClient::~HazelcastClient()
{
/*
	delete all;*/
}
