#include <sstream>
#include <iosfwd>
#include <iostream>
#include <vector>
#include <stdlib.h>
//----------------------------------------------------------------------
#include "Foo.hpp"
//---------------------------------------------------------------------------------------
using std::string;
//---------------------------------------------------------------------------------------
double Foo::toDouble(string toConvert){
    double temp = ::atof(toConvert.c_str());
    return temp;
}
//---------------------------------------------------------------------------------------
std::vector<string> Foo::parseLineToWords(string toParse){

	std::vector<string> parsed;

	int to,from;   from=0;
	bool run=true;
	while(run){
		to=toParse.find(" ",from);
		if(to>=0 && to<=toParse.size()+1 ){
			parsed.push_back(toParse.substr(from,to-from) );
			to=to+2;
			from=to;
		}
		else
			run=false;
	}
	return parsed;
}
//---------------------------------------------------------------------------------------
Foo::~Foo(){
	//std::cout<<std::endl<<"Foo deconst is running";
}
//---------------------------------------------------------------------------------------
int Foo::get(int t,int y){
	std::cout<<"\n"<<t;
	return t;
}
//---------------------------------------------------------------------------------------
Foo::Foo(){
//	Foo::endOfLine="\r\n";
}
//---------------------------------------------------------------------------------------
string Foo::endOfLine="\r\n";
//---------------------------------------------------------------------------------------
std::vector<string> Foo::parse(string toParse){

	std::vector<string> parsed;

	int to,from;   from=0;
	bool run=true;
	while(run){
		to=toParse.find("\r\n",from);//std::cout<<" f:"<<from<<" t:"<<to;
		if(to>=0 && to<=toParse.size()+1 ){
			parsed.push_back(toParse.substr(from,to-from) );
			to=to+2;
			from=to;
		}
		else
			run=false;
	}
	return parsed;
}
//---------------------------------------------------------------------------------------
string Foo::toString(int temp){

	string numb;
	std::stringstream out;
	out << temp;
	numb=out.str();
	return numb;
}
//---------------------------------------------------------------------------------------
string Foo::doubleToString(double temp){

	string numb;
	std::stringstream out;
	out << temp;
	numb=out.str();
	return numb;
}
