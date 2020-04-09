/**
 *Author: Max
 *Co-Authors:
 *Date of generation: 20/04/03
 *Date of  update: 20/04/03
 *Code Properties: Max's test file to test functions he is working on.
*/

#include <stdio.h>
#include <string.h>

#include "../Sensors/Moisture.c"
#include "../Sensors/Waterpump.c"


void checkTests(){
  int moistureTestValue = moistureTest();
  if(moistureTestValue == 0){
    printf("MoistureTest ran successfully.\n");
  }
  else{
    printf("MoistureTest failed, caseud by test nr: %d\n", moistureTestValue);
  }

  int waterpumpTestValue = waterpumpTest();
  if(waterpumpTestValue == 0){
    printf("WaterpumpTest ran successfully.\n");
  }
  else{
    printf("WaterpumpTest failed, caseud by test nr: %d\n", waterpumpTestValue);
  }
}


void main() {
  //checkTests();
  uint8_t a[6] = "abc";
  uint8_t b[6];
  strcat(a, "cde");
  printf(a);
}
