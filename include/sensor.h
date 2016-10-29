#ifndef SENSOR_H
#define SENSOR_H

#include <stdint.h>
#include "bcm2835-1.5/src/bcm2835.h"
#include "indicators.h"
#include "alarm.h"

//Define pin 12 (really GPIO pin 18) as magnet 1
#define MAGNET_1 RPI_GPIO_P1_12

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
	sensorStatus (*readStatus)();	//Function pointer to the readStatus function for this specific sensor
} sensor;

//Function definitions
void UpdateSensorStatus (sensor s);
sensorStatus ReadMagnetSensor (sensor s);
void CheckSensors (sensor s);
void TestSensors (void);

#endif
