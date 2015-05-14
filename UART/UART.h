#ifndef UART_H_
#define UART_H_

#include <wiringSerial.h>
#include <iostream>
#include <string>
#include <queue>

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
//#include "Log.h"

struct UARTItem {
    // Constructor for parsing values when creating the struct object.
    UARTItem(std::string data, int bytes) : data(data), bytes(bytes) {}
    std::string data;
	int bytes;
};

class UARTQueue {
    public:
        UARTQueue();
		void post(std::string data, int bytes);
        UARTItem get();
        ~UARTQueue();
	
	private:
        std::queue<UARTItem> items;
		QMutex mut;
        QWaitCondition postWait;
};

class UART : public QThread {
	public:
		UART(const char *device, int baudRate, UARTQueue *queue);
		~UART();
		void run();
        void stop();
        void handle(UARTItem &item);
		void send(std::string data, int bytes);

	private:
		int fd;
		UARTQueue *queue;
        bool running;
};

#endif
