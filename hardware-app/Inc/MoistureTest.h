/**
 *Author: Max Ryblad
 *Co-Authors: -
 *Date of generation: 20/05/04
 *Date of  update: -
 *Code Properties: The code serves as a header file for the MoistureTest.c file and contains
 *                 declarations of functions and variables.
 */


#ifndef MOISTURESENSORTEST_H
#define MOISTURESENSORTEST_H

  void testCalculateMoistureA(CuTest *tc);
  void testCalculateMoistureB(CuTest *tc);
  void testCalculateMoistureC(CuTest *tc);
  void testCalculateMoistureD(CuTest *tc);
  void testCalculateMoistureE(CuTest *tc);

  void testSetMoistureThreshholdA(CuTest *tc);
  void testSetMoistureThreshholdB(CuTest *tc);
  void testSetMoistureThreshholdC(CuTest *tc);
  void testSetMoistureThreshholdD(CuTest *tc);
  void testSetMoistureThreshholdE(CuTest *tc);

  void setDraughtThreshholdA(CuTest *tc);
  void setDraughtThreshholdB(CuTest *tc);
  void setDraughtThreshholdC(CuTest *tc);
  void setDraughtThreshholdD(CuTest *tc);
  void setDraughtThreshholdE(CuTest *tc);

  CuSuite* moistureGetSuite(void);

#endif
