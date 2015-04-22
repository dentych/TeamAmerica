#include <iostream>
#include "../inc/UART.h"

using namespace std;

int main() {
	cout << "UART test." << endl;

	UART cake("/dev/ttyAMA0", 9600);

	return 0;
}
