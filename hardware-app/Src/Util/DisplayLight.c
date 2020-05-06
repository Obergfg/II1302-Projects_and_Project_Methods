/**
 *Author: Max Ryblad
 *Co-Authors:
 *Date of generation: 20-05-05
 *Date of  update: 
 *Code Properties: Code controlling the green and blue LED lamps on the ST board.
*/
#include "main.h"
//#include "../main.c"

/*
Turns on or off the blue LED on the ST card, depending on inputted value.

@bool is an integer, if 0 then turn off LED, if 1 turn on.
*/
void setBlueLED(int bool){
	HAL_GPIO_WritePin(LD3_GPIO_Port, LD4_Pin, bool);
}


/*
Turns on or off the green LED on the ST card, depending on inputted value.

@bool is an integer, if 0 then turn off LED, if 1 turn on.
*/
void setGreenLED(int bool){
	HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, bool);
}
