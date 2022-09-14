#ifndef LED_H
#define LED_H
#include "..\..\MCAL\GPIO\GPIO.h"
#include "..\..\MCAL\Timer\Timer.h"

// LEDs Colors
#define RED 0
#define YELLOW 1
#define GREEN 2

// Status
#define Sucess 1
#define Fail 0

// Functions
uint8_t LED_Init(uint8_t, uint8_t);
uint8_t LED_ON(uint8_t, uint8_t);
uint8_t LED_OFF(uint8_t, uint8_t);
uint8_t LED_Toggle(uint8_t, uint8_t);
uint8_t LED_Blink(uint8_t, uint8_t, uint8_t);
#endif