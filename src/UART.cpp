#include "../inc/UART.h"

UART::UART(const char *device, int baudRate) {
	fd = serialOpen(device, baudRate);

	if (fd < 0) {
		//log.writeLog(Log::uart);
		std::cout << "Can't connect to UART device." << std::endl;
	}
}

UART::~UART() {
	if (fd >= 0) {
		serialClose(fd);
	}
}

void UART::send(std::string data, int bytes) {
	for (int i = 0; i < bytes; i++) {
		serialPutchar(fd, data[i]);
	}
}
