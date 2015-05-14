#include "../UART/UART.h"

int main() {
    UARTQueue queue;

    UART uart("/dev/ttyAMA0", 9600, &queue);

    while (1) {
        // LELELELELE
    }
}
