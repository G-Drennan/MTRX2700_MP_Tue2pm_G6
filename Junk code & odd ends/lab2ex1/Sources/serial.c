#include "serial.h"

#include <hidef.h> // common defines and macros 
#include "stdlib.h"

#include "derivative.h"


// key variable
struct port serialPort0;
struct port1 serialPort1;

// set up serial port
void SerialInitialise (void) {
 
  SCI0BDH = 0;       // Configure the Baud Rate by writing to the Baud Rate register
  SCI1BDH = 0;       // Configure the Baud Rate by writing to the Baud Rate register
  SCI0BDL = 0x9C;       // Clear all options for SCI Control Register 1
  SCI1BDL = 0x9C;         
  SCI0CR1 = 0;          // Enable the transmitter (TE), receiver (RE) and receive
  SCI1CR1 = 0;  
  SCI0CR2 = 0x2C;       // interrupt enable (RIE) bits only 
  SCI1CR2 = 0x2C;       // interrupt enable (RIE) bits only                          
  
  serialPort0.last = serialPort0.input;         // pointer points to start of array
  serialPort1.last1 = serialPort1.input;         // pointer points to start of array  
  
  serialPort0.currentByte =serialPort0.input;
  serialPort1.currentByte1 =serialPort1.input;  
}


// print to the terminal
void output2sci0 (char currentChar) {
 
  while (!(SCI0SR1 & 0x80));
  
    SCI0DRL = currentChar; 
  
}

// print to the terminal
void output2sci1 (char currentChar1) {
 
  while (!(SCI1SR1 & 0x80));
  
    SCI1DRL = currentChar1; 
  
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED


__interrupt void ISR0(void) {
                        
  
  // Check if SCI0SR1 and see if RDRF triggers the interrupt
  // This indicates that the received byte can be read
  
  if (SCI0SR1 & 0x20) {
 
     
     serialPort0.currentChar = SCI0DRL;        // Read in the received byte in the data register SCI0DRL 
     
     if (serialPort0.currentChar != 0x0D) {    // Check if the received byte is not a carriage return character
          
       *(serialPort0.last) = SCI0DRL;    // Store the received byte
       
       output2sci0(*(serialPort0.last));    // Print the received byte
       
       if (serialPort0.currentChar == 0x08) {  // Check if the received byte is a backspace character 
            
         (serialPort0.last)-- ;//move back string pointer
         output2sci0(0x20);   // Output a space
         output2sci0(0x08);   // Output a backspace
          
       } 
       
       else { 
           
         (serialPort0.last)++;           // Increment the pointer by one
        
       }  
      
     } 
     
     else {                                       // The received byte is a carriage return character 
       
       output2sci0(serialPort0.currentChar);      // Print the carriage return character to terminal 
       *(serialPort0.last) = 0;                  // Add a null terminator to the end of the sequence of characters 
       serialPort0.send = 1;                    // indecate the string is been send             
       SCI0CR2 = 0xAC;   
                          
     }       
  }  
  

  // Check TDRE to be empty. 
  // register transfers the currently stored byte to the transmit shift register if empty
  
  while ((SCI0SR1 & 0x80) && (serialPort0.send == 1)) {
  
    SCI0DRL = *(serialPort0.currentByte);       // Print the current character in the array 
    
    if ((serialPort0.currentByte) == (serialPort0.last)) {     // Check if the current character in the array points to the same character
     serialPort0.send = 0;           // indecate that string is send
     SCI0CR2 = 0x2C;     // Enable bits
     SCI0DRL = 0x0D;     // Print a carriage return character 
     break;            
       
    }  
    (serialPort0.currentByte)++;                // Increment the pointer to inspect the next element
  }
}


__interrupt void ISR1(void) {
                        
  
  // Check if SCI0SR1 and see if RDRF triggers the interrupt
  // This indicates that the received byte can be read
  
  if (SCI1SR1 & 0x20) {
 
     
     serialPort1.currentChar1 = SCI1DRL;        // Read in the received byte in the data register SCI0DRL 
     
     if (serialPort1.currentChar1 != 0x0D) {    // Check if the received byte is not a carriage return character
          
       *(serialPort1.last1) = SCI1DRL;    // Store the received byte in an entry of a container array specified 
                          // by the pointer  
       
       output2sci1(*(serialPort1.last1));    // Print the received byte to the terminal so we have an indication
                          // of what we are typing 
       
       if (serialPort1.currentChar1 == 0x08) {  // Check if the received byte is a backspace character 
            
         (serialPort1.last1)-- ;//move back string pointer
         output2sci1(0x20);   // Output a space
         output2sci1(0x08);   // Output a backspace
          
       } 
       
       else { 
           
         (serialPort1.last1)++;           // Increment the pointer by one to point to the next entry in the array 
        
       }  
      
     } 
     
     else {                                        // The received byte is a carriage return character 
       
       output2sci1(serialPort1.currentChar1);      // Print the carriage return character to terminal 
       *(serialPort1.last1) = 0;                   // Add a null terminator to the end of the sequence of characters 
       serialPort1.send = 1;                       // Toggle the value of the boolean 'send' to indicate that we have sent a string across;             
       SCI1CR2 = 0xAC;                    
                          
     }       
  }  
  

  // Check TDRE to be empty. 
  // register transfers the currently stored byte to the transmit shift register if empty
  
  while ((SCI1SR1 & 0x80) && (serialPort1.send == 1)) {
  
    SCI1DRL = *(serialPort1.currentByte1);       // Print the current character in the array 
    
    if ((serialPort1.currentByte1) == (serialPort1.last1)) {     // Check if the current character in the array points to the same character
                         // that was last entered into the data register
     serialPort1.send = 0;           // Toggle the boolean 'send' to 0 to indicate that we have finished sending
     SCI1CR2 = 0x2C;     // Enable the transmitter (TE), receiver (RE) and receive interrupt enable (RIE) bits 
     SCI1DRL = 0x0D;     // Print a carriage return character 
     break;              // Break out of the loop to indicate that we have finished transmitting
       
    }  
    (serialPort1.currentByte1)++;                // Increment the pointer to inspect the next element in the array to be transmitted 
  }
}




