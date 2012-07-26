// Definition of the ClientConfig class

#ifndef GroupConfig_class
#define GroupConfig_class
// -----------------------------------------------------------------------------------

class GroupConfig // : private Socket
{
 public:

	GroupConfig ( );
    ~GroupConfig();
  	std::string Name;
  	std::string Password;
  	bool setGroupName(std::string);
  };
// -----------------------------------------------------------------------------------

#endif
