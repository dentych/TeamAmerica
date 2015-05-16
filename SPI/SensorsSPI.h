
#ifndef MCP3008SPI_H
#define MCP3008SPI_H
     
#include <unistd.h> //Sleep !!
#include <stdint.h> // 
#include <fcntl.h> //Open for reading and writing ORW
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <stdio.h> 
#include <errno.h>
#include <stdlib.h> 
#include <strings.h>
#include <iostream>

using namespace std;
 
class SensorsSPI{
public:
    SensorsSPI();
    SensorsSPI(string devspi, unsigned char Mode, unsigned int Speed, unsigned char bitsPerWord);
    ~SensorsSPI();

    int SensorsSPIWriteRead( unsigned char *data, int length);
	int JoystickX();
	int JoystickY();
	int JoystickTrig();
	int Pirsensor();
    void WriteToSpeaker(int value);

private:
    unsigned char _mode;			//Spimode
    unsigned char _bitsPerWord;			//Bits transmitted (8)
    unsigned int _speed;			//Clock frequency
    int _spifd;					//file descriptor
     
    int spi_init(string _devspi);
    int spi_exit();
};

#endif
