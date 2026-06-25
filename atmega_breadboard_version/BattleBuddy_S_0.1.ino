/*      Wall Sensor v0.1.04
 *      
 *      Last Modified 1/10/20
 */

#include <SPI.h>
#include <Wire.h>

/*/ Pin Numbers for Board V0.1
#define redLED 9        //Must Be PMW
#define blueLED 10            //Must Be PMW
#define sensorEcho 12     //none
#define sensorTrig 11     //none*/
// Pin Numbers for Breadboard Prototype
#define redLED 5        //Must Be PMW
#define blueLED 3            //Must Be PMW
#define sensorTrig 12     //none
#define sensorEcho 11     //none*/

// System Settings
#define distMin 30            //Min distance for LED fade, in cm
#define distMax 64           //Max distance for LED fade, in cm
#define maxIntensity 0.125 * .6     //Dimming factor for led plus software 3v to 5v conversion
#define cycleTime 50        //both sensors, in ms
float sensitivity = 1.00;

//Loop Control
long nextCycleTime;

// 
//
// Setup
void setup() {  
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(sensorTrig, OUTPUT);
  pinMode(sensorEcho, INPUT);

  introSeq();
    
  nextCycleTime = millis() + cycleTime;
}

//
//
// Main Loop
void loop() {
  if(millis() >= nextCycleTime) {
    nextCycleTime = millis() + cycleTime;
    sampleSensor();
  }
}

//
//
//  Distance(cm) to Intesity(0-255)
int distanceToIntensity(long distance) {
  return constrain(map(distance, distMin * sensitivity, distMax * sensitivity, 255 * maxIntensity, 0), 0, 255 * maxIntensity);
}

//
//
//  Returns distance to 
void sampleSensor() {
  digitalWrite(sensorTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(sensorTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensorTrig, LOW);
  delayMicroseconds(2);

  analogWrite(redLED, 255 - (distanceToIntensity(pulseIn(sensorEcho, HIGH, 400000) * (100.00 / 5882.00))));
}

//
//
// Intro Sequence
//
//    A/V sequence for flashy bootup
void introSeq() {
  analogWrite(redLED, 255);
  analogWrite(blueLED, 0);
  delay(200);
  analogWrite(blueLED, 255);
  delay(800);
  for (int i = 0; i < 256; i++) {
    analogWrite(redLED, 255 - i/16);
    analogWrite(blueLED, 255 - i);
    
    delay(3);
  }

  analogWrite(redLED, 255);
  analogWrite(blueLED, 255);  
}
