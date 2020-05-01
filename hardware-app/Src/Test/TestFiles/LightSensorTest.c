/**
 *Author: Fredrik Öberg
 *Co-Authors: -
 *Date of generation: 200426
 *Date of  update: -
 *Code Properties: The code serves as unit tests for the functions 
                   in the file LightSensor.c and it tests that functions 
                   operates as espected given a varied amount of data 
                   from small negative values to large1 positive.
*/

#include <assert.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
   
#include "CuTest.h"
#include "LightSensor.h"
#include "LightSensorTest.h"
  
    
    /*
    * Unit tests to the function checkRawLightData 
    *
    * @tc is a pointer to the suite the test is added 
    *     to according to the framwork CuTest convention.
    */
    void testCheckRawLightDataA(CuTest *tc) {
        int input = 100000;
        int actual = checkRawLightData(input);
        int expected = 4095;
        CuAssertIntEquals(tc, expected, actual);
    }

    void testCheckRawLightDataB(CuTest *tc) {
        int input = 4095;
        int actual = checkRawLightData(input);
        int expected = 4095;
        CuAssertIntEquals(tc, expected, actual);
    }

    void testCheckRawLightDataC(CuTest *tc) {
        int input = 10;
        int actual = checkRawLightData(input);
        int expected = 10;
        CuAssertIntEquals(tc, expected, actual);
    }

    void testCheckRawLightDataD(CuTest *tc) {
        int input = 0;
        int actual = checkRawLightData(input);
        int expected = 0;
        CuAssertIntEquals(tc, expected, actual);
    }

    void testCheckRawLightDataE(CuTest *tc) {
        int input = -1;
        int actual = checkRawLightData(input);
        int expected = 4095;
        CuAssertIntEquals(tc, expected, actual);
    }

    void testCheckRawLightDataF(CuTest *tc) {
        int input = -99999;
        int actual = checkRawLightData(input);
        int expected = 4095;
        CuAssertIntEquals(tc, expected, actual);
    }

    void testCheckRawLightDataG(CuTest *tc) {
        int input = 2147483647;
        int actual = checkRawLightData(input);
        int expected = 4095;
        CuAssertIntEquals(tc, expected, actual);
    }

    void testCheckRawLightDataH(CuTest *tc) {
        int input = -2147483648;
        int actual = checkRawLightData(input);
        int expected = 4095;
        CuAssertIntEquals(tc, expected, actual);
    }


    /*
    * Unit tests to the function setLightData. 
    *
    * @tc is a pointer to the suite the test is added to according to the framwork CuTest convention.
    */
    void testSetLightDataA(CuTest *tc) {
        int input = 4095;
        int actual = setLightData(input);
        int expected = 0;
        CuAssertIntEquals(tc, expected, actual);
    }

    void testSetLightDataB(CuTest *tc) {
        int input = 4000;
        int actual = setLightData(input);
        int expected = 2;
        CuAssertIntEquals(tc, expected, actual);
    }

    void testSetLightDataC(CuTest *tc) {
        int input = 100;
        int actual = setLightData(input);
        int expected = 98;
        CuAssertIntEquals(tc, expected, actual);
    }

    void testSetLightDataD(CuTest *tc) {
        int input = 0;
        int actual = setLightData(input);
        int expected = 100;
        CuAssertIntEquals(tc, expected, actual);
    }

    void testSetLightDataE(CuTest *tc) {
        int input = -99999;
        int actual = setLightData(input);
        int expected = 0;
        CuAssertIntEquals(tc, expected, actual);
    }

    void testSetLightDataF(CuTest *tc) {
        int input = -1;
        int actual = setLightData(input);
        int expected = 0;
        CuAssertIntEquals(tc, expected, actual);
    }

    void testSetLightDataG(CuTest *tc) {
        int input = 2048;
        int actual = setLightData(input);
        int expected = 50;
        CuAssertIntEquals(tc, expected, actual);
    }
    
    void testSetLightDataH(CuTest *tc) {
        int input = 2147483647;
        int actual = setLightData(input);
        int expected = 0;
        CuAssertIntEquals(tc, expected, actual);
    }

    void testSetLightDataI(CuTest *tc) {
        int input = -2147483648;
        int actual = setLightData(input);  
        int expected = 0;
        CuAssertIntEquals(tc, expected, actual);
    }


    /*
    * Collects the testfunctions of this files and adds them to a common testing suite.
    *
    * @return is the suite containing all the tests of this file.
    */
    CuSuite* lightSensorGetSuite() {
        CuSuite* suite = CuSuiteNew();

        SUITE_ADD_TEST(suite, testCheckRawLightDataA);
        SUITE_ADD_TEST(suite, testCheckRawLightDataB);
        SUITE_ADD_TEST(suite, testCheckRawLightDataC);
        SUITE_ADD_TEST(suite, testCheckRawLightDataD);
        SUITE_ADD_TEST(suite, testCheckRawLightDataE);
        SUITE_ADD_TEST(suite, testCheckRawLightDataF);
        SUITE_ADD_TEST(suite, testCheckRawLightDataG);
        SUITE_ADD_TEST(suite, testCheckRawLightDataH);
        SUITE_ADD_TEST(suite, testSetLightDataA);
        SUITE_ADD_TEST(suite, testSetLightDataB);
        SUITE_ADD_TEST(suite, testSetLightDataC);
        SUITE_ADD_TEST(suite, testSetLightDataD);
        SUITE_ADD_TEST(suite, testSetLightDataE);
        SUITE_ADD_TEST(suite, testSetLightDataF);
        SUITE_ADD_TEST(suite, testSetLightDataG);
        SUITE_ADD_TEST(suite, testSetLightDataH);
        SUITE_ADD_TEST(suite, testSetLightDataI);

        return suite;
    }
