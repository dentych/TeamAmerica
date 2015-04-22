#include <iostream>
#include <string>

using namespace std;

class Protocol
{
public:
	Protocol();
	enum CMDS {
		CMD_FULLSTOP,
		CMD_UP,
		CMD_DOWN,
		CMD_LEFT,
		CMD_RIGHT,
		CMD_SHOOT,
		CMD_RESET
	};

	string constructString(CMDS command, char option);

	char * cmdArray;
	char createChecksum(CMDS command, char option);
};

