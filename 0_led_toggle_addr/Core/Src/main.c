//LED2 (user LED) is connected to PA5 on the chip
//Port A
//Pin 5
//memory map for stmg4 is in user manual, not datasheet
//we are interested in the peripheral block.
/*
 * A 'Microcontroller Peripheral' refers to additional hardware components
 * integrated into a microcontroller to provide extended functionality
 * and capabilities for various applications in computer science
 * */

#define PERIPH_BASE (0x40000000UL)
#define AHB2PERIPH_OFFSET (0x08000000UL)
#define AHB2PERIPH_BASE (PERIPH_BASE + AHB2PERIPH_OFFSET)

#define AHB1PERIPH_OFFSET (0x00020000UL)
#define AHB1PERIPH_BASE (PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOA_OFFSET (0x0UL)
#define GPIOA_BASE (AHB2PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET 0x00001000UL
#define RCC_BASE (AHB1PERIPH_BASE + RCC_OFFSET)

#define AHB2EN_R_OFFSET (0x4CUL) //R for register, so AHB2 enable register offset

#define RCC_AHB2EN_R (*(volatile unsigned int *) (RCC_BASE + AHB2EN_R_OFFSET))

#define GPIOAEN (1U<<0)

#define MODE_R_OFFSET (0x00UL)
#define GPIOA_MODE_R (*(volatile unsigned int *)(GPIOA_BASE + MODE_R_OFFSET))
/*
 * (1U<<10)    // Set bit 10 to 1
 * &=~(1U<<11) //Set bit 11 to 0*/

#define OD_R_OFFSET (0x14UL) //Output data register offset
#define GPIOA_OD_R (*(volatile unsigned int *)(GPIOA_BASE + OD_R_OFFSET))
#define PIN5 (1U<<5)
#define LED_PIN PIN5 //LED2, user LED


int main(void) {
	//1. Enable clock access to GPIOA
	//2. Set PA5 to output pin

	RCC_AHB2EN_R |= GPIOAEN;
	GPIOA_MODE_R |= (1U<<10);
	GPIOA_MODE_R &=~(1U<<11);

	while(1) {
		//Set PA5 high
		//GPIOA_OD_R |= LED_PIN;

		//Toggle PA5
		GPIOA_OD_R ^= LED_PIN;
		for (int i = 0; i < 100000; i++){}
	}
}






