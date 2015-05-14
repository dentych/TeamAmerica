#include "Joystick.h"

JoystickThread::JoystickThread(UARTQueue *uartQueue) : uartQueue(uartQueue) {
    spi = new SensorsSPI("/dev/spidev0.0", SPI_MODE_0, 3000000, 8);
    alarmEnabled = true;
}

void JoystickThread::enableAlarm() {
    alarmEnabled = true;
}

void JoystickThread::disableAlarm() {
    alarmEnabled = false;
}

void JoystickThread::run() {
    std::cout << "Joystick running!" << std::endl;
    running = true;

    while (running) {
        int xCord, yCord, trigger;
        xCord = spi->JoystickX();
        yCord = spi->JoystickY();
        trigger = spi->JoystickTrig();

        handleXCord(xCord);
        handleYCord(yCord);
        handleTrigger(trigger);
    }
}

void JoystickThread::handleXCord(int xCord) {
    if (xCord < 100 && lastX > 450) {
        char option = 50;
        uartQueue->post(
                    protocol.constructString(Protocol::CMD_LEFT, option), 4);
        lastX = xCord;
    }
    else if (xCord > 450 && xCord < 550) {
        if (lastX < 100 || lastX > 800) {
            uartQueue->post(protocol.constructString(Protocol::CMD_FULLSTOP, '0'), 4);
            lastX = xCord;
        }
    }
    else if (xCord > 800 && lastX < 550) {
        uartQueue->post(protocol.constructString(Protocol::CMD_RIGHT, '0'), 4);
        lastX = xCord;
    }
}

void JoystickThread::handleYCord(int yCord) {
    if (yCord < 100 && lastY > 450) {
        char option = 50;
        uartQueue->post(
                    protocol.constructString(Protocol::CMD_DOWN, option), 4);
        lastY = yCord;
    }
    else if (yCord > 450 && yCord < 550) {
        if (lastY < 100 || lastY > 800) {
            uartQueue->post(protocol.constructString(Protocol::CMD_FULLSTOP, '0'), 4);
            lastY = yCord;
        }
    }
    else if (yCord > 800 && lastY < 550) {
        uartQueue->post(protocol.constructString(Protocol::CMD_UP, '0'), 4);
        lastY = yCord;
    }
}

void JoystickThread::handleTrigger(int trig) {

}

void JoystickThread::stop() {
    running = false;
    this->exit();
}
