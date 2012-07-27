#ifndef  TOPIC_HPP
#define  TOPIC_HPP
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
#include "../Connection/Connection.hpp"
#include "Foo.hpp"
//-----------------------------------------------------------------------------
class Topic
{
	public:
	Topic(Connection&);
	~Topic();
	void publish(string,string,string);

	private:
	Connection connection;
};
//-----------------------------------------------------------------------------
void Topic::publish(string flag,string name,string message){

	connection.send("TPUBLISH "+flag+" "+name+" #1"+Foo::endOfLine  );
	connection.send( Foo::toString( message.size() ) + Foo::endOfLine );
	connection.send(message + Foo::endOfLine );

	// No return value. Topic publish is a fire and forget operations
}
//-----------------------------------------------------------------------------
Topic::Topic(Connection& connection){
	this->connection=connection;
}
//-----------------------------------------------------------------------------
Topic::~Topic(){/*******/}
//-----------------------------------------------------------------------------
#endif

