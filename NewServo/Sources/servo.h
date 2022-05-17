#ifndef SERVO_H
#define SERVO_H
#include "derivative.h"
#include "timer.h"

void PWMinitialise(void);

// servo init (PP5 and PP7)
void servo_init(void);

// pan servo controller (PP67)
void elevation(int starting_angle, int ending_angle, int step);

// tilt servo controller (PP45)
void azimuth(int start, int end, int step);

// goes to specified servo position
void setServoPose(int elevation, int azimuth);

void starting_position(void);


#endif

