# RC Car Project
This is the repository for all the files in our RC Car Project at BYU in Fall 2026

## The Idea
The goal of this project is to build an RC Car and controller using a microcontroller. We have the following learning goals:
  - Make a PCB
  - Apply our learning of circuits
  - Practice documentation
  - practice using git
  - Create a controller that can be used in all future projects
  - Create friendship
  - Will Simmons needs to lock in
  - Will are you even seeing this
  - Will we need you to do the math

## What is needed

| Car Componets | Controller Components |
|:----------:|:-------------:|
| Arduino Nano | Arduino ESP32 Nano |
| nRF24l01 | nRf24l01 |
| 2 3-6v Motor | L2C OLED |
| Angle Servo | Joystick |
| H-Bridge (L293D) | 4 Buttons

### How we are currently connecting our project to the microcontroller

#### Controller
| Pin | Componet | 
|:----:|:----:|
|VIN|5v Regulator|
|GND	|GND|
|3.3V|nRF24l01 VCC|
|D13	|nRF24l01 SCK|
|D12	|nRF24l01 MISO|
|D11|	nRF24l01 MOSI|
|D10|	Button 1|
|D9|	Button 2|
|D8|	nRF24l01 CSN|
|D7|	nRF24l01 CE|
|D6| Joystick button SW|
|D3|	Button 3|
|D2|	Button 4|
|A1|	Joystick VRY|
|A2|	Joystick VRX|
|A4| L2C OLED SDA|
|A5| L2C OLED SCL|

#### Car
| Pin | Componet | 
|:----:|:----:|
|VIN|	5v Regulator|
|GND|	GND|
|3.3V|	nRF24l01 VCC|
|D13|	nRF24l01 SCK|
|D12|	nRF24l01 MISO|
|D11|	nRF24l01 MOSI|
|D10|	Right Motor INPUT 1|
|D9|	Right Motor INPUT 2|
|D8|	nRF24l01 CSN|
|D7|	nRF24l01 CE|
|D6|	Servo Instructions|
|D5|	Right Motor PWM Speed|
|D4|	IR Sensor INPUT|
|D3|	Left Motor PWM Speed|
|D2|	Left Motor INPUT 3|
|D1|	Left Motor INPUT 4|

