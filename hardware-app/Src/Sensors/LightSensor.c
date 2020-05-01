/**
 *Author: Fredrik Öberg
 *Co-Authors: -
 *Date of generation: 200425
 *Date of  update: -
 *Code Properties: The code takes raw data from the light sensor of the STM32 unit of the system 
                   and changes it to a value between 0 and 1. The purpose of this is to check 
                   what level of light the plant of the system receives.
*/

#include <math.h>

#include "LightSensor.h"


    /*
    * Checks the raw data gathered from the light sensor through the STM32 module. 
    * It garantuees that the value returned is between 4095 and 0.
    *
    * @lightData is the raw data received from the light sensor
    *
    * @return is the checked light data.
    */
    float checkRawLightData(unsigned int lightData){
        
        
        
			if(4095 < lightData)
            return 4095;
        else
            return lightData;
    }

    /*
    * Sets the raw data received from the Light sensor of the STM32 module to a value between 100 and 0.
    *
    * @lightData is the raw data received from the light sensor and should be between 4095 and 0.
    *
    * @return is the updated light data.
    */
    float setLightData(unsigned int lightData){
        
         return 100 - roundf(checkRawLightData(lightData)/40.95);
    }
