
#include "include/indicators.h"

//Initiates the GPIO pin
int InitIndicators (void) 
{
	//Set the pins to be outputs
	bcm2835_gpio_fsel(RED_LIGHT, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(GREEN_LIGHT, BCM2835_GPIO_FSEL_OUTP);
	
	return 1;
}

//Indicators for the alarm being armed
void IndicateArmed (void) 
{
	bcm2835_gpio_write(RED_LIGHT, HIGH);
	bcm2835_gpio_write(GREEN_LIGHT, LOW);
}

//Indicators for the alarm being disarmed
void IndicateDisarmed (void) 
{
	bcm2835_gpio_write(RED_LIGHT, LOW);
	bcm2835_gpio_write(GREEN_LIGHT, HIGH);
}

//Indicators for the alarm being triggered
void IndicateTriggered (void)
{
	bcm2835_gpio_write(BUZZER, HIGH);
}

//Resets alarm after it's triggered
void ResetTriggered (void)
{
	bcm2835_gpio_write(BUZZER, LOW);
}
