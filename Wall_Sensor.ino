#include <SR04.h>
#include <pitches.h>

/*      Wall Sensor v0.1.04
 *      
 *      Last Modified 1/24/19
 */
 
// Pin Numbers
#define redLED 9        //Must Be PMW
#define blueLED 10       //Must Be PMW
#define warningBuzzer 2 //none
#define ussTrigPin 12   //???
#define ussEchoPin 11   //???

// System Settings
int threshold = 122;     //in cm
int cycleTime = 100;        //in ms

// Instantiate Sensor Object
SR04 usSensor = SR04(ussEchoPin,ussTrigPin);

//
//
// Setup
void setup() {  
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(warningBuzzer, OUTPUT);

  introSeq();
}

//
//
// Intro Sequence
//
//    A/V sequence for flashy bootup
void introSeq() {
  analogWrite(redLED, 0);
  analogWrite(blueLED, 255);
  delay(200);
  analogWrite(blueLED, 0);
  delay(800);
  for (int i = 0; i < 256; i++) {
    analogWrite(blueLED, i);
    delay(3);
  }
  
}

//
//
// beepCalc
//
//    Return a float between 0 and 1 indicating how much of each 
//    cycle should be spent with the buzzer on

float beepCalc (float dist, float threshold) {
  float a = dist/threshold;
  if (dist < .5 * threshold) {
    return 1;
  } else if (dist > threshold) {
    return 0;
  } else {
    return pow((-2 * dist/threshold) + 2, 1);   //<-- WTF? X^1?
  }
}

//
//
//  lightAdj
//
//  Set the color of the LED based on warningInstensity (a float between 0 and 1)
void lightAdj(float warningIntensity) {
  int onLightPin;
  int offLightPin;
  int onLightVal;
  int offLightVal;

  onLightVal = 255 * (0.8 * (pow(warningIntensity * 2 - 1, 4)) + 0.2);
  offLightVal = 255 * ((-pow(warningIntensity - 0.5, 2) * 5) + 0.2);
  if (offLightVal < 0) {
    offLightVal = 0;
  }
  
  if (warningIntensity > .5) {
    onLightPin = redLED;
    offLightPin = blueLED;
  } else {
    onLightPin = blueLED;
    offLightPin = redLED;
  }
  
  analogWrite(onLightPin, onLightVal);
  analogWrite(offLightPin, offLightVal);
}

//
//
// Main Loop
void loop() {
  int dist = usSensor.Distance();
  float warningIntensity = beepCalc(dist, threshold);
  int beepLength = cycleTime * warningIntensity;
  
  lightAdj(warningIntensity);
  //lightAdj((float(analogRead(thresholdPot))/1023.00));
  
  if (warningIntensity > 0){
    tone(warningBuzzer, NOTE_C4, beepLength);
  }
  delay(cycleTime);
}
