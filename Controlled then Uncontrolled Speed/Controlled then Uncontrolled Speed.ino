#include "FastAccelStepper.h"

#define dirPinStepper 4
#define enablePinStepper 2
#define stepPinStepper 9
byte PWM_PIN = 3;

int spd;
int pwm_value;
float diff;

FastAccelStepperEngine engine = FastAccelStepperEngine();
FastAccelStepper *stepper = NULL;

void setup() {
  pinMode(PWM_PIN, INPUT);
  engine.init();
  Serial.begin(9600);
  stepper = engine.stepperConnectToPin(stepPinStepper);
  if (stepper) {
    stepper->setDirectionPin(dirPinStepper);
    stepper->setEnablePin(enablePinStepper);
    stepper->setAutoEnable(true);
  }
}
 
void loop() {
  
  pwm_value = pulseIn(PWM_PIN, HIGH); // input pwm signal from receiver
  stepper->moveByAcceleration(200*diff, 0); // acceleration/decceleration of output frequency

  diff = map(pwm_value, 994, 1990, -2, 3); // pwm_value mapped to value between -2 and 3
  
  stepper->setSpeedInHz(20000);  // max frequency outputed 
  stepper->moveByAcceleration(200*diff, 0); // acceleration/decceleration of output frequency
  spd = (stepper->getCurrentSpeedInMilliHz())/1000; // output frequency
  //Serial.println(spd);

  while (spd > 5500 && spd < 15000) {
    stepper->moveByAcceleration(400, 0); // acceleration/decceleration of output frequency
    spd = (stepper->getCurrentSpeedInMilliHz())/1000; // output frequency 
    //Serial.println(spd);
  }
  while (spd > 5000) {
    stepper->moveByAcceleration(-400, 0); // acceleration/decceleration of output frequency
    spd = (stepper->getCurrentSpeedInMilliHz())/1000; // output frequency 
    //Serial.println(spd);
  }
  
}



