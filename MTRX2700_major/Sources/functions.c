#include "functions.h"
#include "servo.h"
    
double handleLaserValues(unsigned long laserValue, unsigned long *laserArr, int angle) {

  float arrLen = 25.0;
  volatile int i, min, max, converted_laser_value;
  volatile double avg;
  volatile int range;
  for (i = 0; i < arrLen; i++) {
    laserArr[i] = laserArr[i+1];
  }
  converted_laser_value = horizontal_distance(angle, laserValue);
  laserArr[(int)arrLen-1] = converted_laser_value;
  
  max = 0;
  min = 10000;
  avg = 0.0;

  for (i = 0; i < arrLen; i++) {
      if (laserArr[i] > max) {
        max = laserArr[i];
      }
      if (laserArr[i] < min) {
        min = laserArr[i];
      }
    }
    
    range = max - min;

    if (range < 40) {
      avg = 0;
      for (i = 0; i < arrLen; i++) {
        avg = avg + (laserArr[i]/10);
      }
      avg = avg / arrLen;
      
    }
      
    return avg;  
    
}

void determineOccurence(item* current_item) {
      
  if (current_state == prev_state) {
    // nothing has happened yet
  }
  else if (current_state == 9 && current_state != prev_state) {
    // arrived at a gap state
    prev_state = current_state;
    item_address ++;
  } 
  else if (current_state != 9 && prev_state == 9) {
    // arrived at a new box address, record number of boxes
    prev_state = current_state;
    current_item->amount = current_state;
  }
    
}

void initialiseInventoryContents(item** itemArray) {
  
  item* current_item;
  char* names[6] = {"item1", "item2", "item3", "item4","item5", "item6"};
  int k = 0;
  
  for (k = 0; k < 5; k++) {
    current_item = (item*)malloc(sizeof(item));
    strcpy(current_item->name, names[k]);
    itemArray[k] = current_item;
      
  }     
}

void freeMemory(item** itemArray, int numItems){
    int i = 0;
    for(i = 0; i<numItems; i++){
        free(itemArray[i]);
    }
    // Free the pointer to the array
    free(itemArray);

}

