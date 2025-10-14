#include "ch32fun.h"

#define LED_PIN_MASK (1 << 1)

static void SetSysClockTo48MHz_HSI(void)
{
    RCC->CTLR |= RCC_HSION;
    while((RCC->CTLR & RCC_HSIRDY) == 0);
    FLASH->ACTLR &= ~FLASH_ACTLR_LATENCY;
    FLASH->ACTLR |= FLASH_ACTLR_LATENCY_1;
    RCC->CFGR0 &= ~RCC_HPRE;
    RCC->CFGR0 |= RCC_HPRE_DIV1;
    RCC->CFGR0 &= ~RCC_PLLSRC;
    RCC->CFGR0 |= RCC_PLLSRC_HSI_Mul2;
    RCC->CTLR |= RCC_PLLON;
    while((RCC->CTLR & RCC_PLLRDY) == 0);
    RCC->CFGR0 &= ~RCC_SW;
    RCC->CFGR0 |= RCC_SW_PLL;
    while((RCC->CFGR0 & RCC_SWS) != RCC_SWS_PLL);
    for(volatile int i = 0; i < 1000; ++i);
}

int main(void)
{
    RCC->APB2PCENR |= RCC_IOPCEN;
    GPIOC->CFGLR &= ~(0xF << 4);
    GPIOC->CFGLR |= (GPIO_Speed_10MHz | GPIO_CNF_OUT_PP) << 4;
    SetSysClockTo48MHz_HSI();
    while(1)
    {
        GPIOC->BSHR = LED_PIN_MASK;
        Delay_Ms(40);
        GPIOC->BSHR = (LED_PIN_MASK << 16);
        Delay_Ms(960);
    }
}

