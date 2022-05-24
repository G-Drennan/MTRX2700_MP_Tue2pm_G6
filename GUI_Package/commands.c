#include <mc9s12dp256.h>
#include <string.h>
#include <stdio.h> 

#include "commands.h"

//Define the constant strings for the different kinds of commands
const char outputCommand[] = "list";

//**********************************************//
//Define the strings to be output depending on inputs
#define BUFFER 10000
extern char *outputMessage1;//"\n---------------------------------\n" ; //= "This could be the list you are looking for\r\n"; 
//extern char outputMessage2[] = "Or potentially outputs this message\r\n";
extern char errorMessage1[] = "Invalid command\r\n";
//extern int list[3];  
//**********************************************//


//converts num n to char c 
char num2char(int *n){
    char c = *n+'0';
    return c; 
} 

// places a desired number n in a string at a desired position 
char* variableString( char* string, int *position, int *n){
    string[*position] = num2char(n);
    return string; 
}

char dest[BUFFER];
char* outputInvatory(int *list, int InvatoryLen){   
   
      
    char Tempstr0[] = "|  item_X    X  ";
    char Tempstr1[16]; 
    
    int Tempstr0len = strlen(Tempstr0);
    int pos1 = 8;
    int pos2 = 13;  
    char *src;
    int n=0; 
    //strcat(dest, "\n---------------------------------\n");  
   
    // list each item and its ammount
    for(n; n < InvatoryLen; n++){

        char *src1 = variableString(Tempstr0, &pos1, &n);
        char *src2 = variableString(src1, &pos2, &list[n]); 
        strcat(dest, src2);  
    }

    strcat(dest, "\n");  
    return dest;     
} 
    
char* commandFunction(char *inputString, int list[], int InvatoryLen, int *wFpointer){ 
    //Get the length of the input string
    int len = strlen(inputString);
    
  //Output Command
  if(!strncmp(inputString, outputCommand, len-1)){
      //int list[3]; 
      //int InvatoryLen = sizeof(list)/sizeof(int);
      
     outputMessage1 = outputInvatory(list, InvatoryLen);   
    //Set writing flag pointer to 1
    *wFpointer = 1; //Turns on writing flag to ignore reading interrupts 
      
    //First message if parameter is 1 
    
    return outputMessage1; //    
    
  }
  //error message
  else{
      
    *wFpointer = 1; //Turns on writing flag to ignore reading interrupts
    return errorMessage1; //Set the string location to the errorMessage
 
  }
}    