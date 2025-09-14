/*
 * i2c_lib.c
 *
 *  Created on: Sep 2, 2025
 *      Author: Christine
 */
#include "i2c_lib.h"
#include <stdint.h>

#define PERIPH_BASE (0x40000000UL)

#define AHB1PERIPH_OFFSET (0x00020000UL)
#define AHB1PERIPH_BASE (PERIPH_BASE + AHB1PERIPH_OFFSET)

#define RCCPERIPH_OFFSET (0x00001000UL)
#define RCCPERIPH_BASE (AHB1PERIPH_BASE + RCCPERIPH_OFFSET)

#define RCC_APB1ENR_OFFSET (0x58UL)
#define RCC_APB1ENR (RCCPERIPH_BASE + RCC_APB1ENR_OFFSET)

#define RCC_AHB2ENR_OFFSET (0x4CUL)
#define RCC_AHB2ENR (RCCPERIPH_BASE + RCC_AHB2ENR_OFFSET)

#define AHB2PERIPH_OFFSET (0x08000000UL)
#define AHB2PERIPH_BASE (PERIPH_BASE + AHB2PERIPH_OFFSET)

#define GPIOBPERIPH_OFFSET (0x400)
#define GPIOBPERIPH_BASE (AHB2PERIPH_BASE + GPIOBPERIPH_OFFSET)

#define APB1PERIPH_OFFSET (0x00004400UL)
#define APB1PERIPH_BASE (PERIPH_BASE + APB1PERIPH_OFFSET)

#define I2C1PERIPH_OFFSET (0x5400UL)
#define I2C1PERIPH_BASE (PERIPH_BASE + I2C1PERIPH_OFFSET)//(APB1PERIPH_BASE + I2C1PERIPH_OFFSET)


#define GPIOBEN (1U<<1)
#define I2C1EN (1U<<21)
#define AFSEL4 0b0100

typedef struct
{
	volatile uint32_t DUMMY[19];
	volatile uint32_t AHB2ENR;
	volatile uint32_t AHB3ENR[2];
	volatile uint32_t APB1ENR1;
}RCC_TypeDef;

typedef struct
{
	volatile uint32_t MODE;
	volatile uint32_t OTYPE;
	volatile uint32_t OSPEED;
	volatile uint32_t PUPDIR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
	volatile uint32_t BRR;
}GPIO_TypeDef;

typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t DUMMY[2];
	volatile uint32_t TIMINGR;
	volatile uint32_t TIMOUT;
	volatile uint32_t ISR;
	volatile uint32_t ICR;
	volatile uint32_t PEC;
	volatile uint32_t RXDR;
	volatile uint32_t TXDR;
}I2C_TypeDef;

#define RCC ((RCC_TypeDef*) RCCPERIPH_BASE)
#define GPIOB ((GPIO_TypeDef*) GPIOBPERIPH_BASE)
#define I2C1 ((I2C_TypeDef*) I2C1PERIPH_BASE)

static void i2c_start_communication(uint32_t slave_address, uint32_t size);
static void i2c_send_byte(uint8_t data);

void i2c_setup(void)
{
	// enable clock access to i2c1 and gpiob
		// enable clock access to i2c1
	RCC->APB1ENR1 |= I2C1EN;
		// enable clock access to GPIOB
	RCC->AHB2ENR |= GPIOBEN;

	// configure pins
		// alternate function
	GPIOB->MODE &= ~(0b11<<16);
	GPIOB->MODE &= ~(0b11<<18);
	GPIOB->MODE |= (0b10<<16);
	GPIOB->MODE |= (0b10<<18);

	GPIOB->AFRH |= (AFSEL4);
	GPIOB->AFRH |= (AFSEL4<<4);

		// open drain
	GPIOB->OTYPE |= (1U<<8);
	GPIOB->OTYPE |= (1U<<9);

		// high speed
	GPIOB->OSPEED |= (0b10<<16);
	GPIOB->OSPEED |= (0b10<<18);

		// pull up
	GPIOB->PUPDIR &= ~(0b11<<16);
	GPIOB->PUPDIR &= ~(0b11<<18);

	GPIOB->PUPDIR |= (0b01<<16);
	GPIOB->PUPDIR |= (0b01<<18);

	// reset i2c
	I2C1->CR1 &= ~(1<<0);

	// Wait at least 3 clock cycles

	// configure ccr
	uint32_t i2c_timing = 0x00303D5B;
	I2C1->TIMINGR |= i2c_timing;

	// AUTOEND = 1 in cr2

	// enable i2c
	I2C1->CR1 |= (1<<0);
}

void i2c_send_data(uint32_t slave_address, uint32_t size, uint8_t* data)
{
	i2c_start_communication(slave_address, size+1);
	for (int i = 0; i < size; i++)
	{
		i2c_send_byte(data[i]);
	}
	I2C1->CR2 |= (1U<<14);
}

static void i2c_start_communication(uint32_t slave_address, uint32_t size)
{
	// Set address mode (7-bit)
	I2C1->CR2 |= (slave_address<<1); // Bits 8, 9 and 0 are don't care.
	//I2C1->CR2 |= (1U<<10); // R/W -> W
	I2C1->CR2 |= (size<<16); // Size of data

	//I2C1->CR2 |= (1U<<25); // AUTOEND
	// Make sure the I2C-bus is idle. Check that the IDR bits of the sda and scl pins are set.
	I2C1->CR2 |= (1U<<13); // START

	while(I2C1->CR2 & (1U<<13)); // Wait for START to be cleared, which can mean that it is sent
}

static void i2c_send_byte(uint8_t data)
{
	I2C1->TXDR |= (data<<0); // Data to be sent
	while(!(I2C1->ISR & (1U<<1))); // TXIS
}


