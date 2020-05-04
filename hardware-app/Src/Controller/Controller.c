/**
 *Author: Fredrik Öberg
 *Co-Authors: -
 *Date of generation: 200430
 *Date of  update: -
 *Code Properties: The code serves as a controller which has the purpose of keeping 
 *                 the encapsulation of the code as high as poosible.
*/


#include "../constants.c"
#include "Controller.h"
#include "WiFi.h"
#include "LightSensor.h"
#include "Moisture.h"



    /*
    * Receives data from the main function and processe that data by calling 
    * the corresponding function of the given data and after that sends the 
    * processed data to the database.
    *
    * @rawData is the raw data received from the sensors of the STM32 module.
    * @huart handles Structure definition
    */
void updateDatabase(unsigned int* rawData, UART_HandleTypeDef *huart){

	if(UPLOADLIGHT == 1){
			initiateLightTransmission(setLightData(rawData[lightSensorPinIndex]), huart);
	}
	if(UPLOADMOISTURE == 1){
			initiateMoistureTransmission(calculateMoisture(rawData[moistureSensorPinIndex]), huart);
	}
}
