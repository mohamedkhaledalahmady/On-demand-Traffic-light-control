#include "LED.h"

uint8_t LED_Init(uint8_t port, uint8_t pin)
{
    return GPIO_InitPin(port, pin, GPIO_OUTPUT);
}
uint8_t LED_ON(uint8_t port, uint8_t pin)
{
    return GPIO_WritePin(port, pin, GPIO_HIGH);
}
uint8_t LED_OFF(uint8_t port, uint8_t pin)
{
    return GPIO_WritePin(port, pin, GPIO_LOW);
}
uint8_t LED_Toggle(uint8_t port, uint8_t pin)
{
    return GPIO_Toggle(port, pin);
}
uint8_t LED_Blink(uint8_t port, uint8_t pin, uint8_t delay)
{
    LED_Toggle(port, pin);
    _delay_ms(delay);
}