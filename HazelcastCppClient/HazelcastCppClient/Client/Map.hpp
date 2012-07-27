#ifndef Map_class
#define Map_class

#include <map>
#include <vector>
#include <thread>

#include "HazelcastClient.hpp"
#include "../Connection/Connection.hpp"
#include "ClientConfig.hpp"
#include "Foo.hpp"


using std::string;

class Map : public std::thread
{
 public:

   Map (Connection&);
  ~Map (  );

  void startPut (int,string,string&);
  void startGet (int,string&);
  void Stop     ();

  string getMap          ();
  bool get               (string flag,string name,string key,string& value);
  bool getall            (string flag,string name,int getCount,std::vector<string> key,std::vector<string>& value);
  bool put				 (string flag,string name,string ttl,bool noreply,string key,string value,string& oldValue);
  bool tryput		 	 (string flag,string name,string timeOut,string key,string value);
  bool set			 	 (string flag,string name,string ttl,bool noreply,string key,string value);
  bool puttransient 	 (string flag,string name,string ttl,bool noreply,string key,string value);
  bool putandunlock 	 (string flag,string name,bool noreply,string key,string value);
  bool remove		 	 (string flag,string name,bool noreply,string key,string& value);
  bool tryremove		 (string flag,string name,string timeOut,string key,string& value);
 // bool removeitem   	 ();
  bool containskey  	 (string flag,string name,string key);
  bool containsvalue	 (string flag,string name,string value);  //flag,name,time_out,reply
 // bool addlistener	 	 ();
  bool event		 	 ();
 // bool removelistener    ();
  bool keyset		 	 (string flag,string type,string name,std::vector<string>& key);
 // bool entryset	      	 ();
  bool getentry	 		 (string flag,string name,string key,string& costInBytes,string& expirationTime,string& hits,
		  	  	  	  	  string& lastAccessTime,string& lastStoredime,string& value	);
  bool lock		 		 (string flag,string name,string key);
 // bool iskeylocked	  	 ();
  bool unlock	     	 (string flag,string name,string key);
  bool trylock			 (string flag,string name,string timeOut,string key); //<isacquired?> ??
  bool iskeylocked	  	 (string flag,string name,string key); //<isLocked?> true/false ???    ^
  bool lockmap	 	 	 (string flag,string name,string timeOut);
  bool unlockmap     	 (string flag,string name,string timeOut);
  bool forceunlock  	 (string flag,string name,string key);
  bool putall		 	 (string flag,string name,bool noreply,int putCount,std::vector<string> key,std::vector<string> value);
  bool putifabsent  	 (string flag,string name,string ttl,bool noreply,string key,string value,string& replyValue);
 // bool removeifsame     ();
 // bool replaceifnotnull ();
 // bool replaceifsame    ();
  bool trylockandget	 (string flag,string name,string timeOut,string key,string& value);
 // bool flush			 ();
 // bool evcit			 ();
 // bool addlistener	     ();
 // bool removelistener   ();

  /*MGET, MGETALL, MPUT, MTRYPUT, MSET, MPUTTRANSIENT, MPUTANDUNLOCK, MREMOVE,
  MREMOVEITEM, MCONTAINSKEY, MCONTAINSVALUE, ADDLISTENER, EVENT, REMOVELISTENER,
  KEYSET, ENTRYSET, MGETENTRY, MLOCK, MISKEYLOCKED, MUNLOCK, MLOCKMAP, MUNLOCKMAP,
  MFORCEUNLOCK, MPUTALL, MPUTIFABSENT, MREMOVEIFSAME, MREPLACEIFNOTNULL,
  MREPLACEIFSAME, MTRYLOCKANDGET, MFLUSH, MEVICT, MADDLISTENER, MREMOVELISTENER
*/

 private:
    std::thread myThread;

    Connection client;
};
#endif
