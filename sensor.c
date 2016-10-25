#include "include/sensor.h"

//Updates the status of the given sensor, no matter it's type
void UpdateSensorStatus (sensor s)
{
	s.status = (*s.readStatus)();
	return;
}

//Returns the value of a given magnet sensor
sensorStatus ReadMagnetSensor (sensor s)
{
	sensorStatus status = (sensorStatus) bcm2835_gpio_lev(s.pin);
	return status;
}

