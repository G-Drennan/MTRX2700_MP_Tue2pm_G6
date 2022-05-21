#include "functions.h"
#include "derivative.h"
    
unsigned long handleLaserValues(unsigned long laserValue, unsigned long *laserArr) {

  int arrLen = 30;
  int i, avg, min, max;
  volatile int range;
  for (i = 0; i < arrLen; i++) {
    laserArr[i] = laserArr[i+1];
  }
  
  laserArr[arrLen-1] = laserValue;
  
  max = 0;
  min = 10000;
  avg = 0;

  for (i = 0; i < arrLen; i++) {
      if (laserArr[i] > max) {
        max = laserArr[i];
      }
      if (laserArr[i] < min) {
        min = laserArr[i];
      }
    }
    
    range = max - min;

    if (range < 50) {
      avg = 0;
      for (i = 0; i < arrLen; i++) {
        avg = avg + laserArr[i];
      }
      
      if ((avg % arrLen) >= (arrLen/2)) {
        avg = (avg / arrLen)+1;
      } 
      else {
        avg = avg / arrLen;
      }
      
    }
      
    return avg;  
    
}

void determineOccurence(item** itemArray, item* current_item) {
      
  if (current_state == prev_state) {
    // nothing has happened yet
  }
  else if (current_state == 0 && current_state != prev_state) {
    // arrived at a gap state
    prev_state = current_state;
    item_address ++;
  } 
  else if (current_state != 0 && current_state != prev_state) {
    // arrived at a new box address, record number of boxes
    prev_state = current_state;
    current_item->amount = current_state;
  }
    
}

void initialiseInventoryContents(item** itemArray) {
  
  item* current_item;
  char* names[5] = {"item1", "item2", "item3", "item4","item5"};
  int k = 0;
  
  for (k = 0; k < 5; k++) {
    current_item = (item*)malloc(sizeof(item));
    strcpy(current_item->name, names[k]);
    itemArray[k] = current_item;
      
  }     
}

void display(void){
  int seg_values_arr[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; // store 7-seg values for 0-9
  
  PORTB = seg_values_arr[current_state]; //displayed on 7-seg
  
  //0x06
}

void seg7Initialise(void){
    DDRB = 0xFF;      // set port B and D to outputs
    DDRP = 0xFF; 
    
    PTP = 0xFE; // turn the left-most 7-seg 11111110  
}