/*
 * led_screen_lib.c
 *
 *  Created on: Mar 16, 2025
 *      Author: Christine
 */

#include <lcd_screen_lib.h>

I2C_HandleTypeDef _hi2c;

static void send_command(uint8_t command) {
	uint8_t upper_bits = command & 0xF0;
	uint8_t lower_bits = (command << 4) & 0xF0;

	uint8_t send_buffer[4];
	send_buffer[0] = upper_bits | LED_HEADER_BACKLIGHT | LED_HEADER_ENABLE;
	send_buffer[1] = upper_bits | LED_HEADER_BACKLIGHT;

	send_buffer[2] = lower_bits | LED_HEADER_BACKLIGHT | LED_HEADER_ENABLE;
	send_buffer[3] = lower_bits | LED_HEADER_BACKLIGHT;

	HAL_I2C_Master_Transmit(&_hi2c, LED_DEVICE_ADDR, (uint8_t*)&send_buffer, 4, 10);
}

static void send_data(uint8_t data) {
	uint8_t upper_bits = data & 0xF0;
	uint8_t lower_bits = (data << 4) & 0xF0;

	uint8_t send_buffer[4];
	send_buffer[0] = upper_bits | LED_HEADER_RS | LED_HEADER_BACKLIGHT | LED_HEADER_ENABLE;
	send_buffer[1] = upper_bits | LED_HEADER_RS | LED_HEADER_BACKLIGHT;

	send_buffer[2] = lower_bits | LED_HEADER_RS | LED_HEADER_BACKLIGHT | LED_HEADER_ENABLE;
	send_buffer[3] = lower_bits | LED_HEADER_RS | LED_HEADER_BACKLIGHT;

	HAL_I2C_Master_Transmit(&_hi2c, LED_DEVICE_ADDR, (uint8_t*)&send_buffer, 4, 10);
}

void led_init(I2C_HandleTypeDef hi2c) {
	_hi2c = hi2c;

	send_command(0x30);
	HAL_Delay(5);
	send_command(0x30);
	HAL_Delay(1);
	send_command(0x30);
	HAL_Delay(10);

	send_command(0x20);
	HAL_Delay(10);

	send_command(0b00101000);
	HAL_Delay(10);

	send_command(0b00001000);
	HAL_Delay(10);

	send_command(0b00000001);
	HAL_Delay(10);

	send_command(0b00000110);
	HAL_Delay(10);

	send_command(0b00001111);
	HAL_Delay(10);
}

void led_send_character(char ch) {
	send_data((uint8_t) ch);
}

void led_send_string(char* str) {
	while(*str) led_send_character(*str++);
}
