#ifndef IDGenerator_HPP
#define IDGenerator_HPP
//------------------------------------------------------------------------
#include "../Connection/Connection.hpp"
#include "Foo.hpp"
//------------------------------------------------------------------------
class IDGenerator{
public:
	IDGenerator(Connection&);
	~IDGenerator();
	void newID(string,string,string&);
private:
	Connection conneciton;
};
//------------------------------------------------------------------------
IDGenerator::IDGenerator(Connection& connection){
	this->conneciton=connection;
}
//------------------------------------------------------------------------
IDGenerator::~IDGenerator(){/*************/}
//------------------------------------------------------------------------
void IDGenerator::newID(string flag,string name,string& newID){

	conneciton.send("NEWID "+flag+" "+name+Foo::endOfLine );
	conneciton.recv(newID);
}
//------------------------------------------------------------------------
#endif
