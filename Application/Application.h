#ifndef APP_H
#define APP_H
#include "..\ECUAL\LED\LED.h"
#include "..\ECUAL\Button\Button.h"
#include <avr\interrupt.h>

#define GREEN 0
#define YELLOW 1
#define RED 2

#define NormalMode 0
#define PedestrianMode 1

void App_Init();
void App_Start();
static void Delay_5_sec();
static void Delay_half_sec();
static void normal_mode();
static void pedestrian_mode();
static uint8_t GetCarState();
static uint8_t GetPedestrianState();
#endif