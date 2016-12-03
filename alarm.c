#include "include/alarm.h"

uint8_t code [4] = {0,0,0,0};	//The code to arm / disarm the alarm
uint8_t armed = 0;				//Holds the alarms status. 0: Disarmed, 1: Armed

//Checks if the alarm is armed or not
uint8_t IsArmed (void) {
	return armed;
}

//Sets a new code
void SetCode (uint8_t * p) {
	int i;
	for(i = 0; i < 4; i++) {	//Loop through the array
		code[i] = *(p+i);			//Assign the new code
	} 
}

//Returns a pointer to the code
uint8_t * GetCode (void) {
	return (uint8_t *) &code;
}

//Arms the alarm
uint8_t ArmAlarm (uint8_t * p) {
	uint8_t i;
	for(i = 0; i < 4; i++) {
		if(code[i] != *(p+i))		//Check that the code is OK
			return 0;				//If it isn't return 0
	}
	armed = armed | 1;				//If it is, set armed to 1
	IndicateArmed();				//Indicate that the alarm is armed
	return 1;						//Return 1
}

//Disarms the alarm
void DisarmAlarm (void) {
	armed = armed & 0;
	IndicateDisarmed();
}	

//Raises the alarm
void RaiseAlarm (void)
{
	IndicateArmed();
	return;
}

void ResetAlarm (void)
{
	IndicateDisarmed();
	return;
}
