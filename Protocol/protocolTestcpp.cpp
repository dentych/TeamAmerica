#include "Protocol.h"

int main() {
	std::cout << "Constructing protocol object..\n";
	{
		Protocol p;

		std::cout << "Testing createChecksum.. \n";
		std::cout << "Checksum of CMD_LASER ^ option = '0' is " << p.createChecksum(Protocol::CMD_LASER, 0);

		std::cout << "Testing constructString with all commands..\n";
		std::cout << "CMD_FULLSTOP = 'F'\n";
		std::cout << p.constructString(Protocol::CMD_FULLSTOP, '0') << endl;
		std::cout << "CMD_UP = 'O'\n";
		std::cout << p.constructString(Protocol::CMD_UP, '1') << endl;
		std::cout << "CMD_DOWN = 'N'\n";
		std::cout << p.constructString(Protocol::CMD_DOWN, '1') << endl;
		std::cout << "CMD_LEFT = 'V'\n";
		std::cout << p.constructString(Protocol::CMD_LEFT, '2') << endl;
		std::cout << "CMD_RIGHT = 'H'\n";
		std::cout << p.constructString(Protocol::CMD_RIGHT, '2') << endl;
		std::cout << "CMD_SHOOT = 'S'\n";
		std::cout << p.constructString(Protocol::CMD_SHOOT, '0') << endl;
		std::cout << "CMD_ALARM = 'A'\n";
		std::cout << p.constructString(Protocol::CMD_ALARM, '0') << endl;
		std::cout << "CMD_LASER = 'L'\n";
		std::cout << p.constructString(Protocol::CMD_LASER, '0') << endl;
		std::cout << "CMD_LASEROFF = 'K'\n";
		std::cout << p.constructString(Protocol::CMD_LASEROFF, '0') << endl;

		std::cout << "End of Test..\n";
	}
	return 0;
}