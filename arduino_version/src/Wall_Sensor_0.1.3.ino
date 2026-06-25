#include "SR04.h"
#include "pitches.h"

/*      Wall Sensor v0.1.03
 *      
 *      
 */
 
// Pin Numbers
int onOffLED = 5;
int warningBuzzer = 2;
int ussTrigPin = 12;
int ussEchoPin = 11;
int warningLED = 8;
int thresholdPot = A3;

// System Settings
int minThreshold = 61;      //in cm
int maxThreshold = 122;     //in cm
int cycleTime = 100;        //in ms

// Instantiate Sensor Object
SR04 usSensor = SR04(ussEchoPin,ussTrigPin);

//
//
// Setup
void setup() {
  Serial.begin(9600);
  
  pinMode(onOffLED, OUTPUT);
  pinMode(warningBuzzer, OUTPUT);
  pinMode(warningLED, OUTPUT);
  pinMode(thresholdPot, INPUT);

  digitalWrite(onOffLED, HIGH);
}

//
//
// beepCalc

float beepCalc (float dist, float threshold) {
  float a = dist/threshold;
  if (dist < .5 * threshold) {
    return 1;
  } else if (dist > threshold) {
    return 0;
  } else {
    Serial.print(a);
    Serial.print(", ");
    return pow((-2 * dist/threshold) + 2, 1);
  }
}

//
//
// Main Loop
void loop() {
  int dist = usSensor.Distance();
  int threshold = minThreshold + ((maxThreshold - minThreshold) * (float(analogRead(thresholdPot))/1023.00));
  int beepLength;
  beepLength = cycleTime * beepCalc(dist, threshold);
  Serial.print(beepLength);
  Serial.print(", ");
  Serial.print(cycleTime);
  Serial.print(":  ");

  Serial.print(dist);
  Serial.print(" / ");
  Serial.print(threshold);
  Serial.print(" cm  (");
  Serial.print(beepLength);
  Serial.print(" ms)");

  if (dist < threshold){
    //Serial.print(", S");
    digitalWrite(warningLED, HIGH);
    //Serial.print(", L");
    tone(warningBuzzer, NOTE_G5, beepLength);
    //Serial.print(", B");
    Serial.print(beepLength);
    delay(cycleTime);
    //Serial.print(", D");
    //noTone(warningBuzzer);
    //'Serial.print(", N");
  }
  else {
    noTone (warningBuzzer);
    delay(cycleTime);
    digitalWrite(warningLED, LOW);
  }
  Serial.println("");
}
