
#include "include/indicators.h"

//Initiates the GPIO pin. Success = 1, fail = 0.
int InitIndicators (void) {
	/*if(!bcm2835_init())	//Used to initialize the library. If fail, returns 0.
		return 0;
	*/
	//Set the pins to be outputs
	bcm2835_gpio_fsel(RED_LIGHT, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(GREEN_LIGHT, BCM2835_GPIO_FSEL_OUTP);
	
	return 1;
}

//Indicator for the alarm being triggered activare
void IndicateArmed (void) 
{
	bcm2835_gpio_write(RED_LIGHT, HIGH);
	bcm2835_gpio_write(GREEN_LIGHT, LOW);
}

void IndicateDisarmed (void) 
{
	bcm2835_gpio_write(RED_LIGHT, LOW);
	bcm2835_gpio_write(GREEN_LIGHT, HIGH);
}
