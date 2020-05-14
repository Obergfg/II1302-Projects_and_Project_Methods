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
void startController(UART_HandleTypeDef *huart){
	setDraughtThreshhold(DROUGHTTHRESHHOLD);
	
	setupWifi(huart);
	
	loop(huart);
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
Calls connectToWifi function in WiFi.c as well as indicates wifi loading by turning on green LED

@huart handles Structure definition
*/
void setupWifi(UART_HandleTypeDef *huart){
	setGreenLED(1);
	connectToWifi(huart);
	setGreenLED(0);
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


