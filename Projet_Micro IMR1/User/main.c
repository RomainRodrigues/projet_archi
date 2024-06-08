//===========================================================//
// Projet Micro - INFO1 - ENSSAT - S2 2018							 //
//===========================================================//
// File                : Programme de d part
// Hardware Environment: Open1768
// Build Environment   : Keil  Vision
//===========================================================//

#include "lpc17xx_gpio.h"
#include "lpc17xx_i2c.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_timer.h"
#include "touch\ili_lcd_general.h"
#include "touch\lcd_api.h"
#include "affichagelcd.h"
#include "touch\touch_panel.h"

#include "globaldec.h" // fichier contenant toutes les d clarations de variables globales
#include <stdio.h>

#define entree 0
#define sortie 1

short colors[4] = {0xFFE0, 0x07E0, 0x001F, 0xF800};
int currentColor = 0;
uint8_t dataOld[2] = {0x01,0x30};
uint8_t dataNew[2] = {0x02,0x30};
uint8_t dataRecupere;

void pin_Configuration()
{
	PINSEL_CFG_Type config_broche_uart; //  declaration d une structure de configuration et donc reservation memoire pour cette structure
	//--------------------------------------------------

	// Initialisation GPIO2.10 et GPIO2.11 en input
	GPIO_SetDir(2, (1 << 10) | (1 << 11), 0);

	// remplissage de la structure de configuration . NB: il faut remplir tous les champs, sinon risque d'utiliser un champ qui contient n'importe quoi
	config_broche_uart.Portnum = PINSEL_PORT_0;
	config_broche_uart.Pinnum = PINSEL_PIN_27;
	config_broche_uart.Funcnum = PINSEL_FUNC_1;
	config_broche_uart.Pinmode = PINSEL_PINMODE_PULLUP;
	config_broche_uart.OpenDrain = PINSEL_PINMODE_NORMAL;

	// appel de la fonction qui va vraiment initialiser les registres du PIN Connect bloc
	PINSEL_ConfigPin(&config_broche_uart);

	// pareil pour P0.28 il n'y a que le PIN qui change la fonction est la même
	config_broche_uart.Pinnum = PINSEL_PIN_28;

	// appel de la fonction qui va vraiment initialiser les registres du PIN Connect bloc
	PINSEL_ConfigPin(&config_broche_uart);
}

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

void saveNewColor(int index){
		dataNew[1] = index;
		i2c_eeprom_write(NULL, &dataNew, sizeof(dataNew));
}

char* getColorName(int index){
	switch (index){
		case 0:
			return "Yellow";
		case 1:
			return "Green";
		case 2:
			return "Blue";
		case 3:
			return "Red";
		default:
			return "Green";
	}
}

void print_dessin(){
		lcd_clear( colors[currentColor] );
		//sprintf(chaine,"        Green      ");
	  //LCD_write_english_string (32,10,chaine,White,colors[currentColor]);
	  dessiner_rect(80,40,80,80,2,1,Black,Black);
		sprintf(chaine,"Back");
	  LCD_write_english_string (110,70,chaine,White,Black);
	  dessiner_rect(35,130,80,80,2,1,Black,Yellow);
	  dessiner_rect(125,130,80,80,2,1,Black,Green);
	  dessiner_rect(35,220,80,80,2,1,Black,Blue);
	  dessiner_rect(125,220,80,80,2,1,Black,Red);
	
		i2c_eeprom_read(NULL, 0x01, &dataRecupere, 1);
	sprintf(chaine,"Old: %-6s,Current: %-6s", getColorName(dataRecupere),getColorName(currentColor));
	  LCD_write_english_string (10,10,chaine,White,Black);
}

