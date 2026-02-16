#include <Arduino.h>
#include "PS2_CTL.hpp"  
#include "Config.h"     
#include "Hiwonder.hpp" 
#include "Robot_Arm.hpp"

// Objects
PS2_CTL ps2_ctrl; 
LeArm_t arm;
Buzzer_t buzzer;
Led_t led; 

// Servo Angle Variables (0-240 scale)
float s1 = 120, s2 = 120, s3 = 120, s4 = 120, s5 = 120, s6 = 120;

// Speed Constants
const float fastStep = 3.5;  // Always for Servo 1
const float slowStep = 1.1;  // Normal speed for others
const float turboStep = 2.8; // Turbo speed for others

void setup() {
  Serial.begin(115200);
  
  arm.init();
  buzzer.init(IO_BUZZER);
  led.init(IO_LED);
  
  ps2_ctrl.init(); 
  arm.reset(1000); 
}

void loop() {
  // 1. Fetch new data
  ps2_ctrl.receive_msg(); 

  // 2. Determine current speed for Servos 2-6
  // If Left Joystick is pressed, use turboStep, otherwise use slowStep
  float currentSlowStep = ps2_ctrl.keyvalue.bit_leftjoystick_press ? turboStep : slowStep;

  // Servo 1: D-Pad Left/Right (Always Fast)
  if(ps2_ctrl.keyvalue.bit_right) s1 = constrain(s1 + fastStep, 0, 240);
  if(ps2_ctrl.keyvalue.bit_left)  s1 = constrain(s1 - fastStep, 0, 240);

  // Servo 2: D-Pad Up/Down
  if(ps2_ctrl.keyvalue.bit_up)    s2 = constrain(s2 + currentSlowStep, 0, 240);
  if(ps2_ctrl.keyvalue.bit_down)  s2 = constrain(s2 - currentSlowStep, 0, 240);

  // Servo 3: Triangle / Cross
  if(ps2_ctrl.keyvalue.bit_triangle) s3 = constrain(s3 + currentSlowStep, 0, 240); 
  if(ps2_ctrl.keyvalue.bit_cross)    s3 = constrain(s3 - currentSlowStep, 0, 240); 

  // Servo 4: Square / Circle
  if(ps2_ctrl.keyvalue.bit_square)   s4 = constrain(s4 + currentSlowStep, 0, 240); 
  if(ps2_ctrl.keyvalue.bit_circle)   s4 = constrain(s4 - currentSlowStep, 0, 240); 

  // Servo 5: R1 / R2
  if(ps2_ctrl.keyvalue.bit_r1)       s5 = constrain(s5 + currentSlowStep, 0, 240);
  if(ps2_ctrl.keyvalue.bit_r2)       s5 = constrain(s5 - currentSlowStep, 0, 240);

  // Servo 6: L1 / L2
  if(ps2_ctrl.keyvalue.bit_l1)       s6 = constrain(s6 + currentSlowStep, 0, 240);
  if(ps2_ctrl.keyvalue.bit_l2)       s6 = constrain(s6 - currentSlowStep, 0, 240);

  // 3. Write to Servos
  arm.knot_run(1, s1 * 4.16, 20);
  arm.knot_run(2, s2 * 4.16, 20);
  arm.knot_run(3, s3 * 4.16, 20);
  arm.knot_run(4, s4 * 4.16, 20);
  arm.knot_run(5, s5 * 4.16, 20);
  arm.knot_run(6, s6 * 4.16, 20);

  delay(20);
}