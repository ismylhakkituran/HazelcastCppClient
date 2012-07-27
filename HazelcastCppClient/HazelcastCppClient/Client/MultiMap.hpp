#ifndef MultiMap_hpp
#define MultiMap_hpp
//-------------------------------------------------------------
#include "../Connection/Connection.hpp"
#include "Foo.hpp"
//-------------------------------------------------------------
using std::string;
//-------------------------------------------------------------
class MultiMap{
public:
	MultiMap	(Connection&);
	~MultiMap	();
	bool mPut			(string flag,string name,bool noreply,string key,string value);
	bool mRemoveAll		(string flag,string name,bool noreply,string key);
	bool mRemoveValue	(string flag,string name,bool noreply,string key,string value);
	void mValueCount	(string flag,string name,string key,long& countValue);
private:
	Connection connection;
};
//-------------------------------------------------------------
bool MultiMap::mPut(string flag,string name,bool noreply,string key,string value){

	string noReply="";
	if(noReply)
		noReply="noreply ";
	connection.send("MMPUT "+flag+" "+name+" "+noreply+"#2");
	connection.send(Foo::toString(key.size())+" "+Foo::toString(value.size()) +Foo::endOfLine);
	connection.send(key+value+Foo::endOfLine);

	string reply;
	connection.recv(reply);

	std::vector<string> parsed=Foo::parseLineToWords(reply);

	if(parsed[0].at(1)=='K' && parsed[2]=="true")
		return true;
	else
		return false;
}
//-------------------------------------------------------------
bool MultiMap::mRemoveValue(string flag,string name,bool noreply,string key,string value){

	string noReply="";
	if(noReply)
		noReply="noreply ";
	connection.send("MMREMOVE "+flag+" "+name+" "+noreply+"#2");
	connection.send(Foo::toString(key.size())+" "+Foo::toString(value.size()) +Foo::endOfLine);
	connection.send(key+value+Foo::endOfLine);

	string reply;
	connection.recv(reply);

	std::vector<string> parsed=Foo::parseLineToWords(reply);

	if(parsed[0].at(1)=='K' && parsed[2]=="true")
		return true;
	else
		return false;
}
//-------------------------------------------------------------
bool MultiMap::mRemoveAll(string flag,string name,bool noreply,string key){

	string noReply="";
	if(noReply)
		noReply="noreply ";
	connection.send("MMREMOVE "+flag+" "+name+" "+noreply+"#1");
	connection.send(Foo::toString(key.size())+Foo::endOfLine);
	connection.send(key+Foo::endOfLine);

	string reply;
	connection.recv(reply);

	std::vector<string> parsed=Foo::parseLineToWords(reply);

	if(parsed[0].at(1)=='K' && parsed[2]=="true")
		return true;
	else
		return false;
}
//-------------------------------------------------------------
void MultiMap::mValueCount(string flag,string name,string key,long& valueCount){

	connection.send("MMVALUECOUNT "+flag+" "+name+" #1"+Foo::endOfLine);
	connection.send( Foo::toString( key.size() ) + Foo::endOfLine );
	connection.send(key+Foo::endOfLine);

	string reply;
	connection.recv(reply);
	std::vector<string> parsed=Foo::parseLineToWords(reply);
	if(parsed[0].at(1)=='K')
		valueCount=Foo::toDouble( parsed[2] );

}
//-------------------------------------------------------------
MultiMap::MultiMap(Connection& connection){
	this->connection=connection;
}
//-------------------------------------------------------------
MultiMap::~MultiMap(){/**********/}
//-------------------------------------------------------------
#endif
