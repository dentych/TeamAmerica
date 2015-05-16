#include "Joystick.h"

JoystickThread::JoystickThread(UARTQueue *uartQueue) : uartQueue(uartQueue) {
    spi = new SensorsSPI("/dev/spidev0.0", SPI_MODE_0, 3000000, 8);
    alarmEnabled = true;
    lastX = 0;
    lastY = 0;
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

        usleep(250000);
    }
}

void JoystickThread::handleXCord(int xCord) {
    Protocol::CMDS direction;
    int xDelta = xCord - 512;
    int stopCount = 0;

    if (xDelta > 0) {
        direction = Protocol::CMD_RIGHT;
    }
    else {
        xDelta *= (-1);
        direction = Protocol::CMD_LEFT;
    }

    if (xDelta < 100 && lastX != 0) {
        lastX = 0;
        uartQueue->post(protocol.constructString(CMD_FULLSTOP, 0), 4);
    }
    else if (xDelta < 400 && lastX != 1) {
        lastX = 1;
        uartQueue->post(protocol.constructString(direction, '1'), 4);
    }
    else if (xDelta > 400 && lastX != 2) {
        lastX = 2;
        uartQueue->post(protocol.constructString(direction, '2'), 4);
    }
}

void JoystickThread::handleYCord(int yCord) {
    Protocol::CMDS direction;
    int yDelta = yCord - 512;

    if (yDelta > 0) {
        direction = Protocol::CMD_UP;
    }
    else {
        yDelta *= (-1);
        direction = Protocol::CMD_DOWN;
    }

    if (yDelta > 340 && lastY != 3) {
        lastY = 3;
        uartQueue->post(protocol.constructString(direction, '3'), 4);
    }
    else if (yDelta < 340 && yDelta > 170 && lastY != 2) {
        lastY = 2;
        uartQueue->post(protocol.constructString(direction, '2'), 4);
    }
    else if (yDelta < 170 && yDelta > 50 && lastY != 1) {
        lastY = 1;
        uartQueue->post(protocol.constructString(direction, '1'), 4);
    }
    else if (yDelta < 50 && lastY != 0) {
        lastY = 0;
        uartQueue->post(protocol.constructString(Protocol::CMD_FULLSTOP, 0), 4);
    }
}

void JoystickThread::handleTrigger(int trig) {
    int trigBit;

    if (trig > 900) {
        trigBit = 1;
    }
    else {
        trigBit = 0;
    }

    if (trigBit == 1 && lastTrig == 0) {
        uartQueue->post(protocol.constructString(Protocol::CMD_SHOOT, '0'), 4);
    }

    lastTrig = trigBit;
}

void JoystickThread::stop() {
    running = false;
    this->exit();
}
