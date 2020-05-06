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
uint8_t ATReset[] = "AT+RESTORE\r\n";
uint8_t ATConnectionSetting[] = "AT+CWMODE=1\r\n";
uint8_t ATConnectWifi[] = ATCWJAP; //wifi username and password, stored in private.c
uint8_t ATLocalIP[] = "AT+CIFSR\r\n";
uint8_t ATPingGoogle[] = "AT+PING=\"8.8.8.8\"\r\n";

//uint8_t ATResetResponse[50];
//uint8_t ATConnectionSettingResponse[50];
//uint8_t ATConnectWifiResponse[500];
//uint8_t ATPingGoogleResponse[300];
uint8_t errorMessage[750];

/*
  Test function used to test that functions work propetly.

  @return an integer to signalize which test that failed. returns 0 if all tests were successful.
*/
int setupWifi(){
	HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin); //Turn on green pin
	if(HAL_UART_Transmit(&huart2, ATReset, sizeof(ATReset), 1000) == HAL_OK){
		//HAL_UART_Receive(&huart2, errorMessage, sizeof(errorMessage), 1000);
		if(HAL_UART_Transmit(&huart2, ATConnectionSetting, sizeof(ATConnectionSetting), 1000) == HAL_OK){
			if(HAL_UART_Transmit(&huart2, ATConnectWifi, sizeof(ATConnectWifi), 1000) == HAL_OK){
				//HAL_UART_Receive(&huart2, ATConnectWifiResponse, sizeof(ATConnectWifiResponse), 1000);
				if(HAL_UART_Transmit(&huart2, ATLocalIP, sizeof(ATLocalIP), 1000) == HAL_OK){
					if(HAL_UART_Transmit(&huart2, ATPingGoogle, sizeof(ATPingGoogle), 1000) == HAL_OK){
						//HAL_UART_Receive(&huart2, ATPingGoogleResponse, sizeof(ATPingGoogleResponse), 1000);
						//HAL_GPIO_TogglePin(LD3_GPIO_Port, LD4_Pin); //Turn on blue pin
						HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
						//HAL_UART_Receive(&huart2, errorMessage, sizeof(errorMessage), 1000);
						return 1; //success
					} //Temp comment
				}
			}
		}
	}
	//HAL_UART_Receive(&huart2, errorMessage, sizeof(errorMessage), 1000);


	HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin); //Turn off green pin
	return 0; //fail
}

int wifiTest(){
	return 0;
}



