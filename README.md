Note for README:

The content of this README was written entirely by me (Zoraiz). Grok AI was used solely to refine the language, eliminate grammatical and spelling errors, and enhance readability.

# Glove-Controlled Robotic Arm

First complete human-motion-to-machine project: a wearable glove with flex sensors wirelessly controls a 3D-printed robotic hand in real time.

When you bend your fingers, the robotic fingers bend exactly the same way — simple, direct, and surprisingly satisfying.

## What It Does

- Flex sensors on a glove detect finger bending  
- Arduino Nano reads sensors → converts to open/closed states  
- Sends binary data wirelessly via Bluetooth (HC-05)  
- Receiving Arduino Uno moves 5 servo motors → pulls tendons → robotic fingers move  
- Real-time mirroring of human hand gestures  

## Main Features

- 5-finger independent control  
- Wireless Bluetooth communication (HC-05 pair)  
- Simple threshold-based flex sensor detection (no complex ML)  
- Tendon-driven 3D-printed robotic hand (fishing wire + servos)  
- Bidirectional finger motion (open & close)  
- Very low latency for noticeable real-time feel  

## Hardware Components

**Glove / Transmitter side:**
- Arduino Nano  
- 5× Flex sensors (one per finger)  
- HC-05 Bluetooth module (master)  
- 9V battery + 5V regulator  
- Power switch + indicator LED  

**Robotic Hand / Receiver side:**
- Arduino Uno  
- HC-05 Bluetooth module (slave)  
- 5× MG996R servo motors  
- 3D-printed robotic hand & forearm (modified open-source design)  
- Fishing wire tendons  
- Stable 5–6V power supply (capable of handling 5 servos)  

## Repository Files

STL files for the 3D-printed robotic hand, forearm, and joints are included in this repository — print them, assemble, and use fishing wire as tendons for smooth finger motion.


**Note:** The receiver firmware is very basic and usually written separately:  
Listen for "OK" header → read 5 binary digits → map to servo angles (0° or 90°/120°)

## How to Upload & Run

**1. Glove / Transmitter Arduino Nano** (`robotic_arm.ino`)

- Connect to the glove circuit:
  - Flex sensors → A0 to A4
  - HC-05 TX → pin 3 (SoftwareSerial RX)
  - HC-05 RX → pin 2 (SoftwareSerial TX)
- Open `robotic_arm.ino` in Arduino IDE
- Board → Arduino Nano
- Select correct COM port
- Upload

**2. Robotic Hand / Receiver Arduino Uno** (separate simple code – not included here)

Typical receiver sketch structure:
```cpp
#include <Servo.h>
Servo thumb, finger1, finger2, finger3, finger4;

void setup() {
  Serial.begin(9600);
  thumb.attach(2); finger1.attach(3); finger2.attach(4);
  finger3.attach(5); finger4.attach(6);
}

void loop() {
  if(Serial.available() >= 6) {
    if(Serial.readStringUntil('\n').startsWith("OK")) {
      int s1 = Serial.read() - '0';
      int s2 = Serial.read() - '0';
      int s3 = Serial.read() - '0';
      int s4 = Serial.read() - '0';
      int s5 = Serial.read() - '0';
      
      thumb.write(s1 ? 120 : 0);
      finger1.write(s2 ? 110 : 0);
      finger2.write(s3 ? 110 : 0);
      finger3.write(s4 ? 110 : 0);
      finger4.write(s5 ? 110 : 0);
    }
  }
}
