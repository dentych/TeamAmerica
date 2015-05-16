#include "SensorsSPI.h"
#include <wiringPi.h>


int SensorsSPI::spi_init(std::string devspi)
{
	_spifd = open(devspi.c_str(), O_RDWR);
	int mode = _mode;
	int bitsPerWord = _bitsPerWord;
	int speed = _speed;

	if(_spifd < 0)
	{
		perror("Unable to open SPI device");
		exit(1);
	}
 
	int check = -1;
    check = ioctl (_spifd, SPI_IOC_WR_MODE, &mode);
    if(check < 0)
	{
        perror("Unable to WRITE SPImode");
        exit(1);
    }
 
    check = ioctl (_spifd, SPI_IOC_RD_MODE, &mode);
    if(check < 0) 
	{
		perror("Unable to READ SPImode");
		exit(1);
    }
 
    check = ioctl (_spifd, SPI_IOC_WR_BITS_PER_WORD, &bitsPerWord);
    if(check < 0)
	{
		perror("unable to WRITE bitsPerWord");
		exit(1);
    }
 
    check = ioctl (_spifd, SPI_IOC_RD_BITS_PER_WORD, &bitsPerWord);
    if(check < 0) 
	{
		perror("Unable to set READ bitsPerWord");
		exit(1);
    }  
 
    check = ioctl (_spifd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);    
    if(check < 0) 
	{
		perror("Unable to WRITE speed");
		exit(1);
    }
 
    check = ioctl (_spifd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);    
    if(check < 0) 
	{
		perror("Unable to READ speed");
		exit(1);
    }
    return check;
}


int SensorsSPI::spi_exit()
{
    int check = -1;
    check = close(_spifd);
    if(check < 0) 
	{
      perror("Unable to close SPI device");
      exit(1);
    }
    return check;
}


int SensorsSPI::SensorsSPIWriteRead( unsigned char *data, int length)
{
 
  struct spi_ioc_transfer spi[length];
  int i = 0;
  int retVal = -1; 
  
 bzero(spi, sizeof spi);
// one spi transfer for each byte
 
  for (i = 0; i < length; i++){
 
    spi[i].tx_buf        = (unsigned long)(data + i); // transmit from "data"
    spi[i].rx_buf        = (unsigned long)(data + i) ; // receive into "data"
    spi[i].len           = sizeof(*(data + i)) ;
    spi[i].delay_usecs   = 0 ;
    spi[i].speed_hz      = this->_speed ;
    spi[i].bits_per_word = this->_bitsPerWord ;
    spi[i].cs_change = 0;
}
 
 retVal = ioctl (this->_spifd, SPI_IOC_MESSAGE(length), &spi) ;
 
 if(retVal < 0){
    perror("Problem transmitting spi data ");
    exit(1);
 }
 
return retVal;
 
}
 

 // Default constructor. Set member variables to this
 // default values and then call init()
 
 
SensorsSPI::SensorsSPI(){
    wiringPiSetup();
    pinMode (25, OUTPUT);
    this->_mode = SPI_MODE_0 ;
    this->_bitsPerWord = 8;
    this->_speed = 1000000;
    this->_spifd = -1;
    this->spi_init(string("/dev/spidev0.0"));
}
 

 // overloaded constructor set variables by user ME
 // and then call spiinit()
 
SensorsSPI::SensorsSPI(string devspi, unsigned char spiMode, unsigned int spiSpeed, unsigned char spibitsPerWord){
    this->_mode = spiMode ;
    this->_bitsPerWord = spibitsPerWord;
    this->_speed = spiSpeed;
    this->_spifd = -1;
    this->spi_init(devspi);
 
}
 

 // Destructor: calls spi_exit()


SensorsSPI::~SensorsSPI(){
    this->spi_exit();
}

int SensorsSPI::JoystickX()
{

	int a2dValX = 0;
	unsigned char dataX[3];
	dataX[0] = 1;						//  first byte transmitted -> start bit
	dataX[1] = 0b10000000;					// second byte transmitted -> (SGL/DIF = 1 d1=d2=d0=0)
	dataX[2] = 0;						// third byte transmitted....don't care

	SensorsSPIWriteRead(dataX, sizeof(dataX));

	a2dValX = (dataX[1] << 8) & 0b1100000000;		//merge data[1] & data[2] to get result
	a2dValX |= (dataX[2] & 0xff);
	
	cout << "The Result for X is: \n" << a2dValX << endl;
	return a2dValX;
}

int SensorsSPI::JoystickY()
{
	int a2dValY = 0;
	unsigned char dataY[3];
	dataY[0] = 1; 
	dataY[1] = 0b10010000; 
	dataY[2] = 0;  

	SensorsSPIWriteRead(dataY, sizeof(dataY));

	a2dValY = 0;
	a2dValY = (dataY[1] << 8) & 0b1100000000; 
	a2dValY |= (dataY[2] & 0xff);

	cout << "The Result for Y is: \n" << a2dValY << endl;
	return a2dValY;
}

int SensorsSPI::JoystickTrig()
{
	int a2dValTrig = 0;
	unsigned char dataTrig[3];
	dataTrig[0] = 1;  
	dataTrig[1] = 0b10100000;
	dataTrig[2] = 0; 

	SensorsSPIWriteRead(dataTrig, sizeof(dataTrig));

	a2dValTrig = 0;
	a2dValTrig = (dataTrig[1] << 8) & 0b1100000000; 
	a2dValTrig |= (dataTrig[2] & 0xff);

	cout << "The Result for Trigger is: \n" << a2dValTrig << endl;
	return a2dValTrig;
}

int SensorsSPI::Pirsensor()
{
	int a2dValPIR = 0;
	unsigned char dataPIR[3];
	dataPIR[0] = 1;
	dataPIR[1] = 0b10110000;
	dataPIR[2] = 0;

	SensorsSPIWriteRead(dataPIR, sizeof(dataPIR));

	a2dValPIR = 0;
	a2dValPIR = (dataPIR[1] << 8) & 0b1100000000;
	a2dValPIR |= (dataPIR[2] & 0xff);

    return a2dValPIR;
}

void SensorsSPI::WriteToSpeaker(int value) {
    digitalWrite(25, value);
}
