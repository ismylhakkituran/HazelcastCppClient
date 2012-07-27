#include "GroupConfig.hpp"

//-------------------------------------------------------------------
std::string GroupConfig::getPassword  ( ){

	return this->Password;
}
//-------------------------------------------------------------------
std::string GroupConfig::getName(){

	return this->Name;
}
//-------------------------------------------------------------------
std::string GroupConfig::getGroupName ( ){

	return this->Name;
}
//-------------------------------------------------------------------
std::string GroupConfig::getProtocolType(){

	return this->ProtocolType;
}
//-------------------------------------------------------------------
void GroupConfig::setProtocolType(std::string prtcltype){

	this->ProtocolType=prtcltype;
}
//-------------------------------------------------------------------
void GroupConfig::setGroupName(std::string grpname){

	this->GroupName=grpname;
}
//-------------------------------------------------------------------
void GroupConfig::setName(std::string name){

	this->Name=name;
}
//-------------------------------------------------------------------
void GroupConfig::setPassword(std::string pass){

	this->Password=pass;
}
bool GroupConfig::isLogin(std::string islgn){

	if(islgn==LoginFlag)
		return true;

	else
		return false;
}
std::string GroupConfig::getLoginFlag(){

	return LoginFlag;
}
//-------------------------------------------------------------------
GroupConfig::GroupConfig(){

	ProtocolType = "P01";
	Name		 = "dev";
	Password	 = "dev-pass";
	LoginFlag	 = "6141";
}
//-------------------------------------------------------------------
GroupConfig::~GroupConfig(){
	//..................
}
//-------------------------------------------------------------------

