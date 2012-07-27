#ifndef Lock_HPP
#define Lock_Hpp
//------------------------------------------------------------------------
#include "../Connection/Connection.hpp"
#include "Foo.hpp"
//------------------------------------------------------------------------
class Lock{

public:
	Lock(Connection&);
	~Lock();

	void lock			(string flag,string name);
	void unlock			(string flag,string name);
	void forceUnlock	(string flag,string name);
	bool isLocked		(string flag,string name);
private:
	Connection connection;
};
//------------------------------------------------------------------------
void Lock::lock(string flag,string name){
	connection.send("LOCK_LOCK "+flag+" "+name+Foo::endOfLine);
	string reply;
	connection.recv(reply);
}
//------------------------------------------------------------------------
void Lock::unlock(string flag,string name){
	connection.send("LOCK_UNLOCK "+flag+" "+name+Foo::endOfLine);
	string reply;
	connection.recv(reply);
}
//------------------------------------------------------------------------
void Lock::forceUnlock(string flag,string name){
	connection.send("LOCK_FORCE_UNLOCK "+flag+" "+name+Foo::endOfLine);
	string reply;
	connection.recv(reply);
}
//------------------------------------------------------------------------
bool Lock::isLocked(string flag,string name){
	connection.send("LOCK_IS_LOCKED "+flag+" "+name+Foo::endOfLine);
	string reply;
	connection.recv(reply);
	std::vector<string> parsed=Foo::parseLineToWords(reply);
	if(parsed[2]=="true")
		return true;
	else return false;
}
//------------------------------------------------------------------------
Lock::Lock(Connection& connection){
	this->connection=connection;
}
//------------------------------------------------------------------------
Lock::~Lock(){/*********/}
//------------------------------------------------------------------------
#endif
