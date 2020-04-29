/**
 *Author: Fredrik Öberg
 *Co-Authors: -
 *Date of generation: 200426
 *Date of  update: -
 *Code Properties: The code serves as a header file for the LightSensorTest.c file and contains 
 *                 declarations of functions and variables.
 */


#ifndef LIGHTSENSORTEST_H
#define LIGHTSENSORTEST_H

    void testCheckRawLightDataA(CuTest *tc);
    void testCheckRawLightDataB(CuTest *tc);
    void testCheckRawLightDataC(CuTest *tc);
    void testCheckRawLightDataD(CuTest *tc);
    void testCheckRawLightDataE(CuTest *tc);
    void testCheckRawLightDataF(CuTest *tc);
    void testCheckRawLightDataG(CuTest *tc);
    void testCheckRawLightDataH(CuTest *tc);

    void testSetLightDataA(CuTest *tc);
    void testSetLightDataB(CuTest *tc);
    void testSetLightDataC(CuTest *tc);
    void testSetLightDataD(CuTest *tc);
    void testSetLightDataE(CuTest *tc);
    void testSetLightDataF(CuTest *tc);
    void testSetLightDataG(CuTest *tc);
    void testSetLightDataH(CuTest *tc);
    void testSetLightDataI(CuTest *tc);

    CuSuite* lightSensorGetSuite(void);

#endif