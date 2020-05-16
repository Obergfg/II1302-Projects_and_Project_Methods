/**
 *Author: Fredrik �berg
 *Co-Authors: Max Ryblad
 *Date of generation: 200429
 *Date of  update: 20-05-05
 *Code Properties: The code handles the communication between the STM32 module and the ESP8266 wifi module.
*/

#include "private.c"
#include "main.h"
#include "WiFi.h"


uint8_t postBuffer[256];
uint8_t receiveBuffer[512];


 /*
    * Transmits data to the ESP8266 module.
    *
    * @command is the command sent to ESP8266.
		* @size is the size of the command in bytes.
		* @huart handles Structure definition
    *
    * @return is the status of the connection between STM32 and ESP8266.
    */
HAL_StatusTypeDef transmit(uint8_t* command, int size, UART_HandleTypeDef *huart){

	if(HAL_UART_Transmit(huart, command, size, 1000) == HAL_OK)
			return	HAL_UART_Receive(huart, receiveBuffer, sizeof(receiveBuffer), 1000);
	else
			return HAL_ERROR;
		
}


/*
    * Restarts the ESP8266 module.
    *.
		* @huart handles Structure definition
    *
    * @return is the status of the connection between STM32 and ESP8266.
    */
HAL_StatusTypeDef restartWiFi(UART_HandleTypeDef *huart){

	uint8_t reset[] = "AT+RST\r\n";

	return transmit(reset, sizeof(reset), huart);
}


/*
    * Restores the ESP8266 module.
    *.
		* @huart handles Structure definition
    *
    * @return is the status of the connection between STM32 and ESP8266.
    */
HAL_StatusTypeDef restoreWiFi(UART_HandleTypeDef *huart){

	uint8_t reset[] = "AT+RESTORE\r\n";

	return transmit(reset, sizeof(reset), huart);
}

/*
    * Connects the ESP8266 module to router/wifi specified in private.c
    *.
		* @huart handles Structure definition
    *
    * @return is the status of the connection between STM32 and ESP8266.
    */
HAL_StatusTypeDef connectToRouter(UART_HandleTypeDef *huart){

	uint8_t reset[] = ATCWJAP;

	return transmit(reset, sizeof(reset), huart);
}


/*
    * Sets the SSL buffer of the ESP8266 module.
    *
		* @huart handles Structure definition
    *
    * @return is the status of the connection between STM32 and ESP8266.
    */
HAL_StatusTypeDef setSSLbuffer(UART_HandleTypeDef *huart){

	uint8_t sslBuf[] = "AT+CIPSSLSIZE=4096\r\n";
	
	return transmit(sslBuf, sizeof(sslBuf), huart);
}

/*
    * Gets the access points the ESP8266 module reaches.
    *
		* @huart handles Structure definition
    *
    * @return is the status of the connection between STM32 and ESP8266.
    */
HAL_StatusTypeDef getAP(UART_HandleTypeDef *huart){

	uint8_t AP[] = "AT+CWLAP\r\n";
	
	return transmit(AP, sizeof(AP), huart);
}


/*
    * Sets the Cw mode of the ESP8266 module.
    *
		* @huart handles Structure definition
    *
    * @return is the status of the connection between STM32 and ESP8266.
    */
HAL_StatusTypeDef setCWMode(UART_HandleTypeDef *huart){

	uint8_t cwMode[] = "AT+CWMODE=1\r\n";
	
	return transmit(cwMode, sizeof(cwMode), huart);
		
}


/*
    * Gets the IP of the ESP8266 module.
    *
		* @huart handles Structure definition
    *
    * @return is the status of the connection between STM32 and ESP8266.
    */
HAL_StatusTypeDef getIP(UART_HandleTypeDef *huart){

	uint8_t checkIP[] = "AT+CIFSR\r\n";

	return transmit(checkIP, sizeof(checkIP), huart);
}


/*
    * Sets the mux parameter of the ESP8266 module to 0.
    *
		* @huart handles Structure definition
    *
    * @return is the status of the connection between STM32 and ESP8266.
    */
HAL_StatusTypeDef setMux(UART_HandleTypeDef *huart){

	uint8_t mux[] = "AT+CIPMUX=0\r\n";

	return transmit(mux, sizeof(mux), huart);
}


