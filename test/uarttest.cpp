#include "../UART/UART.h"

int main() {
    UARTQueue queue;

    UART uart("/dev/ttyAMA0", 9600, &queue);

    queue.post("string", 6);
    
    uart.wait();
}
