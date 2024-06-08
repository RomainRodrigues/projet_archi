#include "my_memory.h"

void init_i2c_eeprom()
{
	I2C_Init(LPC_I2C0, 500000);
	I2C_Cmd(LPC_I2C0, ENABLE);
}

void i2c_eeprom_write(uint16_t addr, void *data, int length)
{
	I2C_M_SETUP_Type i2cSetup;

	i2cSetup.sl_addr7bit = 0x50; // Lu dans la doc de la carte donné par le prof
	i2cSetup.tx_data = (uint8_t*)data;
	i2cSetup.tx_length = length;//length
	i2cSetup.rx_data = NULL;
	i2cSetup.rx_length = NULL;
	i2cSetup.retransmissions_max = 10;
	i2cSetup.callback = NULL;

	I2C_MasterTransferData(LPC_I2C0, &i2cSetup, I2C_TRANSFER_POLLING);
}

void i2c_eeprom_read(uint8_t addr, uint8_t add_case, void *data_recup, int length)
{

	I2C_M_SETUP_Type setupi2c;
    
    setupi2c.sl_addr7bit = 0x50; 
    setupi2c.tx_data = &add_case; 
    setupi2c.tx_length = 1;	
    
		
		setupi2c.rx_data = data_recup;
	  setupi2c.rx_length = length;  
    setupi2c.retransmissions_max = 10;
		setupi2c.retransmissions_count = 0;
		setupi2c.tx_count = 0;
		setupi2c.rx_count = 0;
		
	setupi2c.callback = NULL;
    
    I2C_MasterTransferData(LPC_I2C0, &setupi2c, I2C_TRANSFER_POLLING);
}