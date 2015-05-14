
#include "SensorsSPI.h"

SensorsSPI a2d("/dev/spidev0.0", SPI_MODE_0, 3000000, 8);



int main(void)
{
// Dette Objekt bliver givet spichannel 0 paa  raspberry, Hvilken mode (input rising edge, output falling edge), clockhastighed, antal bits - her 8.
for (;;)
{
	a2d.JoystickX();
	sleep(1);
	a2d.JoystickY();
	sleep(1);
	a2d.JoystickTrig();
	sleep(1);	
	a2d.Pirsensor();	
	sleep(1);
	}
return 0;

}
