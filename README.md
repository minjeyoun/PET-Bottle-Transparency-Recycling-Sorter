# PET Bottle Transparency Recycling Sorter

An Arduino-based smart recycling bin that distinguishes transparent and colored PET bottles using a light sensor and an IR sensor.

## Overview

This project is a prototype smart recycling bin designed to distinguish between transparent and colored PET bottles.

The system detects the presence of a PET bottle using an IR sensor and determines its transparency using a light sensor. Based on the sensor readings, an Arduino controls a servo motor, NeoPixel LED, and LCD to provide the appropriate response.

The system can also be controlled and monitored through Bluetooth communication.

## Features

- Detects the presence of a PET bottle using an IR sensor
- Distinguishes transparent and colored PET bottles using a light sensor
- Automatically controls the recycling bin inlet with a servo motor
- Displays the detection result on an LCD
- Provides visual feedback using a NeoPixel LED
- Sends detection results through Bluetooth
- Allows the system to be activated or deactivated remotely

## Hardware

| Component | Purpose |
|---|---|
| Arduino Uno | Main microcontroller |
| HC-06 Bluetooth Module | Bluetooth communication |
| Light Sensor | Detects PET bottle transparency |
| IR Sensor | Detects the presence of a PET bottle |
| NeoPixel LED | Displays system status |
| Servo Motor | Controls the recycling bin inlet |
| 16x2 I2C LCD | Displays detection results |

## Pin Configuration

| Component | Arduino Pin |
|---|---|
| NeoPixel LED | D12 |
| Bluetooth RX/TX | D7 / D6 |
| Light Sensor | D8 |
| IR Sensor | D9 |
| Servo Motor | D2 |
| I2C LCD | A4 (SDA), A5 (SCL) |

## Software

- Arduino IDE
- C/C++
- Bluetooth Serial Communication

### Arduino Libraries

```cpp
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#include <Servo.h>
#include "HX711.h"
#include <LiquidCrystal_I2C.h>

# Demonstration

The following video demonstrates the detection and sorting process for transparent and colored PET bottles.

<!-- Add your GitHub video link here -->

# System Operation
1. System Control

The system uses Bluetooth serial communication to control its operating state.

 - T → Turn the system ON
 - F → Turn the system OFF

When the system is turned off, the NeoPixel LED is turned off and the LCD backlight is disabled.

2. PET Bottle Detection

The system reads two digital sensor inputs:

int Light_S_P = digitalRead(LightsensorPin);
int Ir_S_P = digitalRead(IRsensorPin);

 - Light_S_P → Light sensor state
 - Ir_S_P → IR sensor state

The combination of these two sensor states determines the current condition.

# Detection Logic
## No PET Bottle Detected

Light Sensor = 0
IR Sensor = 1

The system remains in its normal standby state.

 - LED: OFF
 - Servo: Closed position
 - LCD: No detection message

### Transparent PET Bottle

Light Sensor = 0
IR Sensor = 0

The system identifies the object as a transparent PET bottle.

 - LED: Green
 - Servo: Opens the inlet
 - LCD: PASS Transparent
 - Bluetooth: Sends Great Job!

The system waits for approximately 6 seconds before returning to the detection process.

### Colored PET Bottle

Light Sensor = 1
IR Sensor = 0

The system identifies the object as a colored PET bottle.

 - LED: Red
 - Servo: Keeps the inlet closed
 - LCD: Block Colored
 - Bluetooth: Sends Refusal!

The system waits for approximately 3 seconds before returning to the detection process.

# System Flow

        Start
          │
          ▼
   Bluetooth Control
      T / F command
          │
          ▼
      System ON?
       /       \
     No         Yes
     │           │
     ▼           ▼
   Standby   Read Sensors
                 │
                 ▼
        ┌──────────────────┐
        │  IR Sensor Check │
        └──────────────────┘
                 │
                 ▼
        ┌──────────────────────┐
        │ Light Sensor Reading │
        └──────────────────────┘
                 │
        ┌────────┴─────────┐
        ▼                  ▼
 Transparent            Colored
    PET                    PET
        │                  │
        ▼                  ▼
 Servo Open           Servo Closed
        │                  │
        ▼                  ▼
 LCD: PASS             LCD: Block
 Transparent            Colored
        │                  │
        ▼                  ▼
 Bluetooth             Bluetooth
 "Great Job!"           "Refusal!"


## Project Structure

PET-Bottle-Transparency-Recycling-Sorter/
├── README.md
├── code.ino
└── images/
    └── hardware-prototype.jpg

 - code.ino - Arduino source code for the PET bottle detection and sorting system.
 - images/hardware-prototype.jpg - Hardware prototype before integrating the components into the recycling bin enclosure.

# Project Result

The prototype demonstrates a method for automatically distinguishing transparent and colored PET bottles using sensor-based detection.

The system integrates multiple embedded components, including sensors, Bluetooth communication, a servo motor, an LCD, and a NeoPixel LED.

  # Project Information
 - Project Name: PET Bottle Transparency Recycling Sorter
 - Platform: Arduino Uno
 - Language: C/C++
 - Project Type: Embedded System / IoT
 - Department: Department of Electronic Engineering
 - Date: June 2023
