#include "Application\Application.h"
#include "MCAL/Timer/Timer.h"
#include <avr\interrupt.h>

#define F_CPU 1000000UL

// void init()
// {
//     // Timer Mode
//     TCCR0 = 0x00; // normal mode, stopped
//     // set timer start value
//     TCNT0 = 0x0c;
//     // Timer start
//     TCCR0 |= 1 << 0 | 1 << 2; // clk/1024
//                               // TCCR0 |= 1 << 0; // clk
// }
// void delay_1_ms()
// {
//     uint8_t i = 0;
//     // Timer start
//     TCCR0 |= 1 << 0 | 1 << 2; // clk/1024
//     // TCCR0 |= 1 << 0; // clk

//     while (i < 20)
//     {
//         // stop timer after 256 us
//         while ((TIFR & (1 << 0)) == 0)
//             ;
//         TIFR |= (1 << 0);
//         TCNT0 = 0x0c;
//         i++;
//     }
//     i = 0;
//     TCCR0 = 0x00;
// }


int main()
{
    App_Init();

    while (1)
    {
        App_Start();
    }
}