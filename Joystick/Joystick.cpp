#include "Joystick.h"

bool JoystickThread::alarmEnabled = true;
int JoystickThread::objectCount = 0;

JoystickThread::JoystickThread(UARTQueue *uartQueue) : uartQueue(uartQueue) {
    if (objectCount > 0) {
        std::cout << "FATAL ERROR: Two joystick thread objects have been instantiated!" << std::endl;
        exit(-1);
    }
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
        int xCord, yCord, trigger, alarm;
        xCord = spi->JoystickX();
        yCord = spi->JoystickY();
        trigger = spi->JoystickTrig();
        if (alarmEnabled) alarm = spi->Pirsensor();

        handleXCord(xCord);
        handleYCord(yCord);
        handleTrigger(trigger);
        handleAlarm(alarm);

        usleep(100000);
    }
}

void JoystickThread::handleXCord(int xCord) {
    Protocol::CMDS direction;
    int xDelta = xCord - 512;

    if (xDelta > 0) {
        direction = Protocol::CMD_RIGHT;
    }
    else {
        xDelta *= (-1);
        direction = Protocol::CMD_LEFT;
    }

    if (xDelta < 100 && lastX != 0) {
        lastX = 0;
        uartQueue->post(protocol.constructString(Protocol::CMD_FULLSTOP, '0'), 4);
    }
    else if (xDelta < 400 && xDelta > 100 && lastX != 1) {
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

    if (yDelta > 200 && lastY != 1) {
        lastY = 1;
        uartQueue->post(protocol.constructString(direction, '1'), 4);
    }
    else if (yDelta < 200 && lastY != 0) {
        lastY = 0;
        uartQueue->post(protocol.constructString(Protocol::CMD_FULLSTOP, '0'), 4);
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

void JoystickThread::handleAlarm(int alarm) {
    if (alarm > 800 && !alarmCooldown) {
        alarmCooldown = 20;
        spi->WriteToSpeaker(0);
    }

    if (alarmCooldown > 0) {
        if (alarmCooldown == 1) spi->WriteToSpeaker(1);
        alarmCooldown--;
    }
}
