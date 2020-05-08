/**
 *Author: Fredrik Öberg
 *Co-Authors: -
 *Date of generation: 200430
 *Date of  update: -
 *Code Properties: The code serves as a header file for the Controller.c file and contains 
 *                 declarations of functions and variables.
*/

#include "main.h"

#ifndef CONTROLLER_H
#define CONTROLLER_H

void startController(UART_HandleTypeDef *huart);
void loop(UART_HandleTypeDef *huart);
void setupWifi(UART_HandleTypeDef *huart);
void plantTooDryCheck(int);
void updateLED(int);
void updateDatabase(int light, int water, UART_HandleTypeDef *huart);

#endif
