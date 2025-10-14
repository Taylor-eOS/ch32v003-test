#include "ch32fun.h"

#define LED_PIN PD4
#define LED_PORT GPIOD
#define LED_PIN_MASK (1 << 4)
#define LED_CTL_REG CFGLR
#define LED_CTL_SHIFT 16
#define LED_MODE (1 << LED_CTL_SHIFT)
#define LED_CNF 0

int main(void)
{
    RCC->APB2PCENR |= RCC_IOPDEN;
    LED_PORT->LED_CTL_REG &= ~(0xf << LED_CTL_SHIFT);
    LED_PORT->LED_CTL_REG |= LED_MODE | LED_CNF;
    while(1)
    {
        LED_PORT->BSHR = LED_PIN_MASK;
        Delay_Ms(200);
        LED_PORT->BSHR = (LED_PIN_MASK << 16);
        Delay_Ms(200);
    }
}
