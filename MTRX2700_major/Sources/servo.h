#ifndef SERVO_H
#define SERVO_H

int angle_2_elivation_duty (int angle);

int horizontal_distance(int angle, int lidar_dist);

int shelf_angle(int shelf_number);

void PWMinitialise(void);

// sets servo in elevation and azimuth
// note: this requires verification and calibration 
void setServoPose(int azimuth, int elevation);


// interrupt used for cycling through the servo positions
__interrupt void TC6_ISR(void);

void Init_TC6 (void);


#endif