#ifndef SERIAL_HEADER
#define SERIAL_HEADER


// Function to initialise serial SCI0
void SerialInitialise();
 
// Interrupt Service Routine for SCI0 
__interrupt void ISR0(void);

struct port{
   char input[200];      // Input for the Serial Port 
   char currentChar;     // Current character for sci0
   char* currentByte;    // Current byte for sci0
   int send;             // Find out if it is ready to be send (0) or not (1)
   char* last;           // Pointer to point at the last bit of the input sci0   
    
};

struct port1{
   char input[200];      // Input for the Serial Port 
   char currentChar1;     // Current character for sci1 
   char* currentByte1;    // Current byte for sci1
   int send;             // Find out if it is ready to be send (0) or not (1)
   char* last1;           // Pointer to point at the last bit of the input sci1      
    
};

// Interrupt Service Routine for SCI0 
__interrupt void ISR1(void);

#endif 