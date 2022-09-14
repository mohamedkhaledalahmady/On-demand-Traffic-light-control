#include "Button.h"

uint8_t BUTTON_Init(uint8_t port, uint8_t pin)
{
    return GPIO_InitPin(port, pin, GPIO_INPUT);
}
uint8_t BUTTON_PullUp(uint8_t port, uint8_t pin)
{
    return GPIO_WritePin(port, pin, GPIO_HIGH);
}
uint8_t BUTTON_State(uint8_t port, uint8_t pin)
{
    return GPIO_GetPin(port, pin);
}
