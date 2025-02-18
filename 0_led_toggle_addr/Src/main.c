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

#define PERIPH_BASE (0x40000000UL)
#define AHB2PERIPH_OFFSET (0x0800 0000UL)
#define AHB2PERIPH_BASE (PERIPH_BASE + AHB2PERIPH_OFFSET)
