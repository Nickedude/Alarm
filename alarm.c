
#include "include/alarm.h"

//Raises the alarm
void RaiseAlarm (void)
{
	TriggerIndicators();
	return;
}

void ResetAlarm (void)
{
	ResetIndicators();
	return;
}
