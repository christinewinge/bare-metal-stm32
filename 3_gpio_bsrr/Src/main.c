#include "stm32g474xx.h"


#define GPIOAEN (1U<<0)
#define PIN5 (1U<<5)
#define LED_PIN PIN5
#define BS5 (1U<<5)
#define BR5 (1U<<21)

int main(void)
{
	RCC->AHB2ENR |= GPIOAEN;

	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);

	while(1)
	{
		GPIOA->BSRR |= BS5;
		for (int i = 0; i < 500000; i++){}

		GPIOA->BSRR |= BR5;
		for (int i = 0; i < 100000; i++){}
	}
}
