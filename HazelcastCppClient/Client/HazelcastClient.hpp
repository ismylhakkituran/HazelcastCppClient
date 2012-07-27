// Definition of the ClientConfig class

#ifndef HazelcastClient_class
#define HazelcastClient_class

#include <vector>
#include "ClientConfig.hpp"
#include "../Connection/Connection.hpp"

using std::string;

class HazelcastClient     // : private Socket
{
 public:

	 HazelcastClient     ( ClientConfig& clientconfig );
	~HazelcastClient     ( );

	void auth       (ClientConfig& clientconfig);

	bool destroy    (string flag,string type,string name);
	bool trxbegin   (string flag);
	bool trxcommit  (string flag);
	bool trxrollback(string flag);
	bool instances  (string flag,std::vector<string>& type,std::vector<string>& instance );		//   will  be   parse
	bool members    (string flag,std::vector<string>& members);                                 //   will  be   parse
	bool clustertime(string flag,string& time);
	bool ping       (string flag);
	bool partitions (string flag,string key,string& pid,string& adress);						//   will  be   parse
	bool partitions (string flag,std::vector<string>& pid,std::vector<string>& adress);			//   will  be   parse
	Connection connection;


 private:
	//Connection socket;
    std::string endOfLine;


};
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------

#endif
