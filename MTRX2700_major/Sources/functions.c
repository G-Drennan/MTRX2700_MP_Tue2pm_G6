#include "functions.h"
    
unsigned long handleLaserValues(unsigned long laserValue, unsigned long *laserArr) {

  int arrLen = 10;
  int i, avg, min, max, range;
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

    if (range < 5) {
      avg = 0;
      for (i = 0; i < arrLen; i++) {
        avg = avg + laserArr[i];
      }
      avg = avg / arrLen;
    }
      
    return avg;  
    
}

void determineOccurence(int current_state, item** itemArray) {
  
  item* current_item;
  
  if (current_state = prev_state) {
    // nothing has happened yet
    continue;
  }
  else if (current_state == 0) {
    // arrived at a gap state
    prev_state = current_state;
    item_address ++;
    continue;
  } 
  else {
    // arrived at a new box address, record number of boxes
    prev_state = current_state;
    //item* current_item = itemArray[current_state-1];
    //modifyItem(current_item, );
  }
    
}

