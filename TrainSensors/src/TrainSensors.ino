/*
 * Project TrainSensors
 * Description: Particle Photon
 *  code to monitor the sensors on the train
 * Author: JJ OBrien
 * Date: 11/29/2020
 */

#include <Adafruit_LIS3DH.h>

//LIS3DH documentation and examples at: https://learn.adafruit.com/adafruit-lis3dh-triple-axis-accelerometer-breakout/arduino
//I2C configuration
Adafruit_LIS3DH accelerometer = Adafruit_LIS3DH();

sensors_event_t event; 

//set the range of the sensor here
/*your options range from 2G to 16Gs: 
 *LIS3DH_RANGE_2_G
 *LIS3DH_RANGE_4_G
 *LIS3DH_RANGE_8_G
 *LIS3DH_RANGE_16_G
 */
#define RANGE_SELECTION LIS3DH_RANGE_2_G 

//global variables used in velocity calculation
int lastVelocity = 0; //m/s
long lastTimeStamp = millis();

void setup() {
  //setup BAUD rate for 9600 bps
  Serial.begin(9600);
  accelerometer.setRange(RANGE_SELECTION);
}

void loop() {
  float currentVelocity = calculateVelocity();
  Serial.print("Current Velocity: ");
  Serial.println(currentVelocity);
}

//retuns the current velocity in m/s
float calculateVelocity(){
  accelerometer.read();
  //getEvent is supposed to help with acceleration calculation
  accelerometer.getEvent(&event);

  //pull the x, y, and z values
  float currentX = accelerometer.x;
  float currentY = accelerometer.y;
  float currentZ = accelerometer.z;

  Serial.print("Acc: ");
  Serial.println(event.acceleration.x);

  Serial.print("X: ");
  Serial.println(currentX);
  Serial.print("Y: ");
  Serial.println(currentY);
  Serial.print("Z: ");
  Serial.println(currentZ);
  long currentTimestamp = millis();
  //velocity = u + at (u is previous velocity, a is current acceleration, t is time interval)
  float currentVelocity = lastVelocity + event.acceleration.x * (currentTimestamp - lastTimeStamp);
  lastVelocity = currentVelocity;
  lastTimeStamp = currentTimestamp;
  return currentVelocity;
}
