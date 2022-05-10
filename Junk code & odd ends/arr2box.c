#include <string.h>
#include <stdio.h>

/*Code to create a variable output string that can be outputted in codewarroir 
*/
#define BUFFER 10000 

char* outputInvatory(int list[3], int len);

int main(){ 
    int list[3] = {6,9,3};
    int InvatoryLen = sizeof(list)/sizeof(int); 
    //printf("%lu\n", sizeof(list)/sizeof(int));
    char *outputMessage = outputInvatory(list, InvatoryLen);   
   printf("%s", outputMessage);   
} 

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

char* outputInvatory(int list[3], int InvatoryLen){ 
   
   char dest[BUFFER] = "\n---------------------------------\n", 
    Tempstr0[] = "item_X    X\n", Tempstr1[16];
    
    int Tempstr0len = strlen(Tempstr0), pos1 = 5, pos2 = 10;
    char *src ;
    
    // list each item and its ammount
    for(int n=0; n < InvatoryLen; n++){

        char *src1 = variableString(Tempstr0, &pos1, &n);
        char *src2 = variableString(src1, &pos2, &list[n]); 
        strcat(dest, src2);  
    }

    strcat(dest, "---------------------------------\n\n"); 
    return dest;    
} 
