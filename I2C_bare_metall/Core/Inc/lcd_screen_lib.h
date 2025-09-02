/*
 * led_screen_lib.h
 *
 *  Created on: Mar 16, 2025
 *      Author: Christine
 */

#ifndef INC_LCD_SCREEN_LIB_H_
#define INC_LCD_SCREEN_LIB_H_

#define LED_DEVICE_ADDR (0x27)

#define LED_HEADER_RS 0x01
#define LED_HEADER_ENABLE 0x04
#define LED_HEADER_BACKLIGHT 0x08

void led_init();
void led_send_character(char ch);
void led_send_string(char* str);

#endif /* INC_LCD_SCREEN_LIB_H_ */
