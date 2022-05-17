#include <hidef.h>      /* common defines and macros */
#include <assert.h>
#include "derivative.h"      /* derivative-specific definitions */

// need this for string functions

#include "pll.h"
#include "simple_serial.h"

#include "l3g4200d.h"

#include "servo.h"
#include "laser.h"
#include "functions.h"

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

unsigned long laserValueArr[10];

// shelf parameters

volatile int item_address = 1;

// state parameters
volatile int prev_state = 0; // start on a gap state
volatile int current_state = 0;

void main(void) {
  
  IIC_ERRORS error_code = NO_ERROR;
  
  char buffer[128];
    
  int i, itemNumber, distanceDifference;
    
  unsigned long singleSample, avg;
  
  item** itemArray;
  item* current_item;
  
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
  
  itemNumber = 5;
  itemArray = (item**)malloc(sizeof(item*)*itemNumber);
  
  initialiseInventoryContents(itemArray);
   	
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
    if (avg != 0) {
      distanceDifference = avg - shelf_distance;
      current_state = distanceDifference/box_depth;
      current_item = itemArray[item_address-1];
      determineOccurence(current_state, prev_state, itemArray, current_item);
    }
	  
    #endif
  
    
    // format the string of the sensor data to go the the serial    
    sprintf(buffer, "%lu\r\n", singleSample);
    
    // output the data to serial
    SerialOutputString(buffer, &SCI1);
    
    
    //_FEED_COP(); /* feeds the dog */
  } /* loop forever */
  
  /* please make sure that you never leave main */
}
