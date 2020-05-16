
/**
 *Author: Fredrik Öberg
 *Co-Authors: Max Ryblad
 *Date of generation: 200429
 *Date of  update: 20-05-04
 *Code Properties: The code serves as a header file for the WiFi.c file and contains
 *                 declarations of functions and variables.
*/

#include "main.h"

#ifndef WIFI_H
#define WIFI_H

HAL_StatusTypeDef initiateLightTransmission(unsigned int data, UART_HandleTypeDef *huart);
HAL_StatusTypeDef initiateMoistureTransmission(unsigned int data, UART_HandleTypeDef *huart);

HAL_StatusTypeDef connectToWifi(UART_HandleTypeDef *huart);
#endif
