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
//address space APB1: 0x4000 0000 - 0x4000 9800
//address space APB2: 0x4001 0000 - 0x4001 6400
//address space AHB1: 0x4002 0000 - 0x4002 4400
//address space AHB2: 0x4800 0000 - 0x5006 0C00
//the address of GPIO Port A is in here somewhere

//GPIOA adress range: 0x4800 0000 - 0x4800 03FF
//It is in the AHB2 bus (advanced high performance bus. Less clock cycles than other buses.)
//I assume we look at GPIOA because we are looking for port A
//GPIOA_MODER is at offset 0x0, so adress is 0x4800 0000
/*
 * Bits 31:0 MODE[15:0][1:0]: Port x configuration I/O pin y (y = 15 to 0)
These bits are written by software to configure the I/O mode.
00: Input mode
01: General purpose output mode
10: Alternate function mode
11: Analog mode (reset state)
*/

//We need to enable clock to the AHB2 bus by setting the RCC peripheral.
//The RCC is in AHB1 adress space.
//Base address of AHB1: 0x4002 0000
//Offset of RCC: 0x0000 1000

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

//In order to enable clock to GPIOA (in AHB2), set RCC_AHB2EN_R to 0x0000 0001
#define GPIOAEN (1U<<0)

#define MODE_R_OFFSET (0x00UL)
//We are interested in configuring register for GPIOA pin 5.
//We must configure GPIOA_BASE + MODE_R_OFFSET, and look at bits 10 and 11
#define GPIOA_MODE_R (*(volatile unsigned int *)(GPIOA_BASE + MODE_R_OFFSET))
//We want to set it to output pin.
/*
 * Bits 31:0 MODE[15:0][1:0]: Port x configuration I/O pin y (y = 15 to 0)
These bits are written by software to configure the I/O mode.
00: Input mode
01: General purpose output mode
10: Alternate function mode
11: Analog mode (reset state)
 * */
//We must set pin 10 to 1 and pin 11 to 0.

/*
 * (1U<<10)    // Set bit 10 to 1
 * &=~(1U<<11) //Set bit 11 to 0*/

//We must be able to set the data register to 1 or 0, to turn the LED on or off.

#define OD_R_OFFSET (0x14UL) //Output data register offset
#define GPIOA_OD_R (*(volatile unsigned int *)(GPIOA_BASE + OD_R_OFFSET))
#define PIN5 (1U<<5)
#define LED_PIN PIN5 //LED2, user LED









