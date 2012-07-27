#ifndef CountDownLatch_hpp
#define CountDownLatch_hpp
//---------------------------------------------------------------
#include "../Connection/Connection.hpp"
#include "Foo.hpp"
//---------------------------------------------------------------
using std::string;
//---------------------------------------------------------------
class CounDownLatch{
public:
	CounDownLatch(Connection&);
	~CounDownLatch();
	bool await			(string,string,double);
	void getCount		(string,string,double&);
	bool setCount		(string,string,string);
	void countDown		(string,string);
private:
	Connection connection;
};
//---------------------------------------------------------------
bool CounDownLatch::await(string flag,string name,double time){

	connection.send("CDLAWAIT "+flag+" "+name+" "+Foo::doubleToString(time) +Foo::endOfLine);
	string reply;
	connection.recv(reply);
	if(reply[1]=="K")
		return true;
	else return false;
}
//---------------------------------------------------------------
void CounDownLatch::getCount(string flag,string name,double& count){

	connection.send("CDLGETCOUNT "+flag+" "+name+Foo::endOfLine );
	string reply;
	connection.recv(reply);
	std::vector<string> parsed=Foo::parseLineToWords(reply);
	if(parsed[0].at(1)=='K'){
		count=Foo::toDouble(parsed[2]);
	}
}
//---------------------------------------------------------------
bool CounDownLatch::setCount(string flag,string name,string count){

	connection.send("CDLSETCOUNT "+flag+" "+name+" "+count+Foo:: endOfLine );
	string reply;
	connection.recv(reply);
	std::vector<string> parsed=Foo::parseLineToWords(reply);
	if(parsed[0].at(1)=='K' && parsed[2]=="true" ){
			return true;
	}
	else return false;
}
//---------------------------------------------------------------
void CounDownLatch::countDown(string flag,string name ){

	connection.send("CDLCOUNTDOWN "+flag+" "+name+Foo::endOfLine);
	// recv ok did not received ,ignoreed
}
//---------------------------------------------------------------
CounDownLatch::CounDownLatch(Connection& connection){
	this->connection=connection;
}
//---------------------------------------------------------------
CounDownLatch::~CounDownLatch(){/***********/}
//---------------------------------------------------------------
#endif
