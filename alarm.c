#include "include/alarm.h"

uint8_t code [4] = {1,1,1,1};	//The code to arm / disarm the alarm
uint8_t status = 0;				//Holds the alarms status. 0: Disarmed, 1: Armed, 2: Triggered

//Checks if the alarm is armed or not
uint8_t IsArmed (void) {
	return status;
}

//Sets a new code
void SetCode (uint8_t * p) {
	int i;
	for(i = 0; i < 4; i++) {		//Loop through the array
		code[i] = *(p+i);			//Assign the new code
	} 
}

//Returns a pointer to the code
uint8_t * GetCode (void) {
	return (uint8_t *) &code;
}

//Arms the alarm
uint8_t ArmAlarm (uint8_t * p) {
	uint8_t i;						//Counter for the loop
	for(i = 0; i < 4; i++) {		//Loop through the whole code
		if(code[i] != *(p+i))		//Check that the code is OK
			return 0;				//If it isn't return 0
	}
	status = status | 1;			//If it is, set armed to 1
	IndicateArmed();				//Indicate that the alarm is armed
	return 1;						//Return 1
}

//Disarms the alarm
void DisarmAlarm (void) {
	status = status & 0;			//Set the alarm status to unarmed
	IndicateDisarmed();				//Change the indicators
}	

//Raises the alarm
void RaiseAlarm (void)
{
	printf("Alarm triggered!");
	IndicateTriggered();
	return;
}

void ResetAlarm (void)
{
	ResetTriggered();
	return;
}

uint8_t isTriggered (void)
{
	if(status == 2)
		return 1;
	else
		return 0;
}
