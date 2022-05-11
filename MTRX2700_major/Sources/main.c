#include <hidef.h>      /* common defines and macros */
#include <assert.h>
#include "derivative.h"      /* derivative-specific definitions */

// need this for string functions
#include <stdio.h>

#include "pll.h"
#include "simple_serial.h"

#include "l3g4200d.h"

#include "servo.h"
#include "laser.h"

#include "functions.h"

unsigned long laserValueArr[10];


void printErrorCode(IIC_ERRORS error_code) {
  char buffer[128];  
  switch (error_code) {
    case NO_ERROR: 
      sprintf(buffer, "IIC: No error\r\n");
      break;
    
    case NO_RESPONSE: 
      sprintf(buffer, "IIC: No response\r\n");
      break;
    
    case NAK_RESPONSE:
      sprintf(buffer, "IIC: No acknowledge\r\n");
      break;
    
    case IIB_CLEAR_TIMEOUT:
      sprintf(buffer, "IIC: Timeout waiting for reply\r\n");
      break;
    
    case IIB_SET_TIMEOUT: 
      sprintf(buffer, "IIC: Timeout not set\r\n");
      break;
    
    case RECEIVE_TIMEOUT:
      sprintf(buffer, "IIC: Received timeout\r\n");
      break;
    
    case IIC_DATA_SIZE_TOO_SMALL:
      sprintf(buffer, "IIC: Data size incorrect\r\n");
      break;

    default:
      sprintf(buffer, "IIC: Unknown error\r\n");
      break;
  }
    
  SerialOutputString(buffer, &SCI1);
}

void main(void) {
  
  IIC_ERRORS error_code = NO_ERROR;
  
  char buffer[128];
  
  //int currentAddress = 0;
  
  int i;
    
  unsigned long singleSample, avg;
  
  
  for (i=0; i<10; i++) {
   laserValueArr[i] = (unsigned long)i; 
  }
  
  //assert(error_code != NO_ERROR);

  #ifndef SIMULATION_TESTING

  // make sure the board is set to 24MHz
  //  this is needed only when not using the debugger
  PLL_Init();

  // initialise PWM
  PWMinitialise();
  setServoPose(-750, -250); //FOR ANGLE CHANGES WHEN READING MULTIPLE SHELVES

  #endif
  
  // initialise the simple serial
  SerialInitialise(BAUD_9600, &SCI1);
  
  #ifndef SIMULATION_TESTING
  
  // initialise the sensor suite
  error_code = iicSensorInit();
  
  // write the result of the sensor initialisation to the serial
  if (error_code == NO_ERROR) {
    sprintf(buffer, "NO_ERROR\r\n");
    SerialOutputString(buffer, &SCI1);
  } else {
    sprintf(buffer, "ERROR %d\r\n");
    SerialOutputString(buffer, &SCI1);
  }

  laserInit();
  
  #else
  
  #endif

  Init_TC6();
	
  //-----------------------------------------------------------------------------------------|
  // build inventory (without amounts) using a text file of item names (in order of scanning)|
  //-----------------------------------------------------------------------------------------|
	
  EnableInterrupts;
  //COPCTL = 7;
  _DISABLE_COP();
    
  for(;;) {
  
    #ifndef SIMULATION_TESTING
  
    // read the raw values
      
    GetLatestLaserSample(&singleSample);
    
    // laser value array is declared
    // fill out array in handleLaserValues function
    
    avg = handleLaserValues(singleSample, &laserValueArr[0]);
    
    //-----------------------------------------------------------------------------------------|
    // determine what has happened:                                                            |
    //	  1) In same state (either same number of boxes or still in a gap state                |
    //	  2) In a new state								       |
    //-----------------------------------------------------------------------------------------| 
    
    //-----------------------------------------------------------------------------------------|
    // if at a new address modify the number of boxes using the average			       |
    //-----------------------------------------------------------------------------------------| 
    
    //currentAdress++; increment the address once the box number has been updated
	  
    #endif
  
    
    // format the string of the sensor data to go the the serial    
    sprintf(buffer, "%lu\r\n", singleSample);
    
    // output the data to serial
    SerialOutputString(buffer, &SCI1);
    
    
    //_FEED_COP(); /* feeds the dog */
  } /* loop forever */
  
  /* please make sure that you never leave main */
}
