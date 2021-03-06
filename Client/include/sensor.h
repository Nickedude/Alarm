#ifndef SENSOR_H
#define SENSOR_H

#include <stdint.h>
#include "bcm2835.h"
#include "indicators.h"
#include "alarm.h"

#define MAGNET_1 25			//Magnet 1 is on GPIO pin 25
#define IR_1 8				//IR 1 is on GPIO pin 8

//Different states of a sensor
typedef enum 
{
	PASSIVE		= 0,
	TRIGGERED	= 1,
	SABOTAGE	= 2,
} sensorStatus;

//The different types of sensors
typedef enum
{
	MAGNET		= 0,
	IR			= 1,
	TEMPERATURE	= 3,
} sensorType;

//Struct for a sensor
typedef struct sensor_t
{
	uint32_t idnumber;				//ID number of sensor
	char * placement;				//Placement of sensor
	RPiGPIOPin pin;					//The GPIO pin the sensor is connected to
	sensorStatus status;			//Status of sensor
	sensorType type;				//Type of the sensor
} sensor;

//Function definitions
sensorStatus ReadMagnetSensor (sensor s);
sensorStatus ReadIRSensor (sensor s);
void CheckSensors (void);
void InitSensors (void);
void UpdateSensor (sensor * s);

#endif
