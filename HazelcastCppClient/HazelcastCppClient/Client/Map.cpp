#include <map>
#include <exception>
#include <iostream>

#include <atomic>
#include <thread>
#include <chrono>

#include "Map.hpp"
#include "HazelcastClient.hpp"
#include "ClientConfig.hpp"
#include "../Connection/Connection.hpp"
#include "../Connection/SocketException.h"
#include "Foo.hpp"
//---------------------------------------------------------------
using std::string;
//---------------------------------------------------------------
void Map::Stop() {
    myThread.join();
}
//---------------------------------------------------------------
void Map::startPut(int times,string toWrite,string& oldValue) {

	for(int i=0; i<times; i++){
		put(Foo::toString(i),Foo::toString(i),"0",true,Foo::toString(i),toWrite,oldValue );
	}
}
// ---------------------------------------------------------------
void Map::startGet(int times,string& oldValue) {

	for(int i=0; i<times; i++){
		get(Foo::toString(i),Foo::toString(i),Foo::toString(i),oldValue);
	}
}
// ---------------------------------------------------------------
Map::Map(Connection& connection ){
	client=connection;
	if(connection.is_valid()==false && client.is_valid()==false )
		std::cout<<"\nMap client is not valid";

}
// ---------------------------------------------------------------
Map::~Map(){

		std::cout<<"\nMap deconstructor rocks.";

}
// ---------------------------------------------------------------
bool Map::put(string flag,string name,string ttl,bool noreply,string key,string value,string& oldValue){
/*
 *			If noreply is provided, server will not return a response. If no old value exists it will return OK.
 * 			Note that if the key is locked by another thread then the operation will be blocked until the key is
 * 			unlocked.
 */
	string noReply="";
	if(noreply==true){ noReply="noreply "; }

	{
	  client.send("MPUT "+flag+" "+name+" "+ttl+" "+noReply+"#2"+Foo::endOfLine  );
	  client.send( Foo::toString( key.length() )+" "+ Foo::toString( value.length() )+Foo::endOfLine  );
	  client.send( key+value	+Foo::endOfLine );

		  return true;
	}
}
// ---------------------------------------------------------------
bool Map::puttransient(string flag,string name,string ttl,bool noreply,string key,string value){
	if(client.is_valid()==true )
	{
		string noReply;
		if(noreply)
			noReply="noreply";
		else
			noReply="";

	  client.send("MPUTTRANSIENT "+flag+" "+name+" "+ttl+" "+noReply+" #2"  +Foo::endOfLine );
	  client.send( Foo::toString( key.length() )+" "+ Foo::toString( value.length() ) +Foo::endOfLine );
	  client.send( key+value	+Foo::endOfLine );

	  std::string reply;
	  client.recv(reply);

	  if(reply.at(0)=='O'&& reply.at(1)=='K' )
		  return true;
	  else
		  return false;

	}
	else throw SocketException("\nClient is not valid, connection died.");
}
// ---------------------------------------------------------------
bool Map::set(string flag,string name,string ttl,bool noreply,string key,string value){
	if(client.is_valid()==true )
	{
		string noReply;
		if(noreply)
			noReply="noreply";
		else
			noReply="";

	  client.send("MSET "+flag+" "+name+" "+ttl+" "+noReply+" #2"+Foo::endOfLine );
	  client.send( Foo::toString( key.length() )+" "+ Foo::toString( value.length() )+Foo::endOfLine );
	  client.send( key+value	+Foo::endOfLine );

	  std::string reply;
	  client.recv(reply);

	  if(reply.at(0)=='O'&& reply.at(1)=='K' )
		  return true;
	  else
		  return false;

	}
	else throw SocketException("\nClient is not valid, connection died.");
}
// ---------------------------------------------------------------
bool Map::tryput(string flag,string name,string timeOut,string key,string value){
	if(client.is_valid()==true )
	{

	  client.send("MTRYPUT "+flag+" "+name+" "+" "+timeOut+" #2"+Foo::endOfLine );
	  client.send( Foo::toString( key.length() )+" "+ Foo::toString( value.length() )+Foo::endOfLine  );
	  client.send( key+value	+Foo::endOfLine  );

	  std::string reply;
	  client.recv(reply);

	  if(reply.at(0)=='O'&& reply.at(1)=='K' )
		  return true;
	  else
		  return false;

	}
	else throw SocketException("\nClient is not valid, connection died.");
}
// ---------------------------------------------------------------
bool Map::putall(string flag,string name,bool noreply,int putCount,std::vector<string> key,std::vector<string> value){

	if(key.size()==value.size() && value.size()==putCount ){

	if(client.is_valid()==true )
	{
		string noReply;
		if(noreply)
			noReply="noreply";
		else
			noReply="";

	  client.send("MPUTALL "+flag+" "+name+" "+" "+noReply+" #2"+Foo::toString(putCount) +Foo::endOfLine);
	  for(int i=0; i<putCount; i++)
		  client.send( Foo::toString( key[i].length() )+" "+ Foo::toString( value[i].length() )+" " );
		client.send( Foo::endOfLine );
	  for(int i=0; i<putCount; i++)
		  client.send( key[i]+value[i]	 );
		client.send( Foo::endOfLine );

	  std::string reply;
	  client.recv(reply);

	  if(reply.at(0)=='O'&& reply.at(1)=='K' )
		  return true;
	  else
		  return false;

	}
	else throw SocketException("\nClient is not valid, connection died.");
	}
	else throw SocketException("Key size is not equal to value size or putCount");
}
// ---------------------------------------------------------------
bool Map::putandunlock(string flag,string name,bool noreply,string key,string value){

	if(client.is_valid()==true )
	{
		string noReply;
		if(noreply)
			noReply="noreply";
		else
			noReply="";

	  client.send("MPUTANDUNLOCK "+flag+" "+name+" "+" "+noReply+" #2"+Foo::endOfLine);
	  client.send( Foo::toString( key.length() )+" "+ Foo::toString( value.length() ) +Foo::endOfLine);
	  client.send( key+value	+Foo::endOfLine );

	  std::string reply;
	  client.recv(reply);

	  if(reply.at(0)=='O'&& reply.at(1)=='K' )
		  return true;
	  else
		  return false;

	}
	else throw SocketException("\nClient is not valid, connection died.");


}
// ---------------------------------------------------------------
bool Map::trylockandget(string flag,string name,string timeOut,string key,string& value){
	if(client.is_valid()==true )
	{
	  client.send("MTRYLOCKANDGET "+flag+" "+name+" "+" "+timeOut+" #1"+Foo::endOfLine);
	  client.send( Foo::toString( key.length() )+Foo::endOfLine );
	  client.send( key +Foo::endOfLine);

	  std::string reply;
	  client.recv(reply);														// reply parse edilip value ya eşlenecek 2.satır->value.size()
	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	//                                       3.satır->value

	  if(reply.at(0)=='O'&& reply.at(1)=='K' )
		  return true;
	  else
		  return false;

	}
	else throw SocketException("\nClient is not valid, connection died.");
}
// ---------------------------------------------------------------
bool Map::get(string flag,string name,string key,string& value){
	//if(client.is_valid()==true )
	{
	  client.send("MGET "+flag+" "+name+" #1"+Foo::endOfLine);
	  client.send( Foo::toString( key.length() ) +Foo::endOfLine);
	  client.send( key +Foo::endOfLine);

	  std::string reply;
	  client.recv(reply);

	  std::vector<string> lines=Foo::parse(reply);
	  value=lines[lines.size()-1];

	  if(reply[0]=='O'&& reply[1]=='K' )
		  return true;
	  else
		  return false;

	}
	//else throw SocketException("\nClient is not valid, connection died.");
}
// ---------------------------------------------------------------
bool Map::getall(string flag,string name,int getCount,std::vector<string> key,std::vector<string>& value){

	if(key.size()==value.size() && value.size()==getCount ){

	if(client.is_valid()==true )
	{
	  client.send("MGETALL "+flag+" "+name+" #"+Foo::toString(getCount)+Foo::endOfLine );

	  for(int i=0; i<getCount; i++)
		  client.send( Foo::toString( key[i].length() )+" ");				// son konulan boşluk sıkıntı olur mu ?
	    client.send(Foo::endOfLine);
	  for(int i=0; i<getCount; i++)
		  client.send( key[i]	 );
	    client.send(Foo::endOfLine);

	  std::string reply; 												//// return parse edilecek value vectorne basılacak...........
	  client.recv(reply);

	  if(reply.at(0)=='O'&& reply.at(1)=='K' )
		  return true;
	  else
		  return false;

	}
	else throw SocketException("\nClient is not valid, connection died.");
	}
	else throw SocketException("Key size is not equal to value size or putCount");
}
// ---------------------------------------------------------------
bool Map::remove(string flag,string name,bool noreply,string key,string& value){

	if(client.is_valid()==true )
	{
		string noReply;
		if(noreply)
			noReply="noreply";
		else
			noReply="";

	  client.send("MREMOVE "+flag+" "+name+" "+noReply+" #1"+Foo::endOfLine);
	  client.send( Foo::toString( key.length() ) +Foo::endOfLine);
	  client.send( key +Foo::endOfLine);
	  	  	  	  	  	  	  	  	  	  	  	  	  //return parse edilip value ye eşlenecek
	  std::string reply;
	  client.recv(reply);

	  if(reply.at(0)=='O'&& reply.at(1)=='K' )
		  return true;
	  else
		  return false;

	}
	else throw SocketException("\nClient is not valid, connection died.");
}
// ---------------------------------------------------------------
bool Map::tryremove(string flag,string name,string timeOut,string key,string& value){

	if(client.is_valid()==true )
	{

	  client.send("MTRYREMOVE "+flag+" "+name+" "+timeOut+" #1"+Foo::endOfLine);
	  client.send( Foo::toString( key.length() ) +Foo::endOfLine);
	  client.send( key +Foo::endOfLine);
	  	  	  	  	  	  	  	  	  	  	  	  	  //return parse edilip value ye eşlenecek
	  std::string reply;
	  client.recv(reply);

	  if(reply.at(0)=='O'&& reply.at(1)=='K' )
		  return true;
	  else
		  return false;

	}
	else throw SocketException("\nClient is not valid, connection died.");
}
// ---------------------------------------------------------------
bool Map::getentry(string flag,string name,string key,string& costInBytes,string& expirationTime,string& hits,
	  	  	  string& lastAccessTime,string& lastStoredime,string& value	){

	if(client.is_valid()==true )
	{

	  client.send("MGETENTRY "+flag+" "+name+" #1"+Foo::endOfLine);
	  client.send( Foo::toString( key.length() ) +Foo::endOfLine);
	  client.send( key +Foo::endOfLine);
	  	  	  	  	  	  	  	  	  	  	  	  	  //return parse edilip parametreler e ye eşlenecek
	  std::string reply;
	  client.recv(reply);

	  if(reply.at(0)=='O'&& reply.at(1)=='K' )
		  return true;
	  else
		  return false;

	}
	else throw SocketException("\nClient is not valid, connection died.");

}
// ---------------------------------------------------------------
bool Map::keyset(string flag,string type,string name,std::vector<string>& key){

	if(client.is_valid()==true )
	{

	  client.send("KEYSET "+flag+" "+type+" "+name+Foo::endOfLine);
	 	  	  	  	  	  	  	  	  	  	  	  	  	  //return parse edilip parametreler e ye eşlenecek
	  std::string reply;
	  client.recv(reply);

	  if(reply.at(0)=='O'&& reply.at(1)=='K' )
		  return true;
	  else
		  return false;

	}
	else throw SocketException("\nClient is not valid, connection died.");

}// ---------------------------------------------------------------
bool Map::lock(string flag,string name,string key){

	if(client.is_valid()==true )
	{

	  client.send("MLOCK "+flag+" "+name+" #1"+Foo::endOfLine);
	  client.send(Foo::toString(key.size())+Foo::endOfLine);
	  client.send(key+Foo::endOfLine);

	  std::string reply;
	  client.recv(reply);

	  if(reply=="OK "+flag  )
		  return true;
	  else
		  return false;

	}
	else throw SocketException("\nClient is not valid, connection died.");
}
// ---------------------------------------------------------------
bool Map::unlock(string flag,string name,string key){

	if(client.is_valid()==true )
	{

	  client.send("MUNLOCK "+flag+" "+name+" #1"+Foo::endOfLine);
	  client.send(Foo::toString(key.size())+Foo::endOfLine);
	  client.send(key+Foo::endOfLine);

	  std::string reply;
	  client.recv(reply);

	  if(reply=="OK "+flag )
		  return true;
	  else
		  return false;

	}
	else throw SocketException("\nClient is not valid, connection died.");
}
// ---------------------------------------------------------------
bool Map::trylock(string flag,string name,string timeOut,string key){ //<isacquired?>

	if(client.is_valid()==true )  												// henüz kodlanmamış test edemiyoruz.
	{

	  client.send("MTRYLOCK "+flag+" "+name+" "+timeOut+" #1"+Foo::endOfLine);
	  client.send(Foo::toString(key.size())+Foo::endOfLine);
	  client.send(key+Foo::endOfLine);

	  std::string reply;
	  client.recv(reply);

	  if(reply.substr(0,2)=="OK" )
		  return true;
	  else
		  return false;

	}
	else throw SocketException("\nClient is not valid, connection died.");
}
// ---------------------------------------------------------------
bool Map::iskeylocked(string flag,string name,string key){

	if(client.is_valid()==true )
	{

	  client.send("MISKEYLOCKED "+flag+" "+name+" #1"+Foo::endOfLine);
	  client.send(Foo::toString(key.size())+Foo::endOfLine);
	  client.send(key+Foo::endOfLine);

	  std::string reply;
	  client.recv(reply);

	  if(reply.substr(0,2)=="OK" )
		  return true;
	  else
		  return false;

	}
	else throw SocketException("\nClient is not valid, connection died.");
}
// ---------------------------------------------------------------
bool Map::lockmap(string flag,string name,string timeOut){

	if(client.is_valid()==true )
	{

	  client.send("MLOCKMAP "+flag+" "+name+" "+timeOut+" #1"+Foo::endOfLine);
	  std::string reply;
	  client.recv(reply);

	  if(reply.substr(0,2)=="OK" )
		  return true;
	  else
		  return false;

	}
	else throw SocketException("\nClient is not valid, connection died.");
}
// ---------------------------------------------------------------
bool Map::unlockmap(string flag,string name,string timeOut){

	if(client.is_valid()==true )
	{

	  client.send("MUNLOCKMAP "+flag+" "+name+" "+timeOut+" #1"+Foo::endOfLine);
	  std::string reply;
	  client.recv(reply);

	  if(reply.substr(0,2)=="OK" )
		  return true;
	  else
		  return false;

	}
	else throw SocketException("\nClient is not valid, connection died.");
}
// ---------------------------------------------------------------
bool Map::forceunlock(string flag,string name,string key){

	if(client.is_valid()==true )
	{

	  client.send("MFORCEUNLOCK "+flag+" "+name+" #1"+Foo::endOfLine);
	  client.send(Foo::toString(key.size()) );
	  client.send(key);

	  std::string reply;
	  client.recv(reply);

	  if(reply=="OK "+flag )
		  return true;
	  else
		  return false;

	}
	else throw SocketException("\nClient is not valid, connection died.");
}
// ---------------------------------------------------------------
bool Map::containskey(string flag,string name,string key){

	if(client.is_valid()==true )
	{

	  client.send("MCONTAINSKEY "+flag+" "+name+" #1"+Foo::endOfLine);
	  client.send(Foo::toString(key.size()) );
	  client.send(key);

	  std::string reply;
	  client.recv(reply);

	  if(reply.substr(0,2)=="OK")
		  return true;
	  else
		  return false;

	}
	else throw SocketException("\nClient is not valid, connection died.");
}
// ---------------------------------------------------------------
bool Map::containsvalue(string flag,string name,string value){

	if(client.is_valid()==true )
	{

	  client.send("MCONTAINSVALUE "+flag+" "+name+" #1"+Foo::endOfLine);
	  client.send(Foo::toString(value.size()) );
	  client.send(value);

	  std::string reply;
	  client.recv(reply);

	  if(reply.substr(0,2)=="OK")
		  return true;
	  else
		  return false;

	}
	else throw SocketException("\nClient is not valid, connection died.");
}
// ---------------------------------------------------------------
bool Map::putifabsent(string flag,string name,string ttl,bool noreply,string key,string value,string& replyValue){

	if(client.is_valid()==true )
	{
		string noReply;
		if(noreply)
			noReply="noreply";
		else
			noReply="";

	  client.send("MPUTIFABSENT "+flag+" "+name+" "+ttl+" "+noReply+" #2"+Foo::endOfLine);
	  client.send( Foo::toString( key.length() )+" "+Foo::toString( value.length() ) +Foo::endOfLine);
	  client.send( key+value+Foo::endOfLine);
	  	  	  	  	  	  	  	  	  	  	  	  	  //return parse edilip replyvalue ye eşlenecek
	  std::string reply;
	  client.recv(reply);

	  if(reply.at(0)=='O'&& reply.at(1)=='K' )
		  return true;
	  else
		  return false;

	}
	else throw SocketException("\nClient is not valid, connection died.");
}
// ---------------------------------------------------------------
// ---------------------------------------------------------------
























