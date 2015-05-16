#include "../Joystick/Joystick.h"

int main() {
    UARTQueue queue;
    UART uart("/dev/ttyAMA0", 9600, &queue);
    uart.start();
    JoystickThread joystick(&queue);
    joystick.start();

    uart.wait();
    joystick.wait();
}
