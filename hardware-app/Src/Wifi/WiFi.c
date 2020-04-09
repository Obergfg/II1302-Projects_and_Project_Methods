/**
 *Author: Author Name
 *Co-Authors: Co-Author1 Name, Co-Author2 Name
 *Date of generation: YYMMDD
 *Date of  update: YYMMDD
 *Code Properties: The properties of the code...
*/

/*
 Commands:
"AT+RESTORE" Restores the factory default settings of the module
"AT+CWMODE_DEF" Sets the default Wi-Fi mode (Station/AP/Station+AP); configuration saved in the flash.
"AT+GMR" Checks Version Information
"AT+CWLAP" Wifi info (find APs)
"AT+CWJAP=”SSID”,”PASSWORD”" Connect to Wi-Fi
"AT+CIFSR" Shows IP and MAC of component
*/
uint8_t ATReset[] = "AT+RST\r\n";
uint8_t ATConnectionSetting[] = "AT+CWMODE=1\r\n";
uint8_t ATConnectWifi[] = ATCWJAP;
uint8_t ATPingGoogle[] = "AT+PING=\"8.8.8.8\"\r\n";

uint8_t ATResetResponse[50];
uint8_t ATConnectionSettingResponse[50];
uint8_t ATConnectWifiResponse[500];
uint8_t ATPingGoogleResponse[50];
uint8_t errorMessage[300];

/*
  Test function used to test that functions work propetly.

  @return an integer to signalize which test that failed. returns 0 if all tests were successful.
*/
int setupWifi(){
	HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin); //Turn on green pin
	if(HAL_UART_Transmit(&huart2, ATReset, sizeof(ATReset), 1000) == HAL_OK){
		if(HAL_UART_Transmit(&huart2, ATConnectionSetting, sizeof(ATConnectionSetting), 1000) == HAL_OK){
			if(HAL_UART_Transmit(&huart2, ATConnectWifi, sizeof(ATConnectWifi), 1000) == HAL_OK){
				if(HAL_UART_Transmit(&huart2, ATPingGoogle, sizeof(ATPingGoogle), 1000) == HAL_OK){
					HAL_UART_Receive(&huart2, ATPingGoogleResponse, sizeof(ATPingGoogleResponse), 1000);
					HAL_GPIO_TogglePin(LD3_GPIO_Port, LD4_Pin); //Turn on blue pin
					HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
					return 1; //success
				} //Temp comment
				else{
					HAL_UART_Receive(&huart2, errorMessage, sizeof(errorMessage[300]), 1000);
				}
			}
			else{
				HAL_UART_Receive(&huart2, errorMessage, sizeof(errorMessage[300]), 1000);
			}
		}
		else{
			HAL_UART_Receive(&huart2, errorMessage, sizeof(errorMessage[300]), 1000);
		}
	}
	else{
		HAL_UART_Receive(&huart2, errorMessage, sizeof(errorMessage[300]), 1000);
	}

	HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin); //Turn off green pin
	return 0; //fail
}

int wifiTest(){
	return 0;
}



