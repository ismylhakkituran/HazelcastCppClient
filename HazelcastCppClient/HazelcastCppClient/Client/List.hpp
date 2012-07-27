#ifndef List_hpp
#define List_hpp
//------------------------------------------------------------------
#include "../Connection/Connection.hpp"
#include "Foo.hpp"
//------------------------------------------------------------------
using std::string;
//------------------------------------------------------------------
class List{
public:
	List(Connection&);
	~List();
	void add(string,string,bool,string);
private:
	Connection connection;
};
//------------------------------------------------------------------
List::List(Connection& connection){
	this->connection=connection;
}
//------------------------------------------------------------------
void List::add(string flag,string name,bool noreply,string element){

	string noReply="";
	if(noreply)
		noReply="noreply ";

	connection.send("LADD "+flag+" "+name+" "+noReply+"#1"+Foo::endOfLine );
	connection.send(Foo::toString( element.size() ) + Foo::endOfLine );
	connection.send(element+Foo::endOfLine);

	//--------------reply message did't received from server.(ignored)

}
//------------------------------------------------------------------
List::~List(){/******/}
//------------------------------------------------------------------
#endif
