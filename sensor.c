#include "include/sensor.h"

//Initialize the sensors
void InitSensors (void)
{
	//Set the pins to be inputs
	bcm2835_gpio_fsel(MAGNET_1, BCM2835_GPIO_FSEL_INPT);
}


void CheckSensors (sensor s)
{
	if(s.status == TRIGGERED)
	{
		RaiseAlarm();
	}
	else if (s.status == PASSIVE)
	{
		ResetAlarm();
	}
	return;
}

//Updates the status of the given sensor, no matter it's type
void UpdateSensorStatus (sensor s)
{
	s.status = (*s.readStatus)();
	return;
}

//Returns the value of a given magnet sensor
sensorStatus ReadMagnetSensor (sensor s)
{
	uint8_t level = bcm2835_gpio_lev(s.pin);
	if(level == HIGH)
	{
		return PASSIVE;
	}
	else if (level == LOW)
	{
		return TRIGGERED;
	}
	return PASSIVE;
}
