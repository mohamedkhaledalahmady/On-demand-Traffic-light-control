#include "Application.h"

uint8_t Cars_LED_Color;
uint8_t pedestrian_LED_Color;
uint8_t mode;

void App_Init()
{
    // Inital all leds as ouput pins
    LED_Init(GPIO_A, GPIO_PIN_A0);
    LED_Init(GPIO_A, GPIO_PIN_A1);
    LED_Init(GPIO_A, GPIO_PIN_A2);
    LED_Init(GPIO_B, GPIO_PIN_B0);
    LED_Init(GPIO_B, GPIO_PIN_B1);
    LED_Init(GPIO_B, GPIO_PIN_B2);

    // inital
    // LED_ON(GPIO_B, GPIO_PIN_B2);
    // Inital Button as input pin and active internal pull up resistor
    BUTTON_Init(GPIO_D, GPIO_PIN_D2);
    BUTTON_PullUp(GPIO_D, GPIO_PIN_D2);

    // Inital for timer in normal mode
    Timer_Init();
    GICR = 0x40;  // Enable External Interrupts INT0
    MCUCR = 0x03; // Configure INT0 The rising edge of INT0 generates an interrupt request.
    sei();
}
void Delay_5_sec()
{
    uint8_t i = 0;
    // Timer start
    TCCR0 |= 1 << 0 | 1 << 2; // clk/1024
    // TCCR0 |= 1 << 0; // clk

    while (i < 20)
    {
        // stop timer after 256 us
        while ((TIFR & (1 << 0)) == 0)
            ;
        TIFR |= (1 << 0);
        TCNT0 = 0x0c;
        i++;
    }
    i = 0;
    TCCR0 = 0x00;
}

void Delay_half_sec()
{
    uint8_t i = 0;
    // Timer start
    TCCR0 |= 1 << 0 | 1 << 2; // clk/1024
    // TCCR0 |= 1 << 0; // clk

    while (i < 2)
    {
        // stop timer after 256 us
        while ((TIFR & (1 << 0)) == 0)
            ;
        TIFR |= (1 << 0);
        TCNT0 = 0x0c;
        i++;
    }
    i = 0;
    TCCR0 = 0x00;
}

uint8_t GetCarState()
{
    uint8_t i;
    for (i = 0; i < 3; i++)
        if (GPIO_GetPin(GPIO_A, i))
            return i;
    return YELLOW;
}

uint8_t GetPedestrianState()
{
    uint8_t i;
    for (i = 0; i < 3; i++)
        if (GPIO_GetPin(GPIO_B, i))
            return i;
    return YELLOW;
}

ISR(INT0_vect)
{
    pedestrian_mode();
    PORTA = 0x00;
    PORTB = 0x00;

    TCCR0 |= 1 << 0 | 1 << 2; // clk/1024 (Timer ON)
}
void normal_mode()
{
    PORTA = 0xF0;
    PORTB = 0xF0;

    LED_ON(GPIO_A, GPIO_PIN_A0);
    LED_OFF(GPIO_A, GPIO_PIN_A1);
    LED_OFF(GPIO_A, GPIO_PIN_A2);

    LED_OFF(GPIO_B, GPIO_PIN_B0);
    LED_OFF(GPIO_B, GPIO_PIN_B1);
    LED_ON(GPIO_B, GPIO_PIN_B2);
    Delay_5_sec();

    LED_OFF(GPIO_A, GPIO_PIN_A0);
    LED_OFF(GPIO_A, GPIO_PIN_A2);
    LED_OFF(GPIO_B, GPIO_PIN_B0);
    LED_OFF(GPIO_B, GPIO_PIN_B2);
    uint8_t index = 0;
    for (index = 0; index < 10; index++)
    {
        LED_Toggle(GPIO_A, GPIO_PIN_A1);
        LED_Toggle(GPIO_B, GPIO_PIN_B1);
        Delay_half_sec();
    }

    LED_OFF(GPIO_A, GPIO_PIN_A0);
    LED_OFF(GPIO_A, GPIO_PIN_A1);
    LED_ON(GPIO_A, GPIO_PIN_A2);

    LED_ON(GPIO_B, GPIO_PIN_B0);
    LED_OFF(GPIO_B, GPIO_PIN_B1);
    LED_OFF(GPIO_B, GPIO_PIN_B2);

    Delay_5_sec();

    LED_OFF(GPIO_A, GPIO_PIN_A0);
    LED_OFF(GPIO_A, GPIO_PIN_A2);

    LED_OFF(GPIO_B, GPIO_PIN_B0);
    LED_OFF(GPIO_B, GPIO_PIN_B2);
    for (index = 0; index < 10; index++)
    {
        LED_Toggle(GPIO_A, GPIO_PIN_A1);
        LED_Toggle(GPIO_B, GPIO_PIN_B1);
        Delay_half_sec();
    }
}

