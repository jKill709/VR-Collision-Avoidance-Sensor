/*      Wall Sensor v0.1.04
 *      
 *      Last Modified 1/10/20
 *
 *      Ultrasonic proximity sensor with RGB LED visual feedback.
 *      As an object approaches, the LED intensity increases.
 *      Includes startup animation sequence.
 */

#include <SPI.h>
#include <Wire.h>


// Pin Numbers            
#define redLED 5          // Red LED Pin          | Must Be PMW
#define blueLED 3         // Blue LED Pin         | Must Be PMW
#define sensorTrig 12     // HC-SR04 Trigger Pin  | no requirements
#define sensorEcho 11     // HC-SR04 Echo Pin     | no requirements

// System Settings
#define distMin 30                // Min distance for LED fade, in cm
#define distMax 64                // Max distance for LED fade, in cm
#define maxIntensity 0.125 * .6   // Maximum LED brightness scaling factor.  Could be replaced with larger resistor than BOM spec.
#define cycleTime 50              // Sensor update interval in milliseconds

// Sensitivity multiplier used to adjust effective sensor range
float sensitivity = 1.00;

// Loop Control
// Stores the next time the sensor should be sampled
long nextCycleTime;

// 
//
// Setup
void setup() {  

  // Configure LED pins as outputs
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(sensorTrig, OUTPUT);
  pinMode(sensorEcho, INPUT);


  // Configure ultrasonic sensor pins
  introSeq();
    

  // Schedule first sensor reading
  nextCycleTime = millis() + cycleTime;
}

//
//
// Main Loop
void loop() {

  // Timing control.  Only samples the sensor after cycleTime has elapsed.
  if(millis() >= nextCycleTime) {

    // Schedule next sensor reading
    nextCycleTime = millis() + cycleTime;

    // Read distance and update LED output
    sampleSensor();
  }
}

//
//
// Converts distance value into LED intensity value
//
// Close distance  = brighter LED
// Far distance    = dimmer LED
//
// Returns PWM value from 0-255
int distanceToIntensity(long distance) {

  // Maps measured distance range into LED brightness range
  // constrain prevents values outside the valid PWM range
  return constrain(map(distance, distMin * sensitivity, distMax * sensitivity, 255 * maxIntensity, 0), 0, 255 * maxIntensity);
}

//
//
//  Reads ultrasonic sensor and updates LED brightness
void sampleSensor() {

  // Send ultrasonic trigger pulse
  digitalWrite(sensorTrig, LOW);
  delayMicroseconds(2);

  digitalWrite(sensorTrig, HIGH);
  delayMicroseconds(10);

  digitalWrite(sensorTrig, LOW);
  delayMicroseconds(2);

  // Measure echo return time and convert to distance
  // pulseIn returns microseconds
  // Conversion factor converts time into centimeters
  //
  // LED brightness is inverted:
  // closer object = higher intensity
  // farther object = lower intensity
  analogWrite(redLED, 255 - (distanceToIntensity(pulseIn(sensorEcho, HIGH, 400000) * (100.00 / 5882.00))));
}

//
//
// Intro Sequence
//
//    A/V sequence for flashy bootup
void introSeq() {

  // Turn on red LED
  analogWrite(redLED, 255);

  // Turn off blue LED
  analogWrite(blueLED, 0);

  delay(200);

  // Turn on blue LED
  analogWrite(blueLED, 255);

  delay(800);

  // Fade both colors down
  for (int i = 0; i < 256; i++) {

    // Gradually reduce LED intensity
    analogWrite(redLED, 255 - i/16);
    analogWrite(blueLED, 255 - i);
    
    delay(3);
  }

  // Leave LEDs fully illuminated after startup
  analogWrite(redLED, 255);
  analogWrite(blueLED, 255);  
}
