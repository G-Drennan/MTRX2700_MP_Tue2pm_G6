#include "functions.h"
    
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
