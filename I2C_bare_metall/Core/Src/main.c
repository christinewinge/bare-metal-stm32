#include <lcd_screen_lib.h>
#include "main.h"

#define PERIPH_BASE (0x40000000UL)
#define AHB2PERIPH_OFFSET (0x08000000UL)
#define AHB2PERIPH_BASE (PERIPH_BASE + AHB2PERIPH_OFFSET)

#define AHB1PERIPH_OFFSET (0x00020000UL)
#define AHB1PERIPH_BASE (PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOA_OFFSET (0x0UL)
#define GPIOA_BASE (AHB2PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET (0x00001000UL)
#define RCC_BASE (AHB1PERIPH_BASE + RCC_OFFSET)

#define GPIOAEN (1U<<0)
#define PIN5 (1U<<5)
#define LED_PIN PIN5 //LED2, user LED

typedef struct
{
	volatile uint32_t MODER;
	volatile uint32_t DUMMY[4];
	volatile uint32_t ODR;
}GPIO_TypeDef;

typedef struct
{
	volatile uint32_t DUMMY[19];
	volatile uint32_t AHB2ENR;
}RCC_TypeDef;

#define GPIOA ((GPIO_TypeDef*) GPIOA_BASE)
#define RCC ((RCC_TypeDef*) RCC_BASE)

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	/*
	//1. Enable clock access to GPIOA
	RCC->AHB2ENR |= GPIOAEN;

	//2. Set PA5 to output pin
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);
	 * */

	led_init(hi2c1);

	led_send_character('H');
	led_send_string("ello world");

	while (1)
	{

	}
}

