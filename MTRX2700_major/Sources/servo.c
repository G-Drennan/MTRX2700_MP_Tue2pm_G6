#include "derivative.h"
#include "servo.h"
#include <math.h>

#define ZERO_ELEVATION_DUTY 4350
#define ZERO_AZIMUTH_DUTY 2000

int angle_2_elivation_duty (int angle){
  
  int elevation;
  
  elevation = 77.392 + 31.521*angle; //77.392 + 31.521*angle;
  
  return elevation;   
}

// Function calculates horizontal distance to object with trigonometry using current angle and LiDAR reading 
int horizontal_distance (int angle, int lidar_dist){
  double val;
  double distance;
  val = PI / 180;
  distance = (double) lidar_dist * cos((double) angle * val);
  
  return (int)distance;
}

// Function returns angle required to hit middle of given input shelf
int shelf_angle(int shelf_number){
  
  double angle = 0;
  double shelf_elevation_angle = 0;      
  double max_angle = 0;
  
  if (shelf_number == 0){
    return angle;
  } 
  else{
    shelf_elevation_angle = atan((HEIGHT_OF_SHELF - HEIGHT_OF_RADAR+HEIGHT_OF_SHELF*((double)shelf_number-1))/(SHELF_DIST - 50.0)) * 180.0/PI;
    max_angle = atan((HEIGHT_OF_SHELF - HEIGHT_OF_RADAR+HEIGHT_OF_SHELF*(double)shelf_number)/SHELF_DIST) * 180.0/PI;
    
    if(max_angle < shelf_elevation_angle){
      return 0;
    }
    angle = shelf_elevation_angle + 0.5 * (max_angle - shelf_elevation_angle);
    return (int)angle;
  }
}
  


void PWMinitialise(void){
    // set PP5 and PP7 for pwm output 
    PWMCLK = 0; // select clock A
    PWMPOL = 0xA0; // PWM5 and PWM7 output start high
    PWMCTL = 0xC0; // 16-bit PWM: use PWM4 and PWM5 for PWM5, PWM6 and PWM7 for PWM7
    PWMCAE = 0; // Center aligned
    PWMPRCLK = 0x33; // PWM Clock prescaler to 8 

    // set the PWM period appropriate for servos
    PWMPER45 = 0xEA6A;
    PWMPER67 = 0xEA6A;

    // set the initial duty cycle for both servos
    PWMDTY45 = ZERO_ELEVATION_DUTY;
    PWMDTY67 = ZERO_AZIMUTH_DUTY;
    
    PWME  |= 0xFF;      // enable PWM0
}

void setServoPose(int azimuth, int angle){  
    int elevation;
    
    elevation = angle_2_elivation_duty(angle);

    PWMDTY45 = (int)(ZERO_ELEVATION_DUTY + elevation);  // Sets elevation to duty cycle using PWM 45
    PWMDTY67 = (int)(ZERO_AZIMUTH_DUTY + azimuth);   // Sets azimuth to duty cycle using PWM 67
}


void Init_TC6 (void) {
  TSCR1_TEN = 1;
  
  TSCR2 = 0x00;   // prescaler 1, before 32 = 0x04
  TIOS_IOS6 = 1;   // set channel 6 to output compare
    
  TCTL1_OL6 = 1;    // Output mode for ch6
  TIE_C6I = 1;   // enable interrupt for channel 6

  TFLG1 |= TFLG1_C6F_MASK;
}


// variables to make the servo move back and forth
// note: This is just to demonstrate the function of the servo
long iterator_counter = 0;
int toggle = 0;


// the interrupt for timer 6 which is used for cycling the servo
#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
__interrupt void TC6_ISR(void) { 
   
  TC6 = TCNT + 64000;   // interrupt delay depends on the prescaler
  TFLG1 |= TFLG1_C6F_MASK;

  if (toggle == 0)
    iterator_counter++;
  else
    iterator_counter--;
  
  if (iterator_counter > 500) {
    toggle = 1;
  } else if (iterator_counter < 0) {
    toggle = 0;
  }
  
  //setServoPose(50 + iterator_counter, 50 + iterator_counter);    
}