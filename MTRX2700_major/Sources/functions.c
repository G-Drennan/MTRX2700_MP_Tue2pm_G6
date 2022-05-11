#include "functions.h"
    
unsigned long handleLaserValues(unsigned long laserValue, unsigned long *laserArr) {

  int arrLen = 10;
  int i, avg;
  for (i = 0; i < arrLen; i++) {
    laserArr[i] = laserArr[i+1];
  }
  
  laserArr[arrLen-1] = laserValue;
  
  avg = 0;
  
  return avg;  
    
}         
