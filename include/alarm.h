#ifndef ALARM_H
#define ALARM_H

#include "indicators.h"

uint8_t * GetCode (void);
void SetCode (uint8_t * p);
uint8_t ArmAlarm (uint8_t * p);
void DisarmAlarm (void);
void RaiseAlarm (void);
void ResetAlarm (void);
uint8_t IsArmed (void);

#endif
