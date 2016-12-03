/*
 * mainc
 * 
 * Copyright 2016 MrWicki <mrwicki@MrWicki2>
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

uint32_t Init (void)
{
	uint32_t r = 0;
	r = bcm2835_init();
	r &= keypadInit();
	r = r & InitIndicators();
	return r;
}

void MainLoop (void) {
	
	uint8_t a [4] = {0,0,0,0};	//Replace by mallock somehow
	uint32_t i;
	uint8_t c;
	uint8_t * ptr = &a[0];
	
	c = readKey();			//Read input
	bcm2835_delay(500);		//Wait a bit so we only read one char
	
	switch(c) {
		case '1': 
			printf("Please enter the code.\n");
			ReadCode(ptr);
			printf("hej\n");
			c = ArmAlarm(ptr);								//If user picks 1, arm alarm
			if(c)
				printf("Alarm is now armed! Press 2 to disarm\n");
			else
				printf("Wrong code, try again.\n");
			break;
			
		case '2':
			DisarmAlarm();									//If user picks 2, disarm alarm
			printf("Alarm is now disarmed!\n");
			break;
			
		case '3':											//If user picks 3, set a new code
			printf("Please enter the new code!\n");
			ReadCode(ptr);
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
	}
}

int main(int argc, char **argv)
{
	//sensor ms1 = {1, "Teststation", MAGNET_1, PASSIVE, MAGNET, &ReadMagnetSensor};
	Init();
	//uint32_t returncode = Record10Sec();
	//TestSensors();
	/*while(1)
	{
		ReadMagnetSensor(MAGNET_1);
		CheckSensors(ms1);
	}*/
	
	IndicateDisarmed();
	printf("What do you want to do? Press 9 for help.\n");
	while(1) {
		if(IsArmed())
			printf("Armed");
		else
			MainLoop();
	}
	
	bcm2835_gpio_fsel(25, BCM2835_GPIO_FSEL_INPT);
	uint8_t t = bcm2835_gpio_lev(25);
	printf("%d\n",t);
	return 0;
	
}


