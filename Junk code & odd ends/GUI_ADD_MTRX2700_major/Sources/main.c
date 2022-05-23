#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>   
#include <string.h>
// need this for string functions

#include "pll.h"
//#include "simple_serial.h" 

#include "l3g4200d.h" 

#include "servo.h"
#include "laser.h"
#include "functions.h"
#include "7_seg.h"

#include "commands.h" 
#include "stringIO.h"
#include "initialiseIO.h" 

char *currentOutputLocation; //Stores character for output string
int writingFlag = 0; //Variable for if the program is currently outputting a string
int *wFpointer = &writingFlag; //Pointer to the writing flag

int list[3] = {1,2,3}; 
int InvatoryLen = sizeof(list)/sizeof(int); 
 
char inputArray[64]; //Allocated memory for incoming strings  
int arrInLocation; //Location in array for incoming strings
 
interrupt VectorNumber_Vsci1 void SerialInterruptHandler(){

  //Output
  if ((*(SCI1.StatusRegister) & SCI1SR1_TDRE_MASK) && (writingFlag == 1)) {
  
    //Output the current character of the string
    SerialOutputChar(*(currentOutputLocation), &SCI1, wFpointer);  
    //Increment char it points to
    currentOutputLocation++;  
    
  }  
  
  //Input 
  else if((*(SCI1.StatusRegister) & SCI1SR1_RDRF_MASK) && (writingFlag==0)){ 
  
    //Store the current input character to the array by passing pointer to currently empty location
    SerialInputChar(&SCI1, inputArray, arrInLocation);
    
    //If the most recently read function is a newline character, read the command
    if(inputArray[arrInLocation] == '\r'){
   
      char* outputString = commandFunction(inputArray, list, InvatoryLen, wFpointer); //Calls the command function
      currentOutputLocation = &outputString[0]; //Assigns the output character to the returned string
      
      arrInLocation = 0; //Resets the location of the input array pointer
      
      if(writingFlag == 1){
        SerialOutputChar(*(currentOutputLocation), &SCI1, wFpointer); //Force the first character output
        currentOutputLocation++; //Increment pointer  
      }       
    }
    else{
  
      //Increment array location if not finished inputting
      arrInLocation++;
    }
            
  }
}

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
    
  //SerialOutputString(buffer, &SCI1);
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
    
  volatile int i, itemNumber, distanceDifference, remainder, div;
    
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
  setServoPose(-750, -2); //FOR ANGLE CHANGES WHEN READING MULTIPLE SHELVES

  #endif
  
  // initialise the simple serial
  //SerialInitialise(BAUD_9600, &SCI1);
  
  #ifndef SIMULATION_TESTING
  
  // initialise the sensor suite
  error_code = iicSensorInit();
  
  // initialise the 7_seg 
  seg7Initialise();
  
  // write the result of the sensor initialisation to the serial
  if (error_code == NO_ERROR) {
    sprintf(buffer, "NO_ERROR\r\n");
    //SerialOutputString(buffer, &SCI1);
  } else {
    sprintf(buffer, "ERROR %d\r\n");
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
    
    
    // determine state of program
    if (avg != 0) { // checking range is within 5cm (determined error of LiDAR)
      distanceDifference = (avg*10) - shelf_distance;
      
      remainder = distanceDifference % box_depth;
      div = 0.5 * box_depth;
      
      
      // 
      if ((distanceDifference >= 425) && (distanceDifference <= 475)) {   // check if gap state
        current_state = 9; // gap state  
      } 
      else if (div <= remainder) { // check if need to round up 
        
        current_state = distanceDifference / box_depth;
        current_state ++;
      }  
      else {                       // otherwise round down 
        current_state = distanceDifference / box_depth;
      }   
      
      display();                   // send current state to 7-seg for testing purposes
      
      current_item = itemArray[item_address-1];     // update the current item 
      determineOccurence(itemArray, current_item);  // interpret flags to determine real-world occurence 
    }
      // format the string of the sensor data to go the the serial    
  sprintf(buffer, "%lu\r\n", singleSample);
    
  // output the data to serial
  //SerialOutputString(buffer, &SCI1);
  
  }
	  
  #endif
  
    
   int ItemArrLen sizeof(itemArray)/sizeof(int);
   for(int n = 0; n < ItemArrLen; ItemArrLen ++ ){
      list[n] = itemArray[n];
   }
   
   
  //list[0] = 9; list[1] = 7; list[2] = 5;         
  SerialInitialiseBasic(&SCI1); //Initialise the SCI1 port for input and output   
  DDRB = 0xFF; //Set the direction to output       
	EnableInterrupts //Turn on interrupts 

      
}
