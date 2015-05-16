#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "../SPI/SensorsSPI.h"
#include "../UART/UART.h"
#include "../Protocol/Protocol.h"
#include <iostream>
#include <unistd.h>
#include <QThread>

class JoystickThread : public QThread {
public:
    JoystickThread(UARTQueue *uartQueue);
    static void enableAlarm();
    static void disableAlarm();

private:
    void handleXCord(int xCord);
    void handleYCord(int yCord);
    void handleTrigger(int trig);
    void handleAlarm(int alarm);

    void run();
    void stop();

private:
    SensorsSPI *spi;
    UARTQueue *uartQueue;
    Protocol protocol;
    int lastX, lastY, lastTrig;
    int alarmCooldown;
    bool running;

    static bool alarmEnabled;
    static int objectCount;
};

#endif
