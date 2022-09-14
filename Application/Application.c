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
    LED_Init(GPIO_B, GPIO_PIN_A0);
    LED_Init(GPIO_B, GPIO_PIN_A1);
    LED_Init(GPIO_B, GPIO_PIN_A2);

    // Inital Button as input pin and active internal pull up resistor
    BUTTON_Init(GPIO_D, GPIO_PIN_D2);
    BUTTON_PullUp(GPIO_D, GPIO_PIN_D2);

    // Inital for timer in normal mode
    Timer_Init();
    GICR = 0xc0;  // Enable External Interrupts INT0 and INT1
    MCUCR = 0x08; // Configure INT0 active low level triggered and INT1 as falling edge
    sei();
}
static void Delay_5_sec()
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

static void Delay_half_sec()
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

ISR(INT0_vect)
{
    // LED_ON(GPIO_B, GPIO_PIN_B0);
    // Delay_5_sec();
    // mode = PedestrianMode;
    // TCCR0 |= 1 << 0 | 1 << 2; // clk/1024
    // TCNT0 = 0x0c;
    // TCCR0 = 0x00;
    Timer_Init();

    pedestrian_mode();
}
static void normal_mode()
{
    LED_OFF(GPIO_B, GPIO_PIN_B0);

    LED_ON(GPIO_A, GPIO_PIN_A0);
    LED_OFF(GPIO_A, GPIO_PIN_A1);
    LED_OFF(GPIO_A, GPIO_PIN_A2);
    Delay_5_sec();
    // _delay_ms(5000);

    LED_OFF(GPIO_A, GPIO_PIN_A0);
    LED_OFF(GPIO_A, GPIO_PIN_A2);
    uint8_t index = 0;
    for (index = 0; index < 10; index++)
    {
        LED_Toggle(GPIO_A, GPIO_PIN_A1);
        Delay_half_sec();
        // _delay_ms(500);
    }

    LED_OFF(GPIO_A, GPIO_PIN_A0);
    LED_OFF(GPIO_A, GPIO_PIN_A1);
    LED_ON(GPIO_A, GPIO_PIN_A2);
    Delay_5_sec();
    // _delay_ms(5000);

    LED_OFF(GPIO_A, GPIO_PIN_A0);
    LED_OFF(GPIO_A, GPIO_PIN_A2);
    for (index = 0; index < 10; index++)
    {
        LED_Toggle(GPIO_A, GPIO_PIN_A1);
        Delay_half_sec();
        // _delay_ms(500);
    }
}

static void pedestrian_mode()
{
    // do something
    LED_ON(GPIO_B, GPIO_PIN_B0);
    Delay_half_sec();
    // _delay_ms(500);

    LED_OFF(GPIO_B, GPIO_PIN_B0);
    mode = NormalMode;
}
void App_Start()
{
    // if (mode == NormalMode)
    normal_mode();
    // else if (mode == PedestrianMode)
    // pedestrian_mode();
}
