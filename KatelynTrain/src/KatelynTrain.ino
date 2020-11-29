/*
 * Project KatelynTrain
 * Description: Firmware to move the Christmas tree train
 * Author: JJ OBrien 
 * Date: 11/16/2020
 */

#define PWM_PIN D2

int changeSpeed(String newSpeed);
int killSwitch(String argsNotImplemented);



// setup() runs once, when the device is first turned on.
void setup() {
  pinMode(PWM_PIN, OUTPUT);

  //register remote functions 
  Particle.function("changeSpeed", changeSpeed);
  Particle.function("killSwitch", killSwitch);
}

void loop() {

}

int changeSpeed(String newSpeed){
  //255 is the most that the PWM can take
  //the power supply goes to 19.22V, but the train can only take a max of 19.22V
  //throw out anything above 12V (which is ~159)
  int newSpeedAsInt = newSpeed.toInt();
  // if (newSpeedAsInt > 150){
  //   newSpeedAsInt = 150;
  // }else if (newSpeedAsInt < 80)
  // {
  //   newSpeedAsInt = 0;
  // }  

  analogWrite(PWM_PIN, newSpeedAsInt);
}

int killSwitch(String argsNotImplemented){
  changeSpeed("0");
}