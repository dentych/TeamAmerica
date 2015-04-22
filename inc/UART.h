#ifndef UART_H_
#define UART_H_

#include <wiringSerial.h>
#include <string>
//#include "Log.h"

class UART {
	public:
		UART(char *device, int baudRate);
		~UART();
		void send(std::string data, int bytes);
		std::string receive(int bytes);

	private:
		int fd;
};

#endif
