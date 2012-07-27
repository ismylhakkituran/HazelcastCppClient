// Definition of the ClientConfig class

#ifndef GroupConfig_class
#define GroupConfig_class

#include <string>
// -----------------------------------------------------------------------------------

class GroupConfig // : private Socket
{
 public:

	 GroupConfig ( );
    ~GroupConfig ( );

    bool        isLogin         (std::string);
    std::string getLoginFlag    (           );

    void setName     	 (std::string);
  	void setPassword 	 (std::string);
    void setProtocolType (std::string);
    void setGroupName    (std::string);


  	std::string getPassword  	 ( );
    std::string getGroupName     ( );
    std::string getName			 ( );
    std::string getProtocolType  ( );

 private:
  	std::string Name,
  				LoginFlag,
  				GroupName,
  				Password,
  				ProtocolType;

  };
// -----------------------------------------------------------------------------------

#endif
