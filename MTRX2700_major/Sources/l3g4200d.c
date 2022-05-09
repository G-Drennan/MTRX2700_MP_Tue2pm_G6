/** \file iic.c
 * @brief Functions to read, initialise and test sensors using IIC
 * Most of this code was downloaded from the course website and modified - link in report
 */

/*
 *Implementing code that utilises the IIC. 
 *The functions used in this file come from the file "iicAuxillary".
*/

// Serial port should be set to 9600 baud rate
// check if serial port on Dragon12 is configured somewhere else in our main program
// check if the function checking the e-clock frequency is needed here
// Check if we need timer and alarm functions - if we do copy them over

#include "l3g4200d.h"


#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "l3g4200d_definitions.h"


// Initialise each sensor
IIC_ERRORS iicSensorInit(void)
{
   volatile IIC_ERRORS error_code = NO_ERROR;
   
   // start the iic running
   iicinit(IIC_20KHZ);//IIC_100KHZ);
   
   if (error_code != NO_ERROR)
     return error_code;
}
