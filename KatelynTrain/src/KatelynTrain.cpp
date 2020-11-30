/*
 * Project KatelynTrain
 * Description: Firmware to move the Christmas tree train
 * Author: JJ OBrien 
 * Date: 11/16/2020
 */

#include "Particle.h"
#ifndef KATELYN_TRAIN_H
    #include <KatelynTrain.h>
#endif

//used to debounce potentiometer
int lastPot = MIN_BITS_WITH_POT;
int currentSpeed = 0;

// setup() runs once, when the device is first turned on.
void setup() {
  pinMode(PWM_PIN, OUTPUT);
  pinMode(POT_PIN, INPUT);

  //register remote functions 
  Particle.function("changeSpeed", changeSpeed);
  Particle.function("killSwitch", killSwitch);
}

void loop() {
  Serial.print("current speed: ");
  Serial.println(currentSpeed);
  //poll the potentiometer to see if we need to change speed
  changeSpeedWithPotentiometer();
  delay(2000);
}

//bounded from 1 to 50
int changeSpeed(String newSpeed){
  Serial.print("new speed: "); 
  Serial.println(newSpeed);
  //255 is the most that the PWM can take
  //the power supply goes to 19.22V, but the train can only take a max of 12V
  //the usable speeds seem to be between 150 (barely moves) and 200 (derails)
  int newSpeedAsInt = newSpeed.toInt();
  //PWM ranges from 0 to 255, but only 150-200 is useful to the train, so we work with those values
  int pwmSignal = 0;
  if (newSpeedAsInt > PWM_RANGE){
    pwmSignal = MAX_PWM;
  }else if (newSpeedAsInt > 0)
  {
    pwmSignal = MIN_PWM + newSpeedAsInt;
  }else{
    pwmSignal = 0;
  }

  //todo: remove the currentspeed global variable once done debugging
  currentSpeed = newSpeedAsInt;
  analogWrite(PWM_PIN, pwmSignal);
}

void changeSpeedWithPotentiometer(){
  int currentPot = analogRead(POT_PIN);
  // Serial.print("current pot: ");
  // Serial.println(currentPot);
  // Serial.print("lastpot: ");
  // Serial.println(lastPot);
  int difference = lastPot - currentPot;

  //debounce (i.e. no change less than 50 should be acknowledged)
  if (difference > 50 || difference < -50) {
    changeSpeed(String(((currentPot-MIN_BITS_WITH_POT)/(double)MIN_BITS_WITH_POT) * PWM_RANGE));
    lastPot = currentPot;
  }
}

int killSwitch(String argsNotImplemented){
  changeSpeed("0");
}