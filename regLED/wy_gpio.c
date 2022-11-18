#include "wy_gpio.h"

void GPIO_Init(GPIO_StructTypedef *gpioN, GPIO_InitStructTypedef *gpioInit)
{
    uint8_t pinPosition;
    uint8_t cnt;
    uint64_t *gpioCR = (uint64_t *)&(gpioN->CRL);
    uint64_t mask;
    for (cnt = 0; cnt < 16; cnt++)
        if (gpioInit->pin & ((0x01) << cnt))
        {
            pinPosition = cnt << 2;
            mask = (uint64_t)0x0f << pinPosition;
            mask = ~mask;
            *gpioCR &= mask;

            if (gpioInit->mode == GPIO_Mode_IPD || gpioInit->mode == GPIO_Mode_IPU)
            {
                mask = (uint64_t)0x08 << pinPosition;
                *gpioCR |= mask;
            }
            else
            {
                mask = (uint64_t)(gpioInit->mode) << pinPosition;
                *gpioCR |= mask;
            }
        }
    if (gpioInit->mode == GPIO_Mode_IPU)
        gpioN->ODR |= gpioInit->pin;
    if (gpioInit->mode == GPIO_Mode_IPD)
        gpioN->ODR &= ~(gpioInit->pin);
}

void GPIO_Setbit(GPIO_StructTypedef *gpioN, uint16_t pin)
{
    gpioN->BSRR = pin;
}
void GPIO_Resetbit(GPIO_StructTypedef *gpioN, uint16_t pin)
{
    gpioN->BRR = pin;
}
