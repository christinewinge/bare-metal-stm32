/*
 * led_screen_lib.c
 *
 *  Created on: Mar 16, 2025
 *      Author: Christine
 */

#include <lcd_screen_lib.h>
#include "i2c_lib.h"

static void send_command(uint8_t command) {
	uint8_t upper_bits = command & 0xF0;
	uint8_t lower_bits = (command << 4) & 0xF0;

	uint8_t send_buffer[4];
	send_buffer[0] = upper_bits | LED_HEADER_BACKLIGHT | LED_HEADER_ENABLE;
	send_buffer[1] = upper_bits | LED_HEADER_BACKLIGHT;

	send_buffer[2] = lower_bits | LED_HEADER_BACKLIGHT | LED_HEADER_ENABLE;
	send_buffer[3] = lower_bits | LED_HEADER_BACKLIGHT;

	i2c_send_data(LED_DEVICE_ADDR, 4, (uint8_t*)&send_buffer);
}

static void send_data(uint8_t data) {
	uint8_t upper_bits = data & 0xF0;
	uint8_t lower_bits = (data << 4) & 0xF0;

	uint8_t send_buffer[4];
	send_buffer[0] = upper_bits | LED_HEADER_RS | LED_HEADER_BACKLIGHT | LED_HEADER_ENABLE;
	send_buffer[1] = upper_bits | LED_HEADER_RS | LED_HEADER_BACKLIGHT;

	send_buffer[2] = lower_bits | LED_HEADER_RS | LED_HEADER_BACKLIGHT | LED_HEADER_ENABLE;
	send_buffer[3] = lower_bits | LED_HEADER_RS | LED_HEADER_BACKLIGHT;

	i2c_send_data(LED_DEVICE_ADDR, 4, (uint8_t*)&send_buffer);
}

void led_init() {
	i2c_setup();

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
