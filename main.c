#include "Application\Application.h"

#define F_CPU 1000000UL

int main()
{
    App_Init();
    while (1)
    {
        App_Start();
    }
}