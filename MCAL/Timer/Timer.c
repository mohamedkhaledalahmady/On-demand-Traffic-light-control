#include "Timer.h"

void Timer_Init()
{
    TCCR0 = 0x00; // normal mode, stopped
    TCNT0 = 0x00; // set timer start value
}
void Timer_Start(uint8_t start_time)
{
    TCNT0 = start_time;
}