/*
    * Closes the connection the ESP8266 module has established.
    *
		* @huart handles Structure definition
    *
    * @return is the status of the connection between STM32 and ESP8266.
    */
HAL_StatusTypeDef closeConnection(UART_HandleTypeDef *huart){

		uint8_t close[] = "AT+CIPCLOSE\r\n\r\n";
	
		return transmit(close, sizeof(close), huart);
}


/*
    * Initates a SSl connection between the ESP8266 module and a Firebase database.
    *
		* @huart handles Structure definition
    *
    * @return is the status of the connection between STM32 and ESP8266.
    */
HAL_StatusTypeDef initateConnection(UART_HandleTypeDef *huart){

	uint8_t start[] = CIPSTART;
	return	transmit(start, sizeof(start), huart);
}

/*
* Creates the post message used to specify where the ESP8266 module sends the given data.
*
* @adress is the incomplete URL to the client receiving the data.
* @data is the data being sent.
* @huart handles Structure definition
*
* @return is the size of the complete message being sent to the ESP8266 module. 
*/
int createPostMessage(char* adress, unsigned int data, UART_HandleTypeDef *huart){
	
	uint8_t contentLength[8];
	uint8_t sendBuffer[32];
	
	sprintf(contentLength, "%d", data);
	
	int cl = 0;
	
	while(contentLength[cl] != NULL)
		   cl++;
	
	
	sprintf(postBuffer, adress, cl, data);
	
	int cnt = 0;
	
	while(postBuffer[cnt] != NULL)
		   cnt++;
	
	sprintf(sendBuffer, "AT+CIPSEND=%d\r\n", cnt);
	
	transmit(sendBuffer, sizeof(sendBuffer), huart);
	
  return cnt;
}

/*
    * Sends the given light data to the Firebase database.
    *
    * @data is the light data received from the STM32 module.
		* @huart handles Structure definition
    *
    * @return is the status of the connection between STM32 and ESP8266.
    */
HAL_StatusTypeDef sendLightData(unsigned int data, UART_HandleTypeDef *huart){
	
		char post[] = POSTLIGHT;

	  int size = createPostMessage(post,  data, huart);
	
		return transmit(postBuffer, size, huart);
}

/*
* Sends the given moisture data to the Firebase database.
*
* @data is the moisture in percent, an int between 0 and 100.
* @huart handles Structure definition
*
* @return is the status of the connection between STM32 and ESP8266.
*/
HAL_StatusTypeDef sendMoistureData(unsigned int data, UART_HandleTypeDef *huart){

	char post[] = POSTMOISTURE;
	
	int size = createPostMessage(post, data, huart);
	
	return	transmit(postBuffer, size, huart);
	
}

/*
    * Initiates the complete light data transmission process of the ESP8266 module.
    *
    * @lightData is the light data received from the STM 32 module. 
		* @huart handles Structure definition
    *
    * @return is the status of the connection between STM32 and ESP8266.
    */
HAL_StatusTypeDef initiateLightTransmission(unsigned int lightData, UART_HandleTypeDef *huart){
	
		  setSSLbuffer(huart);
	    setMux(huart);
	    initateConnection(huart);
    	sendLightData(lightData, huart);

			return closeConnection(huart);
}


/*
    * Initiates the complete moisture data transmission process of the ESP8266 module.
    *
    * @moistureData is the moisture data received from the STM 32 module. 
		* @huart handles Structure definition
    *
    * @return is the status of the connection between STM32 and ESP8266.
    */
HAL_StatusTypeDef initiateMoistureTransmission(unsigned int moistureData, UART_HandleTypeDef *huart){
	
		setSSLbuffer(huart);
		setMux(huart);
		initateConnection(huart);
		sendMoistureData(moistureData, huart);

		return closeConnection(huart);
}

/*
Runs functions in the WiFi.c file to connect to wifi.

return 0 if false, 1 if true.
*/
HAL_StatusTypeDef connectToWifi(UART_HandleTypeDef *huart){
		restoreWiFi(huart);
		HAL_Delay(1000);
		setCWMode(huart);
		HAL_Delay(1000);
		connectToRouter(huart);
	
		return closeConnection(huart);
}

