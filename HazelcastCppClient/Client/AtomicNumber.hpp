#ifndef AtomicNumber_HPP
#define AtomicNumber_HPP
//------------------------------------------------------------------------
#include "../Connection/Connection.hpp"
#include "Foo.hpp"
//-----------------------------------------------------------------------------
class AtomicNumber{
public:
	AtomicNumber		(Connection&);
	~AtomicNUmber		();
	void addAndGet		(string,string,string);
	void getAndSet		(string,string,string);
	bool compareAndSet	(string,string,string,string);
	void getAndAdd		(string,string,string,string);

private:
	Connection connection;
};
//---------------------------------------------------------------------------
void AtomicNumber::addAndGet(string flag,string name,string delta){
//ADDANDGET <flag> <name> <delta>
	string reply;
	connection.send("ADDANDGET "+flag+" "+name+" "+delta+Foo::endOfLine );
	connection.recv(reply);
}
//---------------------------------------------------------------------------
void AtomicNumber::getAndSet(string flag,string name,string newValue){
	//GETANDSET <flag> <name> <newvalue>
	string reply;
	connection.send("GETANDSET "+flag+" "+name+" "+newValue+Foo::endOfLine );
	connection.recv(reply);
}
//---------------------------------------------------------------------------
bool AtomicNumber::compareAndSet(string flag,string name,string update,string expect){
	//COMPAREANDSET <flag> <name> <update> <expect>
	connection.send("COMPAREANDSET "+flag+" "+name+" "+update+" "+expect+Foo::endOfLine);
	string reply;
	connection.recv(reply);
	std::vector<string> parsed=Foo::parseLineToWords(reply); //              PARSE SATIR ARALARINI AYIRAMAZ ÇÖZÜM BUL
	if(parsed[2]=="true")
		return true;
	else return false;
}
//---------------------------------------------------------------------------
void AtomicNumber::getAndAdd(string flag,string name,string delta,string oldValue){
	//GETANDADD <flag> <name> <delta>
	connection.send("GETANDADD "+flag+" "+name+" "+delta+Foo::endOfLine );
	string reply;
	connection.recv(reply);
	std::vector<string >parsed=Foo::parseLineToWords(reply);//              PARSE SATIR ARALARINI AYIRAMAZ ÇÖZÜM BUL
	oldValue=parsed[2];

}
//---------------------------------------------------------------------------
AtomicNumber::AtomicNumber(Connection& connection){
	this->connection=connection;
}
//---------------------------------------------------------------------------
AtomicNumber::~AtomicNumber(){/************/}
//---------------------------------------------------------------------------
#endif
