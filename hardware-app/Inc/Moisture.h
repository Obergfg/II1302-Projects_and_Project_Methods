/**
 *Author: Max Ryblad
 *Co-Authors: -
 *Date of generation: 200504
 *Date of  update: -
 *Code Properties: The code serves as a header file for the Moisture.c file and contains 
 *                 declarations of functions and variables.
*/

#ifndef MOISTURE_H
#define MOISTURE_H

float calculateMoisture(unsigned int rawSensorData);
float getMoistureThreshhold(void);
void setMoistureThreshhold(float newMoisture);
float getDraughtThreshhold(void);
void setDraughtThreshhold(float newMoisture);


#endif
