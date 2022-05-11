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
