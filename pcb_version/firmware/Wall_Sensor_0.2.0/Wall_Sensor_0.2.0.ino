#include <SR04.h>
#include <pitches.h>

/*      Wall Sensor v0.1.04
 *      
 *      Last Modified 1/24/19
 *
 *      Ultrasonic proximity warning system.
 *      Uses distance measurement to control:
 *      - RGB LED warning intensity
 *      - Audible buzzer feedback
 *
 *      As an object approaches:
 *      - LED color shifts from blue toward red
 *      - Warning tone increases in duration
 */
 
// Pin Numbers
#define redLED 9          // Red LED Pin          | Must Be PMW
#define blueLED 10        // Blue LED Pin         | Must Be PMW
#define warningBuzzer 2   // Buzzer Pin           | no requirements
#define ussTrigPin 12     // HC-SR04 Trigger Pin  | no requirements
#define ussEchoPin 11     // HC-SR04 Echo Pin     | no requirements

// System Settings
int threshold = 122;      // Distance at which warning begins, in cm
int cycleTime = 100;      // Main update cycle time, in ms

// Instantiate Sensor Object
SR04 usSensor = SR04(ussEchoPin,ussTrigPin);

//
//
// Setup
void setup() {  

  // Configure output pins
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(warningBuzzer, OUTPUT);

  // Run startup LED animation
  introSeq();
}

//
//
// Intro Sequence
//
//    A/V sequence for flashy bootup
void introSeq() {

  // Start with blue LED fully on
  analogWrite(redLED, 0);
  analogWrite(blueLED, 255);

  delay(200);

  // Turn blue off
  analogWrite(blueLED, 0);

  delay(800);

  // Fade blue LED back in
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
//
//    0 = no warning
//    1 = continuous warning
//
//    Warning increases as distance decreases
float beepCalc (float dist, float threshold) {

  // Distance ratio relative to warning threshold
  float a = dist/threshold;

  // Maximum warning when object is closer than half threshold
  if (dist < .5 * threshold) {
    return 1;

  // No warning when outside threshold distance
  } else if (dist > threshold) {
    return 0;

  // Scale warning intensity between half threshold and threshold
  } else {
    return pow((-2 * dist/threshold) + 2, 1);   //<-- WTF? X^1?
  }
}

//
//
//  lightAdj
//
//  Set the color of the LED based on warningInstensity
//
// warningIntensity:
// 0 = blue / no warning
// 1 = red / maximum warning
//
// Adjusts both active and inactive LED channels
void lightAdj(float warningIntensity) {

  int onLightPin;
  int offLightPin;

  int onLightVal;
  int offLightVal;


  // Calculate brightness of active LED channel
  onLightVal = 255 * (0.8 * (pow(warningIntensity * 2 - 1, 4)) + 0.2);

  // Calculate brightness of inactive LED channel
  offLightVal = 255 * ((-pow(warningIntensity - 0.5, 2) * 5) + 0.2);


  // Prevent negative PWM values
  if (offLightVal < 0) {
    offLightVal = 0;
  }


  // Select LED color based on warning intensity
  if (warningIntensity > .5) {

    // Higher warning = red dominant
    onLightPin = redLED;
    offLightPin = blueLED;

  } else {

    // Lower warning = blue dominant
    onLightPin = blueLED;
    offLightPin = redLED;
  }


  // Apply calculated LED brightness
  analogWrite(onLightPin, onLightVal);
  analogWrite(offLightPin, offLightVal);
}

//
//
// Main Loop
void loop() {

  // Read distance from ultrasonic sensor
  int dist = usSensor.Distance();

  // Convert distance into warning intensity
  float warningIntensity = beepCalc(dist, threshold);

  // Convert warning intensity into buzzer duration
  int beepLength = cycleTime * warningIntensity;
  

  // Update RGB LED output
  lightAdj(warningIntensity);


  // Play warning tone if object is within range
  if (warningIntensity > 0){

    // Tone duration increases as object gets closer
    tone(warningBuzzer, NOTE_C4, beepLength);
  }

  // Wait before next sensor update
  delay(cycleTime);
}
