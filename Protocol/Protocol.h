#include <iostream>
#include <string>

using namespace std;

class Protocol
{
public:
	Protocol();
	~Protocol();
	enum CMDS {
		CMD_FULLSTOP,
		CMD_UP,
		CMD_DOWN,
		CMD_LEFT,
		CMD_RIGHT,
		CMD_SHOOT,
		CMD_ALARM,
        CMD_LASER,
        CMD_LASEROFF
	};

	string constructString(CMDS command, char option);

	char * cmdArray;
	char createChecksum(CMDS command, char option);
};

