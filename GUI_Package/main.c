#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include <stdio.h>   
#include <string.h>

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

/*interrupt 25 void Hbutton_ISR(){
    
    list[0] = 9; list[1] = 7; list[2] = 5;  
	//for()
    SerialInitialiseBasic(&SCI1); //Initialise the SCI1 port for input and output   
    DDRB = 0xFF; //Set the direction to output   
} */


//Main
void main(void){

  list[0] = 9; list[1] = 7; list[2] = 5;         
  SerialInitialiseBasic(&SCI1); //Initialise the SCI1 port for input and output   
  DDRB = 0xFF; //Set the direction to output    
	EnableInterrupts //Turn on interrupts


  for(;;) {
  
  } 
} 
 
