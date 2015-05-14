#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "../SPI/SensorsSPI.h"
#include "../UART/UART.h"
#include "../Protocol/Protocol.h"
#include <iostream>
#include <QThread>

class JoystickThread : public QThread {
public:
    JoystickThread(UARTQueue *uartQueue);
    void enableAlarm();
    void disableAlarm();
    void handleXCord(int xCord);
    void handleYCord(int yCord);
    void handleTrigger(int trig);

    void run();
    void stop();

private:
    SensorsSPI *spi;
    UARTQueue *uartQueue;
    Protocol protocol;
    int lastX, lastY;
    bool alarmEnabled;
    bool running;
};

#endif
