#include "UART.h"

/*
 * UARTQueue class implementation
 */
UARTQueue::UARTQueue() {
    std::cout << "Creating UARTQueue." << std::endl;
}

void UARTQueue::post(std::string data, int bytes) {
    QMutexLocker lock(&mut);
    items.push(UARTItem(data, bytes));
    postWait.wakeOne();
}

UARTItem UARTQueue::get() {
    QMutexLocker lock(&mut);
    while (items.empty()) {
        postWait.wait(&mut);
    }

    UARTItem item = items.front();
    items.pop();

    return item;
}

UARTQueue::~UARTQueue() {
    std::cout << "Destroying UARTQueue." << std::endl;
}

/*
 * UART class implementation
 */
UART::UART(const char *device, int baudRate, UARTQueue *queue) : queue(queue) {
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

void UART::run() {
    running = true;

    while (running) {
        UARTItem item = queue->get();
        handle(item);
    }

    std::cout << "UART run loop over!" << std::endl;
}

void UART::handle(UARTItem &item) {
    std::string cmd = item.data;
    int bytes = item.bytes;
    send(cmd, bytes);
}

void UART::stop() {
    running = false;
}

void UART::send(std::string data, int bytes) {
    std::cout << "Sending string over UART!" << std::endl;
	for (int i = 0; i < bytes; i++) {
		serialPutchar(fd, data[i]);
	}
}
