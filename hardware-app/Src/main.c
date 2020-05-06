/* Includes */
#include "main.h"
#include "private.c"
#include "Util/GeneralSensorFunctions.c"
#include "Util/MXFunctions.c"
#include "WiFi/WiFi.c"
#include "WiFi/Curl.c"
#include "string.h"
#include <stdio.h>


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

uint8_t helloWorld[13] = "Hello World\r\n";

uint8_t wifiTesting[750];
//uint8_t wifiCommand[] = "AT+CIPSTART=\"TCP\",\"farmtesting-cbe6a.firebaseio.com\",\"80\"\r\n";
//uint8_t wifiCommand[] = "AT+CIPSTART=\"TCP\",\"92.35.98.102\",\"25565\"\r\n";
//uint8_t wifiCommand[] = "AT+CIPMUX=0\r\n";
//uint8_t wifiCommand2[] = "AT+CIPSTART=\"SSL\",\"farmtesting-cbe6a.firebaseio.com\",\"443\"\r\n";
//uint8_t wifiCommand3[] = "AT+CIPSENDEX=100\r\n";
//uint8_t wifiCommand4[] = "POST /IoT.json HTTP/1.1\r\nHost: farmtesting-cbe6a.firebaseio.com\r\nContent-Type: text/plain\r\n\r\n420\r\n\r\n\r\n";
//uint8_t wifiCommand5[] = "AT+CIPCLOSE\r\n\r\n";


uint8_t wifiCommand[] = "AT+CIPMUX=0\r\n";
uint8_t wifiCommand2[] = "AT+CIPSTART=\"TCP\",\"google.com\",80\r\n";
uint8_t wifiCommand3[] = "AT+CIPSEND=18\r\n"; //was 18
uint8_t wifiCommand4[] = "GET / HTTP/1.1\r\n\r\n";//Host: google.com\r\n\r\n";
uint8_t wifiCommand5[] = "AT+CIPCLOSE\r\n\r\n";

/*
uint8_t FirebaseTest0[] = "AT+CIPMUX=0\r\n";
uint8_t FirebaseTest1[] = "AT+CIPSTART=\"TCP\",\"https://farmtesting-cbe6a.firebaseio.com\",80\r\n";
uint8_t FirebaseTest2[] = "AT+CIPSEND=68\r\n"; //Was 100 eller 118 eller 18
uint8_t FirebaseTest3[] = "GET /light.json HTTP/1.1\r\nHost: farmtesting-cbe6a.firebaseio.com\r\n\r\n";
//uint8_t FirebaseTest3[] = "POST /IoT.json HTTP/1.1\r\nHost: farmtesting-cbe6a.firebaseio.com\r\nContent-Type: text/plain\r\nContent-Length: 3\r\n\r\n420\r\n\r\n";
uint8_t FirebaseTest4[] = "AT+CIPCLOSE\r\n\r\n";
*/

uint8_t FirebaseTest00[] = "AT+CIPSSLSIZE=4096\r\n";
uint8_t FirebaseTest0[] = "AT+CIPMUX=0\r\n";
uint8_t FirebaseTest1[] = "AT+CIPSTART=\"SSL\",\"farmtesting-cbe6a.firebaseio.com\",443\r\n";
uint8_t FirebaseTest2[] = "AT+CIPSEND=256\r\n"; //Was 121
uint8_t FirebaseTest3[] = "POST /IoT.json HTTP/1.1\r\nHost: farmtesting-cbe6a.firebaseio.com\r\nContent-Type: text/plain\r\nContent-Length: 3\r\n\r\n123\r\n\r\n\r\n";
//uint8_t FirebaseTest3[] = "POST /IoT.json HTTP/1.1\r\nHost: farmtesting-cbe6a.firebaseio.com\r\nContent-Type: text/plain\r\nContent-Length: 3\r\n\r\n420\r\n\r\n";
uint8_t FirebaseTest4[] = "AT+CIPCLOSE\r\n\r\n";

