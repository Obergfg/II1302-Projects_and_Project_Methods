  /**
 *Author: Fredrik Öberg

 *Co-Authors: Max Ryblad

 *Date of generation: 200425

 *Date of  update: 200506

 *Code Properties: The code contains the main function of the unit testing 
 *                 procedure of "The Farm" project. It initializes the unit 
 *                 tests and ouputs the testresults.
*/

  #include <stdio.h>

  #include "UnitTests.h"
  #include "CuTest.h"
  #include "LightSensorTest.h"
  #include "MoistureTest.h"

    
    /*
    * Initiates the unit testing process.
    */
    void initiateUnitTests(void) {
        CuString *output = CuStringNew();
        CuSuite* testSuite = CuSuiteNew();
        
        CuSuiteAddSuite(testSuite, lightSensorGetSuite());
         CuSuiteAddSuite(testSuite, moistureGetSuite());
    
        CuSuiteRun(testSuite);
        CuSuiteSummary(testSuite, output);
        CuSuiteDetails(testSuite, output);
        printf("%s\n", output->buffer);
    }
    
    /*
    * Is the main function of this program and is called upon when executing. 
    *
    * @return is is 0 when the program has executed correctly.
    */
    int main(void) {

       initiateUnitTests();

       return 0;
    }

