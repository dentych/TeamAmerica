#include <iostream>
#include "../inc/UART.h"

int main() {
	cout << "UART test." << endl;

	UART cake("/dev/ttyAMA0", 9600);

	return 0;
}
