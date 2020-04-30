/* Includes */
//#include "curl/curl.h"

/**
 *Author: Author Name
 *Co-Authors: Co-Author1 Name, Co-Author2 Name
 *Date of generation: YYMMDD
 *Date of  update: YYMMDD
 *Code Properties: The properties of the code...
*/

/*
void test(){
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
		curl_easy_setopt(curl, CURLOPT_URL, "https://farmtesting-cbe6a.firebaseio.com/light.json");
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
		struct curl_slist *headers = NULL;
		headers = curl_slist_append(headers, "Content-Type: text/plain");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		const char *data = "124124124";
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
		res = curl_easy_perform(curl);
	}
	curl_easy_cleanup(curl);
}
*/
/*
POST /light.json HTTP/1.1
Host: farmtesting-cbe6a.firebaseio.com
Content-Type: text/plain

420
*/

/*
GET / HTTP/1.1
Host: 92.35.98.102:25565



*/

uint8_t ATLocalTest0[] = "AT+CIPMUX=0\r\n";
uint8_t ATLocalTest1[] = "AT+CIPSTART=\"TCP\",\"http://92.35.98.102\",\"25565\"\r\n";
uint8_t ATLocalTest2[] = "AT+CIPSEND=63\r\n";
uint8_t ATLocalTest3[] = "GET / HTTP/1.1\r\nHost: 92.35.98.102:25565\r\n\r\n";
uint8_t ATLocalTest4[] = "AT+CIPCLOSE\r\n\r\n";

uint8_t ATFirebaseTest0[] = "AT+CIPMUX=0\r\n";
uint8_t ATFirebaseTest1[] = "AT+CIPSTART=\"TCP\",\"farmtesting-cbe6a.firebaseio.com\",80\r\n";
uint8_t ATFirebaseTest2[] = "AT+CIPSEND=100\r\n";
//uint8_t ATFirebaseTest3[] = "test\r\n";
//uint8_t ATFirebaseTest3[] = "POST /IoT.json HTTP/1.1\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: 3\r\n\r\n420\r\n\r\n";
uint8_t ATFirebaseTest3[] = "POST /IoT.json HTTP/1.1\r\nHost: farmtesting-cbe6a.firebaseio.com\r\nContent-Type: text/plain\r\n\r\n420\r\n\r\n\r\n";
uint8_t ATFirebaseTest4[] = "AT+CIPCLOSE\r\n\r\n";

uint8_t responseMsg[1000];

int curlTest = 0;
HAL_StatusTypeDef response1 = 69;
HAL_StatusTypeDef response2 = 69;

void localTest(){
	if(HAL_UART_Transmit(&huart2, ATLocalTest0, sizeof(ATLocalTest0), 1000) == HAL_OK){
		//HAL_Delay(500);
		/*
		curlTest = curlTest + 1;
		if(HAL_UART_Transmit(&huart2, ATLocalTest1, sizeof(ATLocalTest1), 1000) == HAL_OK){
			//HAL_Delay(500);
			curlTest = curlTest + 1;
			if(HAL_UART_Transmit(&huart2, ATLocalTest2, sizeof(ATLocalTest2), 1000) == HAL_OK){
				//HAL_Delay(500);
				curlTest = curlTest + 1;
				if(HAL_UART_Transmit(&huart2, ATLocalTest3, sizeof(ATLocalTest3), 1000) == HAL_OK){
					//HAL_Delay(500);
					curlTest = curlTest + 1;
					if(HAL_UART_Transmit(&huart2, ATLocalTest4, sizeof(ATLocalTest4), 1000) == HAL_OK){
						curlTest = curlTest + 1;
						HAL_GPIO_TogglePin(LD3_GPIO_Port, LD4_Pin); //Turn on blue pin
					}
				}
			}
		}*/
		HAL_UART_Receive(&huart2, responseMsg, sizeof(responseMsg), 1000);
	}
	HAL_UART_Receive(&huart2, errorMessage, sizeof(errorMessage), 1000);
}

void firebastTest(){
	if(HAL_UART_Transmit(&huart2, ATFirebaseTest0, sizeof(ATFirebaseTest0), 1000) == HAL_OK){
		curlTest = curlTest + 1;
		if(HAL_UART_Transmit(&huart2, ATFirebaseTest1, sizeof(ATFirebaseTest1), 1000) == HAL_OK){
			curlTest = curlTest + 1;
			//HAL_UART_Receive(&huart2, responseMsg, sizeof(responseMsg[500]), 1000);
			//HAL_Delay(500);
			if(HAL_UART_Transmit(&huart2, ATFirebaseTest2, sizeof(ATFirebaseTest2), 1000) == HAL_OK){
				curlTest = curlTest + 1;
				//HAL_UART_Receive(&huart2, responseMsg, sizeof(responseMsg[500]), 1000);
				//HAL_Delay(500);
				if(HAL_UART_Transmit(&huart2, ATFirebaseTest3, sizeof(ATFirebaseTest3), 1000) == HAL_OK){
					curlTest = curlTest + 1;
					//HAL_UART_Receive(&huart2, responseMsg, sizeof(responseMsg[500]), 1000);
					//HAL_Delay(500);
					if(HAL_UART_Transmit(&huart2, ATFirebaseTest4, sizeof(ATFirebaseTest4), 1000) == HAL_OK){
						curlTest = curlTest + 1;
						HAL_GPIO_TogglePin(LD3_GPIO_Port, LD4_Pin); //Turn on blue pin
					}
				}
			}
		}
	}
	HAL_UART_Receive(&huart2, responseMsg, sizeof(responseMsg), 1000);
}

void testSend(){
	firebastTest();
	//HAL_UART_Transmit(&huart2, ATLocalTest0, sizeof(ATLocalTest0), 1000);
	//HAL_Delay(500);
	//HAL_UART_Transmit(&huart2, "AT+CIPSTATUS", 12, 1000);
	//HAL_Delay(500);
	//HAL_UART_Receive(&huart2, errorMessage, sizeof(errorMessage), 1000);
}