/*
uint8_t sendBuffer[bufferAmount][122] = {
	"AT+CIPSSLSIZE=4096\r\n",
	"AT+CIPMUX=0\r\n",
	"AT+CIPSTART=\"SSL\",\"farmtesting-cbe6a.firebaseio.com\",443\r\n",
	"AT+CIPSEND=256\r\n", //Updates later
	"POST /IoT.json HTTP/1.1\r\nHost: farmtesting-cbe6a.firebaseio.com\r\nContent-Type: text/plain\r\nContent-Length: 3\r\n\r\n123\r\n\r\n\r\n",
	"AT+CIPCLOSE\r\n\r\n"
};
*/


uint8_t sendCommand0[] = "AT+CIPSSLSIZE=4096\r\n";
uint8_t sendCommand1[] = "AT+CIPMUX=0\r\n";
uint8_t sendCommand2[] = "AT+CIPSTART=\"SSL\",\"projekt-och-projektmetoder.firebaseio.com\",443\r\n";
uint8_t sendCommand3[] = "AT+CIPSEND=256\r\n";
uint8_t sendCommand4[] = "POST /Max.json HTTP/1.1\r\nHost: projekt-och-projektmetoder.firebaseio.com\r\nContent-Type: text/plain\r\nContent-Length: 3\r\n\r\n998\r\n\r\n\r\n";
uint8_t sendCommand5[] = "AT+CIPCLOSE\r\n\r\n";

uint8_t * sendBuffer[] = {sendCommand0, sendCommand1, sendCommand2, sendCommand3, sendCommand4, sendCommand5};
//uint8_t sendBuffer[6][2] = {"AT","AL","AT","AT","AT","AT"};



const int bufferAmount = 6;

uint8_t receiveBuffer0[100];
uint8_t receiveBuffer1[100];
uint8_t receiveBuffer2[100];
uint8_t receiveBuffer3[100];
uint8_t receiveBuffer4[100];
uint8_t receiveBuffer5[100];

uint8_t * receiveBuffer[] = {receiveBuffer0, receiveBuffer1, receiveBuffer2, receiveBuffer3, receiveBuffer4, receiveBuffer5};

//uint8_t receiveBuffer[bufferAmount][100];

void updateCIPSEND(){
  sprintf((char*)sendBuffer[3], "AT+CIPSEND=%d\r\n", sizeof(sendBuffer[4]));
}

void testSendBuffer(){
	for(int i = 0; i < bufferAmount; i++){
		if(HAL_UART_Transmit(&huart2, sendBuffer[i], sizeof(sendBuffer[i]), 1000) == HAL_OK){
			HAL_UART_Receive(&huart2, receiveBuffer[i], sizeof(receiveBuffer[i]), 1000);
		}
	}



/*
if(HAL_UART_Transmit(&huart2, sendCommand0, sizeof(sendCommand0), 1000) == HAL_OK){
		HAL_UART_Receive(&huart2, receiveBuffer[0], sizeof(receiveBuffer[0]), 1000);
		if(HAL_UART_Transmit(&huart2, sendCommand1, sizeof(sendCommand1), 1000) == HAL_OK){
			HAL_UART_Receive(&huart2, receiveBuffer[1], sizeof(receiveBuffer[1]), 1000);
			if(HAL_UART_Transmit(&huart2, sendCommand2, sizeof(sendCommand2), 1000) == HAL_OK){
				HAL_UART_Receive(&huart2, receiveBuffer[2], sizeof(receiveBuffer[2]), 1000);
				if(HAL_UART_Transmit(&huart2, sendCommand3, sizeof(sendCommand3), 1000) == HAL_OK){
					HAL_UART_Receive(&huart2, receiveBuffer[3], sizeof(receiveBuffer[3]), 1000);
					if(HAL_UART_Transmit(&huart2, sendCommand4, sizeof(sendCommand4), 1000) == HAL_OK){
						HAL_UART_Receive(&huart2, receiveBuffer[4], sizeof(receiveBuffer[4]), 1000);
						if(HAL_UART_Transmit(&huart2, sendCommand5, sizeof(sendCommand5), 1000) == HAL_OK){
							HAL_UART_Receive(&huart2, receiveBuffer[5], sizeof(receiveBuffer[5]), 1000);
						}
					}
				}
			}
		}
	}
	*/
}

