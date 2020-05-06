/**
 *Author: Max Ryblad
 *Co-Authors:
 *Date of generation: 20/04/03
 *Date of  update: 20/05/04
 *Code Properties: Code controlling the moisture sensor.
*/

#include "Moisture.h"

int draughtThreshhold; 	//0 - 100
int moistureThreshhold; //0 - 100
int currentMoisture;		//0 - 100

/**
* Gets the current moisture of the plant
*
*	@rawSensorData value between 0 and 4095 representing resistance to sensor. Higher number means less water.
*
* @return float value between 0 and 100 indicating the percentage of wetness.
* 100 means 100% wet and 0 means that it is completly dry.
*/
int calculateMoisture(int rawSensorData){
  currentMoisture = (1-(rawSensorData/4095.0)) * 100;
	if(currentMoisture < 0)
		currentMoisture = 0;
	else if(currentMoisture > 100)
		currentMoisture = 100;
	return currentMoisture;
}

/*
  Gets the threshhold for moisture, the moisture that we do not want to
  go over. This is the number where the waterer stops watering.

  @return returns the current moistureThreshhold which is an integer value between 0 and 100.
*/
int getMoistureThreshhold(){
  if(moistureThreshhold >= 0 && moistureThreshhold <= 100){
    return moistureThreshhold;
  }
  else{
    return -1;
  }
}

/*
  Sets the threshhold for moisture, the moisture that we do not want to
  go over. This is the number where the waterer stops watering.

  @param moisture is a integer value between 0 and 100 to sets the moistureThreshhold.
*/
void setMoistureThreshhold(int newMoisture){
  if(newMoisture >= 0 && newMoisture <= 100){
    moistureThreshhold = newMoisture;
  }
}

/*
  Gets the threshhold for draught, the draughtness level that decides when to water.
  If the moisture of the plant goes below the draughtness level, the controller will
  call the waterpump to water the plant.

  @return returns the current draughtThreshhold which is an integer value between 0 and 100.
*/
int getDraughtThreshhold(){
  if(draughtThreshhold >= 0 && draughtThreshhold <= 100){
    return draughtThreshhold;
  }
  else{
    return -1;
  }
}

/*
  Sets the threshhold for draught, the draughtness level that decides when to water.
  If the moisture of the plant goes below the draughtness level, the controller will
  call the waterpump to water the plant.

  @param the new draughtThreshhold which is an integer value between 0 and 100.
*/
void setDraughtThreshhold(int newDraught){
  if(newDraught >= 0 && newDraught <= 100){
    draughtThreshhold = newDraught;
  }
}


/*
  Test function used to test that functions work propetly.

  @return an integer to signalize which test that failed. returns 0 if all tests were successful.
*/
int moistureTest(){
  setMoistureThreshhold(0);
  if(getMoistureThreshhold() != 0){
    return 1;
  }
  setMoistureThreshhold(100);
  if(getMoistureThreshhold() != 100){
    return 2;
  }
  setMoistureThreshhold(50);
  if(getMoistureThreshhold() != 50){
    return 3;
  }
  setMoistureThreshhold(-1);
  if(getMoistureThreshhold() < 0){
    return 4;
  }
  setMoistureThreshhold(200);
  if(getMoistureThreshhold() > 100){
    return 5;
  }



  setDraughtThreshhold(0);
  if(getDraughtThreshhold() != 0){
    return 6;
  }
  setDraughtThreshhold(100);
  if(getDraughtThreshhold() != 100){
    return 7;
  }
  setDraughtThreshhold(50);
  if(getDraughtThreshhold() != 50){
    return 8;
  }
  setDraughtThreshhold(-1);
  if(getDraughtThreshhold() < 0){
    return 9;
  }
  setDraughtThreshhold(200);
  if(getDraughtThreshhold() > 100){
    return 10;
  }

  //return 0 means no error.
  return 0;
}
