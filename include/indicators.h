#ifndef INDICATORS_H
#define INDICATORS_H

#include "bcm2835-1.5/src/bcm2835.h"	//Needed for GPIO support
#include <stdio.h>
#include <string.h>

//Define pin 11 (really GPIO pin 17) to be the one used for sending the dots and dashes
#define RED_LIGHT RPI_GPIO_P1_11

int InitIndicators (void);
void TriggerIndicators (void);
void ResetIndicators (void);

#endif
