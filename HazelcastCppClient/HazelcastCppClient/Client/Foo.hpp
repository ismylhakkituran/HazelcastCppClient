#ifndef Foo_hpp
#define Foo_hpp
//----------------------------------------------------------------------
#include <sstream>
#include <iosfwd>
#include <iostream>
#include <vector>
//---------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------
using std::string;
//----------------------------------------------------------------------
class Foo
{
 public:

	~Foo();
	Foo();

	int  						get					(int t,int y);
    static string 				endOfLine;
    static std::vector<string>  parse				(string);
    static std::vector<string>  parseLineToWords	(string);
    static string 				toString			(int);
    static string 				doubleToString		(double);
    static double				toDouble			(std::string);

};
//---------------------------------------------------------------------------------------

#endif