/*
uint8_t mux[] = "AT+CIPMUX=0\r\n";
uint8_t start[] = "AT+CIPSTART="SSL","projekt-och-projektmetoder.firebaseio.com",443\r\n";
uint8_t send[] = "AT+CIPSEND=256\r\n";
uint8_t post[] = "POST /IoT.json HTTP/1.1\r\nHost: projekt-och-projektmetoder.firebaseio.com\r\nContent-Type: text/plain\r\nContent-Length: 3\r\n\r\n123\r\n\r\n\r\n";
uint8_t close[] = "AT+CIPCLOSE\r\n\r\n";
*/

/*
IBM IOT broker

Curl kommando, vanligt ramverk för t.ex biluppdateringar

Wireshark för att sniffa

Simulerad IoT data från dator att jobba med. Linus har exempel med IoT broker.

Grupp 7,8 TIEDB

Flytta våran lucid chart till delad mapp.

Jobba mot usecase

Flaggor för testning på "Projekt arkitekturen"
Test-case kopplas ihop med use-case
*/
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	initialize();
	
	//firebastTest();
	
	setupWifi();
	//updateCIPSEND();
	testSendBuffer();
	
<<<<<<< HEAD
=======
	
>>>>>>> parent of 468a9ae... Added test code to get MAC address.
	/*
	if(HAL_UART_Transmit(&huart2, (uint8_t*)"AT+CIFSR\r\n", 10, 1000) == HAL_OK){
		HAL_UART_Receive(&huart2, wifiTesting, sizeof(wifiTesting), 1000);
	}
<<<<<<< HEAD
	int save = 0;
	int startCounter = -1;
	int indexCounter = 0;
	for(int i = 0; i < 100; i++){
		if(wifiTesting[i] == 'M'){
			startCounter = 5;
			save = 1;
		}
		else{
			startCounter--;
		}
		if(save == 1 && startCounter <= 0){
			MAC[indexCounter] = wifiTesting[i];
			indexCounter++;
		}
		if(indexCounter >= 17){
			break;
		}
	}
=======
>>>>>>> parent of 468a9ae... Added test code to get MAC address.
	*/
	
	/*
	if(HAL_UART_Transmit(&huart2, wifiCommand, sizeof(wifiCommand), 1000) == HAL_OK){
		if(HAL_UART_Transmit(&huart2, wifiCommand2, sizeof(wifiCommand2), 1000) == HAL_OK){
			if(HAL_UART_Transmit(&huart2, wifiCommand3, sizeof(wifiCommand3), 1000) == HAL_OK){
				if(HAL_UART_Transmit(&huart2, wifiCommand4, sizeof(wifiCommand4), 1000) == HAL_OK){
					HAL_UART_Transmit(&huart2, wifiCommand5, sizeof(wifiCommand5), 1000);
					HAL_UART_Receive(&huart2, wifiTesting, sizeof(wifiTesting), 1000);
				}
			}
		}
	}
	*/
	
	/*
	if(HAL_UART_Transmit(&huart2, FirebaseTest00, sizeof(FirebaseTest00), 1000) == HAL_OK){
		if(HAL_UART_Transmit(&huart2, FirebaseTest0, sizeof(FirebaseTest0), 1000) == HAL_OK){
			if(HAL_UART_Transmit(&huart2, FirebaseTest1, sizeof(FirebaseTest1), 1000) == HAL_OK){
				//if(HAL_UART_Transmit(&huart2, sendBuffer, sizeof(sendBuffer), 1000) == HAL_OK){
					//if(HAL_UART_Transmit(&huart2, FirebaseTest3, sizeof(FirebaseTest3), 1000) == HAL_OK){
						//HAL_UART_Transmit(&huart2, FirebaseTest4, sizeof(FirebaseTest4), 1000);
						HAL_UART_Receive(&huart2, wifiTesting, sizeof(wifiTesting), 1000);
					//}
				//}
			}
		}
	}
	*/
	
	
	//Ping google
	//HAL_UART_Transmit(&huart2, ATPingGoogle, sizeof(ATPingGoogle), 1000);
	//HAL_UART_Receive(&huart2, wifiTesting, sizeof(wifiTesting), 1000);
	

	
	//if(setupWifi() == 1){
	//	testSend();
	//}
	

  /* Infinite loop */
	/*
  while (1)
  {
		//HAL_UART_Transmit(&huart2, helloWorld, 13, 10);
		HAL_Delay(1000);
		updateADCSensors(); //Check ADC pins
  }
	*/
}
