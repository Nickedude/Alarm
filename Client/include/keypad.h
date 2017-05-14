#ifndef KEYPAD_H
#define KEYPAD_H

#include "bcm2835.h"	//Needed for GPIO support
#include <stdio.h>

//Sets up the keypad IO pins
uint8_t keypadInit ();

//Reads the next key pressed and returns it. It's appropriate with a delay after this function is called.
uint8_t readKey ();

//Reads the 4 character code and saves it starting on codeptr
void ReadCode (uint8_t * codptr);


#endif
