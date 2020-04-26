#   
#  Author: Fredrik Öberg
#  Co-Authors: -
#
#  Date of generation: 200426
#
#  Date of  update: -
#
#  Code Properties: The code represents a Makefile which purpose 
#  is to create a unit test program for The Farm project hardware code.
#
#


## Variables

# The gcc flags used for the compilation of the object files
CFLAGS = -Wall -g -c

# The paths to the sensor source files and test files.
SENSORSPATH =  ../Sensors
TESTFILESPATH = TestFiles

#The path to the header files needed when compiling the sensor files as well as the gcc include option command.
SENSORINCLUDES = -I$(SENSORSPATH)/Include

#The path to the header files needed when compiling the test files as well as the gcc include option command.
TESTFILESINCLUDE = -I$(TESTFILESPATH)/Include $(SENSORINCLUDES)

# The paths to the the header files needed for UnitTests.c
UNITTESTS = -IInclude $(SENSORINCLUDES) $(TESTFILESINCLUDE)

# All the object files needed for the unit test executiion.
OBJECTS = UnitTests.o CuTest.o LightSensor.o LightSensorTest.o



## Paths

# The paths to the source files needed in the prerequisites.
vpath %.c $(SENSORSPATH):TestFiles



## Rules

# The rules of the makefile which has the following shapes:
#
# target … : prerequisites …
#         recipe
#         …
#         …

#The default Rule  which outputs the test.exe file
all: $(OBJECTS)
	gcc $(OBJECTS) -o test

#The main Unit Test file rule. 
UnitTests.o:
	gcc $(UNITTESTS) $(CFLAGS) UnitTests.c

#The CuTest unit test framework rule.
CuTest.o:
	gcc $(CUTEST) $(CFLAGS) $(TESTFILESPATH)/CuTest.c

#The rules for the sensor source code files being tested	
LightSensor.o:
	gcc $(SENSORINCLUDES) $(CFLAGS) $(SENSORSPATH)/LightSensor.c

#The rules for the test files for the sensor source codes.
LightSensorTest.o:
	gcc $(TESTFILESINCLUDE) $(CFLAGS) $(TESTFILESPATH)/LightSensorTest.c
	
# When the test has been executed type "make clean" in your command 
# line of choice to remove the object files as well as the created exe file.
clean:
	del test.exe *.o

