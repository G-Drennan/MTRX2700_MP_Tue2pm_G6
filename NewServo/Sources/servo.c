#include "derivative.h"
#include <math.h> 
#include "servo.h"
#include "timer.h"


#define ZERO_ELEVATION_DUTY 4600
#define ZERO_AZIMUTH_DUTY 2000


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

    TSCR1 = 0x90;
    TSCR2 = 0x80;
    
    PWME  |= 0xFF;      // enable PWM0
}

void azimuth(int starting_angle, int ending_angle, int step) {
  // convert angles to duty cycles
  int start_dutycycle, end_dutycycle, steps;
  int i;
  start_dutycycle = starting_angle * 10 + ZERO_AZIMUTH_DUTY;
  end_dutycycle = ending_angle * 10 + ZERO_AZIMUTH_DUTY;
  steps = step * 10;
  
  // loop
  for(i = start_dutycycle; i < end_dutycycle; i += steps){
    PWMDTY67 += steps;
    delay(10);
  }    
}


void elevation(int starting_angle, int ending_angle, int step) {
  // convert angles to duty cycles
  int start_dutycycle, end_dutycycle, steps;
  int i;
  start_dutycycle = starting_angle * 10 + ZERO_ELEVATION_DUTY;
  end_dutycycle = ending_angle * 10 + ZERO_ELEVATION_DUTY;
  steps = step * 10;
  
  for(i = start_dutycycle; i < end_dutycycle; i += steps){
    PWMDTY45 += steps;
    delay(10);
  }      
}


void setServoPose(int elevation, int azimuth){
  // convert angles to duty cycles
  int elevation_dtcycle, azimuth_dtcycle;
  azimuth_dtcycle = azimuth * 10 + ZERO_AZIMUTH_DUTY;
  elevation_dtcycle = elevation * 10 + ZERO_ELEVATION_DUTY; 
  
  // update position
  PWMDTY45 = elevation_dtcycle;
  PWMDTY67 = azimuth_dtcycle; 
}


void starting_position(void){
  // start and end azimuth angles
  int start_azimuth = 30, end_azimuth = -30;
  
  // start and end elevation angles
  int start_elevation = 40, end_elevation = -40;
  
  // increment angle
  int step_angle = 10;
  
  // current elevation and azimuth angles
  int current_azimuth = start_azimuth, current_elevation = start_elevation;
  
  // distance
  int distance = 0;
  
  // starting position
  setServoPose(current_azimuth,current_elevation);
  delay(10);
  
  // main loop
  while(start_azimuth >= end_azimuth){
    
    // elevate downwards until it reaches bottom
    while(current_elevation >= end_elevation){
      
      // next azimuth angle
      current_elevation -= step_angle;
      
      // goes to new azimuth position
      setServoPose(current_azimuth,current_elevation);
      delay(10);
    }
  
    // repositions to azimuth upward
    current_azimuth -= step_angle;
    current_elevation += step_angle;
    setServoPose(current_elevation, current_azimuth);
    delay(10);
    
    // azimuth up until reached top
    while(current_elevation <= start_elevation){
      
      // stop when no measurement receieved 
      if(distance == 0){ 
        continue;
      }
      // next azimuth angle
      current_elevation += step_angle;
      
      // new azimuth position
      setServoPose(current_azimuth,current_elevation);
      delay(10);
    }
    
    // reposition to azimuth downwards
    current_azimuth -= step_angle;
    current_elevation -= step_angle;
    setServoPose(current_azimuth,current_elevation);
    delay(10);
    
  }
  
}