#include "include/sensor.h"

//Variables
uint32_t nrofsensors = 0;	//Holds the current number of sensors
sensor sensors [10] = {};	//Keeps track of the plugged in sensors

//Initialize the sensors
void InitSensors (void)
{
	bcm2835_gpio_fsel(MAGNET_1, BCM2835_GPIO_FSEL_INPT);	//Initiate GPIO pins
	bcm2835_gpio_fsel(IR_1, BCM2835_GPIO_FSEL_INPT);

	sensor mk1 = {1, "Test", MAGNET_1,PASSIVE,MAGNET};		//Create variable for magnet 1
	sensor ir1 = {2, "Test", IR_1, PASSIVE, IR};			//Create variable for motion sensor 1 
	sensors[nrofsensors++] = mk1;							//Add mk1 to the array of current sensors
	sensors[nrofsensors++] = ir1;							//Add ir1 to the array of current sensors
	mk1.status = ReadMagnetSensor(mk1);						//Update status of mk1
	ir1.status = ReadIRSensor(ir1);
}

//Checks all the sensors and raises the alarm if anyone of them is triggered
void CheckSensors (void)
{
	int i;
	for(i = 0; i < nrofsensors; i++)			//Loop through all the sensors
	{
		UpdateSensor((sensor *) &sensors[i]);	//Updates sensor i
		if(sensors[i].status == TRIGGERED)		//If sensor i is triggered
		{
			RaiseAlarm();						//Raise the alarm
		}
		else 									//If not, reset the alarm indicator
		{
			ResetAlarm();						//Reset the alarm indicator
		}
	}
	return;
}

//Updates the status of a sensor by reading it's level
void UpdateSensor (sensor * s) 
{
	if(s -> type == MAGNET)						//If it's a magnet
	{
		(*s).status = ReadMagnetSensor(*s);		//Update the status for a magnet sensor
	}
	else if(s -> type == IR)
	{
		(*s).status = ReadIRSensor(*s);
	}
	else 										//If no valid typ of sensor is assigned ...
	{
		return; 								//Do nothing
	}
}

//Returns the value of a given magnet sensor
sensorStatus ReadMagnetSensor (sensor s)
{
	uint8_t level = bcm2835_gpio_lev(s.pin);		//Read the level of the pin
	if(level == HIGH)								//If it's high ...
	{
		return PASSIVE;								//Return passive status
	}
	else if (level == LOW)							//If it's low ...
	{
		return TRIGGERED;							//The contact has been breached, return triggered status
	}
	else 
	{
		return PASSIVE;								//This will never happen, but return passive status as default
	}
}


//Returns the value of a given motion sensor
sensorStatus ReadIRSensor (sensor s)
{
	uint8_t level = bcm2835_gpio_lev(s.pin);		//Read the level of the pin
	if(level == LOW)								//If it's low ...
	{
		return PASSIVE;							//Return passive status
	}
	else if (level == HIGH)						//If it's high ...
	{
		return TRIGGERED;							//Motion has been detected, return triggered status
	}
	else 
	{
		return PASSIVE;							//This will never happen, but return passive status as default
	}
}
