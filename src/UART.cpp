#include "../inc/UART.h"

UART::UART(char *device, int baudRate) {
	fd = serialOpen(device, baudRate);

	if (fd < 0) {
		//log.writeLog(Log::uart);
	}
}

UART::~UART() {
	if (fd >= 0) {
		serialClose(fd);
	}
}

void UART::send(char data[], int bytes) {
	// SEND SHIT
}

std::string UART::receive(int bytes) {
	// MODTAG SHIT
}
