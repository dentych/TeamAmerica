#include "camerafeed.h"
#include <QApplication>
#include <QWidget>
#include "login.h"
#include <iostream>
#include <wiringSerial.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    wiringPiSetupGpio();

    UARTQueue *uartQueue = new UARTQueue();
    UART *uart = new UART("/dev/ttyAMA0", 9600, uartQueue);
    uart->start();
    JoystickThread *joystick = new JoystickThread(uartQueue);
    joystick->start();

    Login window(uartQueue, uart, joystick);
    window.showFullScreen();
    window.setWindowTitle("Login");
    window.show();

    int ret = a.exec();

    // Disable joystick and shizzle.
    joystick->stop();
    uart->stop();

    uartQueue->post("0", 1);

    while (joystick->isRunning()) { /* WAIT TIME */ }
    if (!joystick->isRunning()) delete joystick;

    while (uart->isRunning()) { /* WAIT TIME */ }
    if (!uart->isRunning()) delete uart;

    delete uartQueue;

    return ret;


}
