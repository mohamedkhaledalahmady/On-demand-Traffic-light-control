#ifndef TIMER_H
#define TIMER_H

#include "../GPIO/GPIO.h"

#define FREQ 1000000UL

void Timer_Init();
void Timer_Start(uint8_t);

#endif