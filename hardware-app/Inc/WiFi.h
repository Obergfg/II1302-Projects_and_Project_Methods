
/**
 *Author: Fredrik Öberg
 *Co-Authors: -
 *Date of generation: 200429
 *Date of  update: -
 *Code Properties: The code serves as a header file for the WiFi.c file and contains 
 *                 declarations of functions and variables.
*/

#include "main.h"

#ifndef WIFI_H
#define WIFI_H


HAL_StatusTypeDef transmit(uint8_t* command ,int size, UART_HandleTypeDef *huart);
HAL_StatusTypeDef resetWiFi(UART_HandleTypeDef *huart);
HAL_StatusTypeDef setSSLbuffer(UART_HandleTypeDef *huart);
HAL_StatusTypeDef getAP(UART_HandleTypeDef *huart);
HAL_StatusTypeDef setCWMode(UART_HandleTypeDef *huart);
HAL_StatusTypeDef getIP(UART_HandleTypeDef *huart);
HAL_StatusTypeDef setMux(UART_HandleTypeDef *huart);
HAL_StatusTypeDef initateConnection(UART_HandleTypeDef *huart);
HAL_StatusTypeDef sendLightData(unsigned int data, UART_HandleTypeDef *huart);
HAL_StatusTypeDef closeConnection(UART_HandleTypeDef *huart);

HAL_StatusTypeDef initiateLightTransmission(unsigned int data, UART_HandleTypeDef *huart);
#endif