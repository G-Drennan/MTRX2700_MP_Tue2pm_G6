#include "timer.h"

#include "derivative.h"      /* derivative-specific definitions */


void delay(int k)
{
    volatile unsigned int i,j; //Variables for count

    for (i = 0; i < k; i++) //Nested for loop with null operation to count up
    {
        for (j = 0; j < k; j++)
        {
        }
    }
}
