#include <mc9s12dp256.h>
#include <string.h>

#include "commands.h"

//Define the constant strings for the different kinds of commands
const char outputCommand[] = "list";

//**********************************************//
//Define the strings to be output depending on inputs
extern char outputMessage1[] = "This could be the list you are looking for\r\n";
//extern char outputMessage2[] = "Or potentially outputs this message\r\n";
extern char errorMessage1[] = "Invalid command\r\n";

//**********************************************//
//Compare input to command function
char* commandFunction(char *inputString, int *wFpointer){
  
  //Get the length of the input string
  int len = strlen(inputString);  

  //Output Command
  if(!strncmp(inputString, outputCommand, len-1)){
  
    //Set writing flag pointer to 1
    *wFpointer = 1; //Turns on writing flag to ignore reading interrupts
    
    //First message if parameter is 1
    return outputMessage1; //Set the string location to the outputMessage1
    
  }
  //error message
  else{
      
    *wFpointer = 1; //Turns on writing flag to ignore reading interrupts
    return errorMessage1; //Set the string location to the errorMessage
 
  }
}