void testEcran(){
	touch_read();
	dataOld[1] = currentColor;
	if(touch_x >= 900 && touch_x <= 1800 && touch_y >= 1500 && touch_y <= 2500){ 
		i2c_eeprom_write(NULL, &dataOld, sizeof(dataOld));
		currentColor = 0;
				
		saveNewColor(currentColor);
		
		print_dessin();
	} else if(touch_x >= 2400 && touch_x <= 3300 && touch_y >= 1500 && touch_y <= 2500){ 
		i2c_eeprom_write(NULL, &dataOld, sizeof(dataOld));
		currentColor = 1;
		
		saveNewColor(currentColor);
		
		print_dessin();
	} else if(touch_x >= 900 && touch_x <= 1800 && touch_y >= 2700 && touch_y <= 3250){ 
		i2c_eeprom_write(NULL, &dataOld, sizeof(dataOld));
		currentColor = 2;
				
		saveNewColor(currentColor);
		
		print_dessin();
	} else if(touch_x >= 2400 && touch_x <= 3300 && touch_y >= 2700 && touch_y <= 3250){ 
		i2c_eeprom_write(NULL, &dataOld, sizeof(dataOld));
		currentColor = 3;
				
		saveNewColor(currentColor);
		
		print_dessin();
	}else if(touch_x >= 1600 && touch_x <= 2700 && touch_y >= 800 && touch_y <= 1400){ 
		i2c_eeprom_read(NULL, 0x01, &dataRecupere, 1);
		currentColor = dataRecupere;
				
		saveNewColor(currentColor);
		
		print_dessin();
	}
}

//================================================
// Timer handler, pas besoin d'appel fonction
//================================================
void TIMER0_IRQHandler(void) {
		// Vérifiez si une interruption de MR0 s'est produite
    if (TIM_GetIntStatus(LPC_TIM0, TIM_MR0_INT)) {
        // Effacer l'interruption
        TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
        
        if(TP_DOWN()){
					testEcran();
				}
    }
}

 
//==========================================
//Initialisation du timer
//==========================================
void initTimer() {
	
		// Déclaration des structures de configuration
    PINSEL_CFG_Type configPinsel;
    TIM_TIMERCFG_Type configTimer;
    TIM_MATCHCFG_Type maconfigmatch;

    // Configuration du pin P1.28 sur MAT0.0
    configPinsel.Portnum = PINSEL_PORT_1;
    configPinsel.Pinnum = PINSEL_PIN_28;
    configPinsel.Funcnum = PINSEL_FUNC_3;
    configPinsel.Pinmode = PINSEL_PINMODE_PULLUP;
    configPinsel.OpenDrain = PINSEL_PINMODE_NORMAL;
    PINSEL_ConfigPin(&configPinsel);

    // Configuration du timer
    configTimer.PrescaleOption = TIM_PRESCALE_USVAL;  // Précision en microsecondes
    configTimer.PrescaleValue = 1;  // Prescaler à 1 µs
    TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &configTimer);

    // Configuration du match pour générer une interruption toutes les 10 ms
    maconfigmatch.MatchChannel = 0;
    maconfigmatch.IntOnMatch = ENABLE;  // Interruption activée sur correspondance
    maconfigmatch.StopOnMatch = DISABLE;
    maconfigmatch.ResetOnMatch = ENABLE;
    maconfigmatch.ExtMatchOutputType = TIM_EXTMATCH_TOGGLE;
    maconfigmatch.MatchValue = 10000;  // 10 ms
    TIM_ConfigMatch(LPC_TIM0, &maconfigmatch);

    // Activer l'interruption du timer 0
    NVIC_EnableIRQ(TIMER0_IRQn);

    // Démarrer le timer
    TIM_Cmd(LPC_TIM0, ENABLE);
}


//===========================================================//
// Function: Main
//===========================================================//
int main(void)
{

	int n;
	// char* data = "EZRZER";

	// Init(); // init variables globales et pinsel pour IR =>   faire

	lcd_Initializtion(); // init pinsel ecran et init LCD
	touch_init(); // init pinsel tactile et init tactile;   ne laisser que si vous utilisez le tactile
	pin_Configuration();
	init_i2c_eeprom();
	initTimer();

	i2c_eeprom_read(NULL, 0x02, &dataRecupere, 1);
	
	if(dataRecupere >= 0 && dataRecupere <= 3){
		currentColor = dataRecupere;// reload the last color loaded
	}
	
	print_dessin();

	while (1)
	{
	};
	// pour l'instant, le main fait juste quelques inits ...   vous d' crire le reste
}

//---------------------------------------------------------------------------------------------
#ifdef DEBUG
void check_failed(uint8_t *file, uint32_t line)
{
	while (1)
		;
}
#endif
