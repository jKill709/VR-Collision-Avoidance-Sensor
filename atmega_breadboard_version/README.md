# Atmega-Breadboard Wall Sensor -  "The Battle Buddy"

![Arduino Prototype](images/assembled-front.jpg)

## Purpose

Build on previous work to create usable prototype of an embedded device to prevent physical collisions while using VR headsets.

This prototype was developed to validate the off-the-shelf modules and design used for this embedded device before transitioning to a Custom PCB implementation.

---

## Architecture

- Ultrasonic sensor module (HC-SR04) to measure distance
- Red and blue LEDs to alert the VR user of detected objects and the estimated distance
- LEDs are ran non destructivly to the optical cavity of the VR headset for user indication
- atmega328p microcontroller for logic and control
- Li-on Battery for wireless operation
- HW-107 Battery Management Module for charging

---

## Hardware

### Components

| Item | Qty | Reference | Value | Description |
|:---|:---:|:---:|:---:|:---|
| 1 | 1 | U1 |  | Microcontroller |
| 2 | 1 | X1 |  | Piezoelectric Oscillator |
| 3 | 2 | C1 C2 | 22 pF | Ceramic Capacitor |
| 4 | 1 | HC-SR04 |  | Ultrasonic Sensor |
| 5 | 1 | R1 | 10K Ohms | Resistor |
| 6 | 1 | D1 | 5V | RGB LED |
| 7 | 2 | R2 R3 | 220 Ohms | Current-Limiting Resistor |
| 8 | 1 |  | 400 Tie-Points | Breadboard |
| 9 | 1 | Boost | 3V to 5V | Boost Converter |
| 10 | 1 | S1 |  | Power Switch |
| 11 | 1 | HW-107 |  | Battery Management Module |
| 12 | 1 | B1 | 3.7V 300 mAh | Li-ion Battery |


### Hardware Documentation

- Circuit diagram: `hardware/Circuit_Map.png`
- Bill of materials: `hardware/BOM.csv`
- Image of materials: `images/parts-staged.jpg`

---

## Software

The Arduino firmware:

- Startup sequence to indicate function
- Reads distance measurements from the HC-SR04 sensor
- Activates visual alerts when an object is detected

Firmware location:

```
<!-- firmware/BattleBuddy_S_0.1/BattleBuddy_S_0.1.ino -->
```

---

## Design Notes

This version focuses on design validation before committing to a PCB design.

Changes:
- Uses bare microprocessor instead of Arduino UNO R3
- Adds battery operation with USB charging, allowing alpha testing
- Swaps buzzer for a more nuanced LED signaling system: uses 2 colors to show distance to detection

Limitations:
- Only breadboarded, so not rugged enough for beta testing
- Only shows detection in current direction
- Not optimized for a final embedded product
- Sub-optimal switch choice.  I used what I had.
- Indicator LED is run nondestructively, but this is not the best user experience  (see `images/indicator-installed.png`)

---

## Lessons Learned

This prototype validated:

- Can perform it's basic function in actual use (Alpha testing was successful!)
- Bare microprocessor design works
- Warning feedback mechanisms were improved
- Suitable for wearing as a VR headset accessory