void pedestrian_mode()
{
    // do something
    if (GetCarState() == RED)
    {
        // LED_ON(GPIO_A, GPIO_PIN_A2);  // red car on
        LED_ON(GPIO_B, GPIO_PIN_B0);  // green pedestrian on
        LED_OFF(GPIO_B, GPIO_PIN_B1); // yellow pedestrian off
        LED_OFF(GPIO_B, GPIO_PIN_B2); // red pedestrian off

        Delay_5_sec();
        LED_OFF(GPIO_A, GPIO_PIN_A2); // red car off
        LED_OFF(GPIO_B, GPIO_PIN_B0); // green pedestrian off
    }
    else if (GetCarState() == GREEN || GetCarState() == YELLOW)
    {
        LED_ON(GPIO_B, GPIO_PIN_B2);  // red pedestrian on
        LED_OFF(GPIO_A, GPIO_PIN_A0); // green car off
        LED_OFF(GPIO_A, GPIO_PIN_A2); // red car off
        LED_OFF(GPIO_B, GPIO_PIN_B2); // red pedestrian off

        // LED_OFF(GPIO_A, GPIO_PIN_A0); // green car off

        uint8_t index = 0; // both yellow blink
        for (index = 0; index < 10; index++)
        {
            LED_Toggle(GPIO_A, GPIO_PIN_A1);
            LED_Toggle(GPIO_B, GPIO_PIN_B1);
            Delay_half_sec();
        }

        LED_ON(GPIO_A, GPIO_PIN_A2);  // red car on
        LED_ON(GPIO_B, GPIO_PIN_B0);  // green pedestrian on
        LED_OFF(GPIO_B, GPIO_PIN_B1); // yellow pedestrian off
        LED_OFF(GPIO_B, GPIO_PIN_B2); // red pedestrian off
        Delay_5_sec();
        LED_OFF(GPIO_A, GPIO_PIN_A2); // red car off
        LED_OFF(GPIO_B, GPIO_PIN_B0); // green pedestrian off
    }

    // At the end of the two states

    uint8_t index = 0; // both yellow blink
    for (index = 0; index < 10; index++)
    {
        LED_Toggle(GPIO_A, GPIO_PIN_A1);
        LED_Toggle(GPIO_B, GPIO_PIN_B1);
        Delay_half_sec();
    }

    LED_OFF(GPIO_B, GPIO_PIN_B0); // green pedestrian off
    LED_OFF(GPIO_B, GPIO_PIN_B1); // yellow pedestrian off
    LED_OFF(GPIO_A, GPIO_PIN_A1); // yellow car off
    LED_OFF(GPIO_A, GPIO_PIN_A2); // red car off

    LED_ON(GPIO_A, GPIO_PIN_A0);  // green car on
    LED_OFF(GPIO_B, GPIO_PIN_B2); // red pedestrian off

    mode = NormalMode;
}
void App_Start()
{
    normal_mode();
}
