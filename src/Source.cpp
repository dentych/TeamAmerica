#include "Protocol.h"


int main() {

	Protocol p;
	cout << p.createChecksum(Protocol::CMD_DOWN, 50) << endl;
	cout << p.constructString(Protocol::CMD_DOWN, 50) << endl;

}