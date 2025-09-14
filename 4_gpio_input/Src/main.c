#include "stm32g474xx.h"


#define GPIOAEN (1U<<0)
#define GPIOCEN (1U<<2)
#define PIN5 (1U<<5)
#define LED_PIN PIN5
#define BS5 (1U<<5)
#define BR5 (1U<<21)


int main(void)
{
	RCC->AHB2ENR |= GPIOCEN;
	GPIOC->MODER &= ~(1U<<26);
	GPIOC->MODER &= ~(1U<<27);

	RCC->AHB2ENR |= GPIOAEN;
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);

	while(1)
	{
		if (GPIOC->IDR & (1U<<13))
		{
			GPIOA->BSRR |= BS5;
		}

		else
		{
			GPIOA->BSRR |= BR5;
		}
	}
}
