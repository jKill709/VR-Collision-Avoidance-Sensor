# Arduino-Based Wall Sensor

![Arduino Prototype](images/assembled-front.jpg)

## Purpose

Use the Arduino microcontroller development platform to investigate the creation of an embedded device to prevent physical collisions while using VR headsets.

This prototype was developed to validate the core concept before transitioning to a standalone ATmega328P implementation.

---

## Architecture

- Ultrasonic sensor module (HC-SR04) to measure distance
- LED and passive speaker to alert the VR user of detected objects
- Arduino UNO R3 for logic and control
- Potentiometer to adjust detection sensitivity for development
- Serial output over USB for validation and debugging

---

## Hardware

### Components

| Item | Qty | Reference | Value | Description |
|:---|:---:|:---:|:---:|---:|
| 1 | 1 |  |  | Arduino UNO R3 Development Board |
| 2 | 1 | HC-SR04 |  | Ultrasonic Sensor |
| 3 | 1 | BZ1 |  | Passive Buzzer |
| 4 | 1 | D1 | 5V | Green LED (ON/OFF Indicator) |
| 5 | 1 | D2 | 5V | Red LED (Warning LED) |
| 6 | 1 | Pot1 | 10K Ohms | Potentiometer |
| 7 | 2 | R1, R2 | 220 Ohms | Current-Limiting Resistor|
| 8 | 1 |  | 170 Tie-Points | Breadboard |


### Hardware Documentation

- Circuit diagram: `hardware/Circuit_Map.png`
- Bill of materials: `hardware/BOM.csv`

---

## Software

The Arduino firmware:

- Reads distance measurements from the HC-SR04 sensor
- Compares distance against an adjustable warning threshold
- Activates visual and audible alerts when an object is detected
- Provides serial output for testing and calibration

Firmware location:

```
src/Wall_Sensor_0.1.3.ino
```

---

## Design Notes

This version prioritized rapid development and concept validation.

Advantages:
- Fast iteration using the Arduino ecosystem
- Easy debugging through USB serial output
- Minimal hardware setup

Limitations:
- Requires power cord
- Dependent on Arduino development board
- Not optimized for a final embedded product

---

## Lessons Learned

This prototype validated:

- Ultrasonic sensing was suitable for collision detection
- Warning feedback mechanisms were effective
- A standalone microcontroller implementation was feasible
- A threshold value was determined by using potentiometer and serial output, and can now be hardcoded in the next iteration