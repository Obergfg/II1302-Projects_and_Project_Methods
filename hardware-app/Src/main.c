/* Includes */
#include "main.h"
#include "private.c"
#include "Util/GeneralSensorFunctions.c"
#include "Util/MXFunctions.c"
#include "WiFi/WiFi.c"

void initialize(){
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  /* Configure the system clock */
  SystemClock_Config();
  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC_Init();
  MX_USART2_UART_Init();
	updateADCSensors();
}



/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	initialize();
 
	setupWifi();

  /* Infinite loop */
  while (1)
  {
		HAL_Delay(1000);
		updateADCSensors(); //Check ADC pins
  }
}
