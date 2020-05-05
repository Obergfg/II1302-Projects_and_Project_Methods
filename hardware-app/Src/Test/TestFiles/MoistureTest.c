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
  unsigned int input = 0;
  float actual = calculateMoisture(input);
  float expected = 0;
  CuAssertIntEquals(tc, expected, actual);
}
void testCalculateMoistureB(CuTest *tc){
  unsigned int input = 9999;
  float actual = calculateMoisture(input);
  float expected = 1;
  CuAssertIntEquals(tc, expected, actual);
}
void testCalculateMoistureC(CuTest *tc){
  unsigned int input = 819;
  float actual = calculateMoisture(input);
  float expected = 0.2;
  CuAssertIntEquals(tc, expected, actual);
}
void testCalculateMoistureD(CuTest *tc){
  unsigned int input = -999;
  float actual = calculateMoisture(input);
  float expected = 0;
  CuAssertIntEquals(tc, expected, actual);
}
void testCalculateMoistureE(CuTest *tc){
  unsigned int input = 4095;
  float actual = calculateMoisture(input);
  float expected = 1;
  CuAssertIntEquals(tc, expected, actual);
}

/*
* Unit tests to the function setMoistureThreshhold
*
* @tc is a pointer to the suite the test is added
*     to according to the framwork CuTest convention.
*/
void testSetMoistureThreshholdA(CuTest *tc){
  float input = 0;
  setMoistureThreshhold(input);
  float actual = getMoistureThreshhold();
  float expected = 0;
  CuAssertIntEquals(tc, expected, actual);
}
void testSetMoistureThreshholdB(CuTest *tc){
  float input = 1;
  setMoistureThreshhold(input);
  float actual = getMoistureThreshhold();
  float expected = 1;
  CuAssertIntEquals(tc, expected, actual);
}
void testSetMoistureThreshholdC(CuTest *tc){
  float input = 0.5;
  setMoistureThreshhold(input);
  float actual = getMoistureThreshhold();
  float expected = 0.5;
  CuAssertIntEquals(tc, expected, actual);
}
void testSetMoistureThreshholdD(CuTest *tc){
  float input = -1;
  setMoistureThreshhold(input);
  float actual = getMoistureThreshhold();
  float expected = 0;
  CuAssertIntEquals(tc, expected, actual);
}
void testSetMoistureThreshholdE(CuTest *tc){
  float input = 2;
  setMoistureThreshhold(input);
  float actual = getMoistureThreshhold();
  float expected = 1;
  CuAssertIntEquals(tc, expected, actual);
}
/*
* Unit tests to the function setDraughtThreshhold
*
* @tc is a pointer to the suite the test is added
*     to according to the framwork CuTest convention.
*/
void setDraughtThreshholdA(CuTest *tc){
  float input = 0;
  setMoistureThreshhold(input);
  float actual = getMoistureThreshhold();
  float expected = 0;
  CuAssertIntEquals(tc, expected, actual);
}
void setDraughtThreshholdB(CuTest *tc){
  float input = 1;
  setMoistureThreshhold(input);
  float actual = getMoistureThreshhold();
  float expected = 1;
  CuAssertIntEquals(tc, expected, actual);
}
void setDraughtThreshholdC(CuTest *tc){
  float input = 0.5;
  setMoistureThreshhold(input);
  float actual = getMoistureThreshhold();
  float expected = 0.5;
  CuAssertIntEquals(tc, expected, actual);
}
void setDraughtThreshholdD(CuTest *tc){
  float input = -1;
  setMoistureThreshhold(input);
  float actual = getMoistureThreshhold();
  float expected = 0;
  CuAssertIntEquals(tc, expected, actual);
}
void setDraughtThreshholdE(CuTest *tc){
  float input = 2;
  setMoistureThreshhold(input);
  float actual = getMoistureThreshhold();
  float expected = 1;
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
