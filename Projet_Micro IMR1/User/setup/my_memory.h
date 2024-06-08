#include "lpc17xx_i2c.h"
#include <stdio.h>

#ifndef __MY_MEMORY_H
#define __MY_MEMORY_H

void init_i2c_eeprom();

void i2c_eeprom_write(uint16_t addr, void *data, int length);

void i2c_eeprom_read(uint8_t addr, uint8_t add_case, void *data_recup, int length);

#endif