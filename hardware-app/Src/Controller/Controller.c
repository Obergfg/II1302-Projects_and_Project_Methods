/**
 *Author: Fredrik Öberg
 *Co-Authors: Max Ryblad
 *Date of generation: 200430
 *Date of  update: 20-05-05
 *Code Properties: The code serves as a controller which has the purpose of keeping 
 *                 the encapsulation of the code as high as poosible.
*/
#include "Constants.h"
#include "Controller.h"
#include "WiFi.h"
#include "LightSensor.h"
#include "Moisture.h"
#include "DisplayLight.h"


/*
Start function of the controller "class", runs initialization commands like checking the wifi.

@huart handles Structure definition
*/
uint8_t ATConnectWifiResponse[500];
void startController(UART_HandleTypeDef *huart){
	setDraughtThreshhold(DROUGHTTHRESHHOLD);
	
	//if(checkWifiConnection() == 0){
		//if(connectToWifi(huart) == HAL_OK){
			uint8_t ATLocalIP[] = "AT+CIFSR\r\n";
			if(HAL_UART_Transmit(huart, ATLocalIP, sizeof(ATLocalIP), 1000) == HAL_OK){
				HAL_UART_Receive(huart, ATConnectWifiResponse, sizeof(ATConnectWifiResponse), 1000);
			}
			//Something is wrong, cannot continue...
			//loop(huart);
		//}
	//}
	//loop(huart);
}

/*
The outer loop of the whole program that run continously, this is the heart of the program.

@huart handles Structure definition
*/
void loop(UART_HandleTypeDef *huart){
	while(1){
		unsigned int * sensorValues = updateSensorValues();
		int waterPercent = calculateMoisture(sensorValues[moistureSensorPinIndex]);
		int lightPercent = setLightData(sensorValues[lightSensorPinIndex]);
		
		if(UPLOADMOISTURE)
			plantTooDryCheck(waterPercent);
		
		updateDatabase(lightPercent, waterPercent, huart);
		
		HAL_Delay(LOOPDELAY);
	}
}

/*
Runs functions in the WiFi.c file to check whether or not 
the ESP8266(wifi) module has a working wifi connection or not

return 0 if false, 1 if true.
*/
int checkWifiConnection(){
	return 1;
}

/*
Gets drought threshhold values from Moisture.c and compares it the waterPercent.
Turns on or off LED lamps on ST if it is too dry or not.

@waterPercent the current measured water/moisture percentage.
*/
void plantTooDryCheck(int waterPercent){
	if(getDraughtThreshhold() > waterPercent){
		setBlueLED(1);
	}
	else{
		setBlueLED(0);
	}
}



/*
* Pushes the sensors processed data to the database
*
* @light the light level in percent
* @water the moisture level in percent;
* @huart handles Structure definition
*/
void updateDatabase(int light, int water, UART_HandleTypeDef *huart){

	if(UPLOADLIGHT == 1){
		initiateLightTransmission(light, huart);
	}
	if(UPLOADMOISTURE == 1){
		initiateMoistureTransmission(water, huart);
	}
}


