#include "functions.h"
    
unsigned long handleLaserValues(unsigned long laserValue, unsigned long *laserArr) {

  int arrLen = 10;
  int i, avg;
  for (i = (arrLen-2); i--; i>1) {
    laserArr[i-1] = laserArr[i];
  }
  
  laserArr[arrLen-1] = laserValue;
  
  avg = 0;
  
  return avg;  
    
}         