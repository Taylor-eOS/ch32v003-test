#include "ch32fun.h"

#define LED_PIN PC1
#define LED_PORT GPIOC
#define LED_PIN_MASK (1 << 1)
#define LED_CTL_REG CFGLR
#define LED_CTL_SHIFT 4
#define LED_MODE (GPIO_Speed_10MHz | GPIO_CNF_OUT_PP)
#define LED_CNF 0

int main(void)
{
    RCC->APB2PCENR |= RCC_IOPCEN;
    LED_PORT->LED_CTL_REG &= ~(0xf << LED_CTL_SHIFT);
    LED_PORT->LED_CTL_REG |= (LED_MODE << LED_CTL_SHIFT);
    while(1)
    {
        LED_PORT->BSHR = LED_PIN_MASK;
        Delay_Ms(100);
        LED_PORT->BSHR = (LED_PIN_MASK << 16);
        Delay_Ms(100);
    }
}
