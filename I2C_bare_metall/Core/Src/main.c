#include <stdint.h>
#include "i2c_lib.h"
#include "lcd_screen_lib.h"

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

	uint32_t led_device_addr = 0x27;
	led_init();
	led_send_character('A');

	while (1)
	{

	}
}

