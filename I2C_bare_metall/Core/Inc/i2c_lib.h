/*
 * i2c_lib.h
 *
 *  Created on: Sep 2, 2025
 *      Author: Christine
 */

#ifndef INC_I2C_LIB_H_
#define INC_I2C_LIB_H_
#include <stdint.h>

void i2c_setup(void);
void i2c_send_data(uint32_t slave_address, uint32_t size, uint8_t* data);

#endif /* INC_I2C_LIB_H_ */
