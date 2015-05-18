#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "../SPI/SensorsSPI.h"
#include "../UART/UART.h"
#include "../Protocol/Protocol.h"
#include "../Log/Log.h"
#include <iostream>
#include <unistd.h>
#include <QThread>
#include <QLabel>

class JoystickThread : public QThread {
public:
    JoystickThread(UARTQueue *uartQueue, QLabel *shotLabel, int *shots);
    void enableAlarm();
    void disableAlarm();
    void stop();

private:
    void handleXCord(int xCord);
    void handleYCord(int yCord);
    void handleTrigger(int trig);
    void handleAlarm(int alarm);

protected:
    void run();

private:
    SensorsSPI *spi;
    UARTQueue *uartQueue;
    Protocol protocol;
    int lastX, lastY, lastTrig;
    int alarmCooldown;
    QLabel *shotLabel;
    int *shots;
    bool running, alarmEnabled;

    static int objectCount;
};

#endif
