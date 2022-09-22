#include "Application\Application.h"
// #include "MCAL/Timer/Timer.h"
// #include <avr\interrupt.h>
// #include "MCAL/GPIO/GPIO.h"
// #include "ECUAL\Button\Button.h"
// #include "ECUAL\LED\LED.h"

#define F_CPU 1000000UL

// ISR(INT0_vect)
// {
// LED_ON(GPIO_A, GPIO_PIN_A0);
// LED_Toggle(GPIO_A, GPIO_PIN_A0);
// }

int main()
{
    uint8_t state1 = LED_Init(GPIO_A, GPIO_PIN_A0);
    uint8_t state2 = BUTTON_Init(GPIO_D, GPIO_PIN_D2);
    uint8_t state3 = BUTTON_PullUp(GPIO_D, GPIO_PIN_D2);
    while (1)
    {
        if (BUTTON_State(GPIO_D, GPIO_PIN_D2) == 0)
            LED_ON(GPIO_A, GPIO_PIN_A0);
        else
            LED_OFF(GPIO_A, GPIO_PIN_A0);
    }
}