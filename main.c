/*
 * mainc
 *
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include "include/main.h"

//Initiate everything
uint32_t Init (void)
{
	uint32_t r = 0;				//Variable for holding the result
	r = bcm2835_init();			//Init GPIO library
	r &= keypadInit();			//Init settings for keypad
	r = r & InitIndicators();	//Init the indicators
	InitSensors();				//Init the sensors
	return r;					//Return the result
}

//Main menu
void MainLoop (void) {
	
	uint32_t i;								//Variable for loops
	uint8_t c;								//Variable for holding the input
	uint8_t * ptr = (uint8_t *) malloc(4);	//Allocate 4 bytes this pointer can utilize
	
	c = readKey();							//Read input
	bcm2835_delay(500);						//Wait a bit so we only read one char
	
	switch(c) {
		case '1': 											//Arm the alarm
			printf("Please enter the code.\n");				//Ask for the code
			ReadCode(ptr);									//Read the input and save it
			c = ArmAlarm(ptr);								//Try to arm the alarm with the code given
			if(c)											//If one is returned the alarm was successfully armed
				printf("Alarm is now armed! Press 2 to disarm\n");
			else 											//Otherwise the alarm wasn't armed (wrong code)
				printf("Wrong code, try again.\n");
			break;
			
		case '2':											//If user picks 2, disarm alarm
			DisarmAlarm();									//Disarm the alarm
			printf("Alarm is now disarmed!\n");
			break;
			
		case '3':											//If user picks 3, set a new code
			printf("Please enter the new code!\n");
			ReadCode(ptr);									//Read the input
			SetCode(ptr);									//Set new code
			break;
			
		case '4':											//If user picks 4, print the code
			ptr = GetCode();								//Get pointer to the code
			for(i = 0; i < 4; i++) {						//Print each char
				printf("%c",*(ptr+i));						
			}
			printf("\n");
			break;
			
		case '9':											//If user picks 9, display help
			printf("1: Arm\n");
			printf("2: Disarm\n");
			printf("3: Set code\n");
			printf("4: Print code\n");						// Only for debug
			break;
			
		default: 
			break;
			
		free(ptr);											//Free the allocated space
	}
}

void ArmedLoop (void) 
{
	while(1) 
	{
		CheckSensors();
	}
}
	

int main(int argc, char **argv)
{
	Init();	
	IndicateDisarmed();
	ResetTriggered();
	while(1) {
		printf("What do you want to do? Press 9 for help.\n");
		if(isTriggered()) {
			printf("The alarm has been triggered!\n");
		}
		else if(IsArmed()) {
			printf("Armed\n");
			ArmedLoop();
		}
		else
			MainLoop();
	}
	
	/*RaiseAlarm();
	delay(400);
	ResetTriggered();*/
	return 0;
	
}


