#include "Protocol.h"

using namespace std;
Protocol::Protocol(){
	
	cmdArray = new char[9];

	cmdArray[CMD_FULLSTOP] = 'F';
	cmdArray[CMD_UP] = 'O';
	cmdArray[CMD_DOWN] = 'N';
	cmdArray[CMD_LEFT] = 'V';
	cmdArray[CMD_RIGHT] = 'H';
	cmdArray[CMD_SHOOT] = 'S';
	cmdArray[CMD_ALARM] = 'A';
    cmdArray[CMD_LASER] = 'L';
    cmdArray[CMD_LASEROFF] = 'K';
}

Protocol::~Protocol() {
	delete[] cmdArray;
}

string Protocol::constructString(CMDS command, char option) {
	string out;
	out.push_back('1');
	out.push_back(cmdArray[command]);
	out.push_back(option);
	out.push_back(createChecksum(command, option));
	return out;
}

char Protocol::createChecksum(CMDS command, char option) {
	char checksum = cmdArray[command] ^ option;
	return checksum;
}
