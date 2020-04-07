/**
 *Author: Max
 *Co-Authors:
 *Date of generation: 20/04/03
 *Date of  update:20/04/03
 *Code Properties: This class takes care of turning on and off the water pump
 as well as updating how much water is int the tank.
*/

int waterTankMax;
int waterTankCurrent;

/*
  Starts the pump to start watering. Note that it has to be tuned back off again.
*/
void startPump(){

}
/*
  Stops the pump and watering of the plant.
*/
void stopPump(){

}
/*
  Sets the maximum amount of water the watertank can hold (in milliliters)

  @param the amount the tank can hold. (in milliliters)
*/
void setWaterTankMax(int newVolume){
  if(newVolume > 0){
    waterTankMax = newVolume;
  }
}
/*
  Gets the maximum amount of water the watertank can hold. (in milliliters)

  @return the amount the tank can hold in milliliters.
*/
int getWaterTankMax(){
  return waterTankMax;
}
/*
  Sets the current amount of water in the tank. (in milliliters)

  @param The new current amount of water left in the tank. (int milliliters)
*/
void setWaterTankCurrent(int newVolume){
  if(newVolume > 0){
    waterTankCurrent = newVolume;
  }
}
/*
  Gets the current amount of water in the tank. (in milliliters)

  @return The current amount of water left in the tank. (in milliliters)
*/
int getWaterTankCurrent(){
  return waterTankCurrent;
}




/*
  Test function used to test that functions work propetly.

  @return an integer to signalize which test that failed. returns 0 if all tests were successful.
*/
int waterpumpTest(){
  setWaterTankMax(0);
  if(getWaterTankMax() != 0){
    return 1;
  }
  setWaterTankMax(100);
  if(getWaterTankMax() != 100){
    return 2;
  }
  setWaterTankMax(-100);
  if(getWaterTankMax() == -100){
    return 3;
  }


  setWaterTankCurrent(0);
  if(getWaterTankCurrent() != 0){
    return 4;
  }
  setWaterTankCurrent(100);
  if(getWaterTankCurrent() != 100){
    return 5;
  }
  setWaterTankCurrent(-100);
  if(getWaterTankCurrent() == -100){
    return 6;
  }

  return 0;
}
