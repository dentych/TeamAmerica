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
    JoystickThread(UARTQueue *uartQueue, QLabel *shotLabel, int *shots, QLabel *msg);
    void enableAlarm();
    void disableAlarm();
    void enableJoystick();
    void disableJoystick();
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
	Log *log;
    int lastX, lastY, lastTrig, alarmCooldown;
    QLabel *shotLabel, *msg;
    int *shots;
    bool running, alarmEnabled, joystickActive;

    static int objectCount;
};

#endif
