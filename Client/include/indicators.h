#ifndef INDICATORS_H
#define INDICATORS_H

#include "bcm2835.h"	//Needed for GPIO support
#include <stdio.h>
#include <string.h>

#define RED_LIGHT 24	//The red indicator is on pin 24
#define GREEN_LIGHT 10	//The green indicator is on pin 10
#define BUZZER 9		//The buzzer

int InitIndicators (void);
void IndicateArmed (void);
void IndicateDisarmed (void);
void resetTriggered (void);
void IndicateTriggered (void);
void ResetTriggered (void);

#endif
