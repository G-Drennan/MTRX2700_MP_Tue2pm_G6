#include <hidef.h>      /* common defines and macros */
#include <assert.h>
#include "derivative.h"      /* derivative-specific definitions */

// need this for string functions

#include "pll.h"

#include "l3g4200d.h"

#include "servo.h"
#include "laser.h"
#include "functions.h"
#include "7_seg.h"

#include "simple_serial.h"

void printErrorCode(IIC_ERRORS error_code) {
  switch (error_code) {
    case NO_ERROR: 
      //sprintf(buffer, "IIC: No error\r\n");
      break;
    
    case NO_RESPONSE: 
      //sprintf(buffer, "IIC: No response\r\n");
      break;
    
    case NAK_RESPONSE:
      //sprintf(buffer, "IIC: No acknowledge\r\n");
      break;
    
    case IIB_CLEAR_TIMEOUT:
      //sprintf(buffer, "IIC: Timeout waiting for reply\r\n");
      break;
    
    case IIB_SET_TIMEOUT: 
      //sprintf(buffer, "IIC: Timeout not set\r\n");
      break;
    
    case RECEIVE_TIMEOUT:
      //sprintf(buffer, "IIC: Received timeout\r\n");
      break;
    
    case IIC_DATA_SIZE_TOO_SMALL:
      //sprintf(buffer, "IIC: Data size incorrect\r\n");
      break;

    default:
      //sprintf(buffer, "IIC: Unknown error\r\n");
      break;
  }
    
  //SerialOutputString(buffer, &SCI1);
}

unsigned long laserValueArr[10];

// shelf parameters
volatile int item_address = 1;

// state parameters
volatile int prev_state = 0; // start on a gap state
volatile int current_state = 0;
volatile int shelf = 0; // start on the bottom shelf

void main(void) {


  IIC_ERRORS error_code = NO_ERROR;
  
  char buffer[128];
      
  volatile int i, itemNumber,lower_gap_limit, upper_gap_limit, angle, tick;
    
  unsigned long singleSample;
  double avg, distanceDifference;
    
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
  setServoPose(-750, 0); //FOR ANGLE CHANGES WHEN READING MULTIPLE SHELVES

  #endif
  
  
  #ifndef SIMULATION_TESTING
  
  // initialise the sensor suite
  error_code = iicSensorInit();
  
  // initialise the 7_seg 
  seg7Initialise();
 
  // write the result of the sensor initialisation to the serial
  if (error_code == NO_ERROR) {
    //sprintf(buffer, "NO_ERROR\r\n");
    //SerialOutputString(buffer, &SCI1);
  } else {
    //sprintf(buffer, "ERROR %d\r\n");
    //SerialOutputString(buffer, &SCI1);
  }

  laserInit();
  
  #else
  
  #endif
  
  //working up to here  
  
  
  Init_TC6();
	
  //-----------------------------------------------------------------------------------------|
  // build inventory (without amounts) using a text file of item names (in order of scanning)|
  //-----------------------------------------------------------------------------------------|
  
  itemNumber = 6;
  itemArray = (item**)malloc(sizeof(item*)*itemNumber);
  
  initialiseInventoryContents(itemArray);
   	
  EnableInterrupts;
  //COPCTL = 7;
  _DISABLE_COP();
  
  tick = 0;  
  for(;;) {
    
    if (item_address == 4 && tick != 1) {
      shelf++;
      DisableInterrupts;
      current_state = 9;
      prev_state = 9;
      tick = 1;
    }
    
    angle = shelf_angle(shelf);
    setServoPose(-750, angle+2);
    EnableInterrupts;

    #ifndef SIMULATION_TESTING
  
    // read the raw values
     
    GetLatestLaserSample(&singleSample);
    
    // laser value array is declared
    // fill out array in handleLaserValues function
    
    avg = handleLaserValues(singleSample, &laserValueArr[0], angle);
    
    // determine state of program
    if (avg != 0) { // checking range is within 5cm (determined error of LiDAR)
      distanceDifference = (avg*10) - shelf_distance;    //might need to mult by 10?
      
      upper_gap_limit = 475;
      lower_gap_limit = 425;
      
       
      if (distanceDifference >= lower_gap_limit && distanceDifference <= upper_gap_limit && shelf == 0) {   // check if gap state
        current_state = 9; // gap state  
      } 
      else if (distanceDifference >= 525 && distanceDifference <= 575 && shelf == 1) {   // check if gap state
        current_state = 9; // gap state  
      }  
   
      else {                       // otherwise round down 
        current_state = distanceDifference / box_depth;
      }   
      
      display();                   // send current state to 7-seg for testing purposes
      
      current_item = itemArray[item_address-1];     // update the current item 
      determineOccurence(current_item);  // interpret flags to determine real-world occurence
            
      if (item_address == 6) {
    
        SerialInitialise(BAUD_9600, &SCI1);
      
        for (i = 0; i < 6; i++) {
          sprintf(buffer, "Item %d: %d\r\n",i, itemArray[i]->amount);  
        }
      freeMemory(itemArray, 6);
      }
    }
  }
      // format the string of the sensor data to go the the serial    
  //sprintf(buffer, "%lu\r\n", singleSample);
    
  // output the data to serial
  //SerialOutputString(buffer, &SCI1);
  
  
	  
  #endif      
}



