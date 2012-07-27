#ifndef Map_class
#define Map_class
//-----------------------------------------------------------------------
#include "../Connection/Connection.hpp"
#include "../Connection/SocketException.h"
//-----------------------------------------------------------------------
using std::string;
//-----------------------------------------------------------------------
class Set
{
public:
	Set			(Connection&);
	~Set		();
	bool sadd	(string flag,string name,bool noreply,string element );
private:
	Connection connection;
};
//-----------------------------------------------------------------------
Set::Set(Connection& connection ){
	this->connection=connection;
}
//-----------------------------------------------------------------------
Set::~Set(){/****/}
//-----------------------------------------------------------------------
bool Set::sadd(string flag,string name,bool noreply,string element ){

	string noReply="";
	(noreply==true && noReply="noreply ");
	connection.send("SADD "+flag+" "+name+" "+noReply+"#1"+Foo::endOfLine );
	connection.send( Foo::toString( element.size() ) + Foo::endOfLine);
	connection.send(element+Foo::endOfLine);
	string reply;
	connection.recv(reply);
	std::vector<string> parsed=Foo::parseLineToWords(reply);
	if(parsed[0]=="true")
	return true;
	else return false;
}
//-----------------------------------------------------------------------

#endif
