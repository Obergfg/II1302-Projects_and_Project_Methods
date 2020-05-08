/*
 *Author: Max Ryblad
 *Co-Authors: -
 *Date of generation: 20-05-03
 *Date of  update: -
 *Code Properties: The code serves as unit tests for the functions
                   in the file Moisture.c and it tests that functions
                   operates as espected given a varied amount of data
                   from small negative values to large1 positive.
*/

#include <assert.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "CuTest.h"
#include "Moisture.h"
#include "MoistureTest.h"

/*
* Unit tests to the function calculateMoisture
*
* @tc is a pointer to the suite the test is added
*     to according to the framwork CuTest convention.
*/
void testCalculateMoistureA(CuTest *tc){
  int input = 0;
  int actual = calculateMoisture(input);
  int expected = 100;
  CuAssertIntEquals(tc, expected, actual);
}
void testCalculateMoistureB(CuTest *tc){
  int input = 4095;
  int actual = calculateMoisture(input);
  int expected = 0;
  CuAssertIntEquals(tc, expected, actual);
}
void testCalculateMoistureC(CuTest *tc){
  int input = 819;
  int actual = calculateMoisture(input);
  int expected = 80;
  CuAssertIntEquals(tc, expected, actual);
}
void testCalculateMoistureD(CuTest *tc){
  int input = -999;
  int actual = calculateMoisture(input);
  int expected = 100;
  CuAssertIntEquals(tc, expected, actual);
}
void testCalculateMoistureE(CuTest *tc){
  int input = 409500;
  int actual = calculateMoisture(input);
  int expected = 0;
  CuAssertIntEquals(tc, expected, actual);
}

/*
* Unit tests to the function setMoistureThreshhold
*
* @tc is a pointer to the suite the test is added
*     to according to the framwork CuTest convention.
*/
void testSetMoistureThreshholdA(CuTest *tc){
  int input = 0;
  setMoistureThreshhold(input);
  int actual = getMoistureThreshhold();
  int expected = 0;
  CuAssertIntEquals(tc, expected, actual);
}
void testSetMoistureThreshholdB(CuTest *tc){
  int input = 100;
  setMoistureThreshhold(input);
  int actual = getMoistureThreshhold();
  int expected = 100;
  CuAssertIntEquals(tc, expected, actual);
}
void testSetMoistureThreshholdC(CuTest *tc){
  int input = 50;
  setMoistureThreshhold(input);
  int actual = getMoistureThreshhold();
  int expected = 50;
  CuAssertIntEquals(tc, expected, actual);
}
void testSetMoistureThreshholdD(CuTest *tc){
  int input1 = 62;
  setMoistureThreshhold(input1);
  int input2 = -10;
  setMoistureThreshhold(input2);
  int actual = getMoistureThreshhold();
  int expected = 62;
  CuAssertIntEquals(tc, expected, actual);
}
void testSetMoistureThreshholdE(CuTest *tc){
  int input1 = 20;
  setMoistureThreshhold(input1);
  int input2 = 2660;
  setMoistureThreshhold(input2);
  int actual = getMoistureThreshhold();
  int expected = 20;
  CuAssertIntEquals(tc, expected, actual);
}
/*
* Unit tests to the function setDraughtThreshhold
*
* @tc is a pointer to the suite the test is added
*     to according to the framwork CuTest convention.
*/
void setDraughtThreshholdA(CuTest *tc){
  int input = 0;
  setMoistureThreshhold(input);
  int actual = getMoistureThreshhold();
  int expected = 0;
  CuAssertIntEquals(tc, expected, actual);
}
void setDraughtThreshholdB(CuTest *tc){
  int input = 100;
  setMoistureThreshhold(input);
  int actual = getMoistureThreshhold();
  int expected = 100;
  CuAssertIntEquals(tc, expected, actual);
}
void setDraughtThreshholdC(CuTest *tc){
  int input = 50;
  setMoistureThreshhold(input);
  int actual = getMoistureThreshhold();
  int expected = 50;
  CuAssertIntEquals(tc, expected, actual);
}
void setDraughtThreshholdD(CuTest *tc){
  int input1 = 12;
  setMoistureThreshhold(input1);
  int input2 = -100;
  setMoistureThreshhold(input2);
  int actual = getMoistureThreshhold();
  int expected = 12;
  CuAssertIntEquals(tc, expected, actual);
}
void setDraughtThreshholdE(CuTest *tc){
  int input1 = 53;
  setMoistureThreshhold(input1);
  int input2 = 200;
  setMoistureThreshhold(input2);
  int actual = getMoistureThreshhold();
  int expected = 53;
  CuAssertIntEquals(tc, expected, actual);
}


/*
* Collects the testfunctions of this files and adds them to a common testing suite.
*
* @return is the suite containgin all the tests of this file.
*/
CuSuite* moistureGetSuite() {
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testCalculateMoistureA);
    SUITE_ADD_TEST(suite, testCalculateMoistureB);
    SUITE_ADD_TEST(suite, testCalculateMoistureC);
    SUITE_ADD_TEST(suite, testCalculateMoistureD);
    SUITE_ADD_TEST(suite, testCalculateMoistureE);

    SUITE_ADD_TEST(suite, setDraughtThreshholdA);
    SUITE_ADD_TEST(suite, setDraughtThreshholdB);
    SUITE_ADD_TEST(suite, setDraughtThreshholdC);
    SUITE_ADD_TEST(suite, setDraughtThreshholdD);
    SUITE_ADD_TEST(suite, setDraughtThreshholdE);

    SUITE_ADD_TEST(suite, testSetMoistureThreshholdA);
    SUITE_ADD_TEST(suite, testSetMoistureThreshholdB);
    SUITE_ADD_TEST(suite, testSetMoistureThreshholdC);
    SUITE_ADD_TEST(suite, testSetMoistureThreshholdD);
    SUITE_ADD_TEST(suite, testSetMoistureThreshholdE);

    return suite;
}
