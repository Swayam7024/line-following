<div align="center">

# Line Following Robot

**An Arduino robot that follows a black line with a five-sensor IR array – and searches for the line again when it loses it.**

![Arduino](https://img.shields.io/badge/Arduino-Uno%20%2F%20Nano-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![C++](https://img.shields.io/badge/C%2B%2B-Arduino-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Sensors](https://img.shields.io/badge/Sensors-5%C3%97%20IR-E74C3C?style=for-the-badge)
![Driver](https://img.shields.io/badge/Driver-L298N-34495E?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)

[Features](#features) · [Hardware](#hardware) · [Getting Started](#getting-started)

</div>

---

## Overview

This is an Arduino and infrared-sensor based robot that follows a black line. Five IR sensors read the surface under the robot, each reading is compared with a threshold to decide whether it sees black or white, and a dual H-bridge motor driver steers the two drive motors to keep the line under the centre sensor.

## Features

- Five analog IR sensors for line detection
- Adjustable black/white threshold (default `500`)
- Differential drive with PWM speed control via the motor driver enable pins
- Speeds set by two constants: `BASE_SPEED` (default `150`) and `TURN_SPEED` (default `120`)
- Movement modes: forward, turn left, turn right, stop
- **Lost-line recovery:** remembers which side the line was last seen on and keeps turning that way until it finds it again
- Live sensor states printed to the Serial Monitor (9600 baud)

## Hardware

| Component | Purpose |
|---|---|
| Arduino board (e.g. Uno / Nano) | Main controller |
| 5-channel IR sensor array (or 5 IR sensors) | Detects the black line |
| Dual H-bridge motor driver (e.g. L298N) | Drives the two motors |
| 2 × DC gear motor + wheels | Differential drive |
| Chassis, caster wheel, battery pack | Robot base and power |

## Pin Connections

| Arduino Pin | Connected To |
|---|---|
| D9 (PWM) | Motor driver ENA (left motor speed) |
| D10 (PWM) | Motor driver ENB (right motor speed) |
| D7 | Motor driver IN1 |
| D8 | Motor driver IN2 |
| D5 | Motor driver IN3 |
| D6 | Motor driver IN4 |
| A0 | IR sensor 1 (far left) |
| A1 | IR sensor 2 |
| A2 | IR sensor 3 (centre) |
| A3 | IR sensor 4 |
| A4 | IR sensor 5 (far right) |
| GND | Common ground |

> Remove the ENA / ENB jumpers on the L298N so the Arduino can control the motor speed.

## How It Works

Each loop reads all five sensors, treats a value below the threshold as black, and chooses a movement:

| Sensor condition | Action |
|---|---|
| Only the centre sensor (S3) sees black | Move forward (both motors at `BASE_SPEED`) |
| S1 or S2 sees black | Turn left (left motor reverse at `TURN_SPEED`, right forward at `BASE_SPEED`) |
| S4 or S5 sees black | Turn right (left forward at `BASE_SPEED`, right reverse at `TURN_SPEED`) |
| No sensor sees black (line lost) | Keep turning towards the side the line was last seen on; stop if it was last seen in the centre |

```mermaid
flowchart TD
    A[Read 5 IR sensors] --> B{Only S3 black?}
    B -- yes --> F[Forward, last = centre]
    B -- no --> C{S1 or S2 black?}
    C -- yes --> L[Turn left, last = left]
    C -- no --> D{S4 or S5 black?}
    D -- yes --> R[Turn right, last = right]
    D -- no --> E{Last seen side}
    E -- left --> L2[Turn left]
    E -- right --> R2[Turn right]
    E -- centre --> S[Stop]
```

## Getting Started

1. Install the [Arduino IDE](https://www.arduino.cc/en/software). No extra libraries are needed.
2. Open `line_following_robot/line_following_robot.ino`.
3. Select your board under **Tools → Board** and the correct **Port**, then click **Upload**.
4. Place the robot on the track and open the Serial Monitor at **9600 baud** to check the sensor readings (`1` = black).
5. If the robot does not detect the line reliably, adjust `threshold` in the sketch to suit your sensors and surface.
6. Tune `BASE_SPEED` and `TURN_SPEED` for your motors and track – lower speeds follow sharp curves more reliably.

## Project Structure

```
line-following/
├── line_following_robot/
│   └── line_following_robot.ino   # Line follower sketch
├── LICENSE
└── README.md
```

## Future Improvements

- Replace the rule-based steering with a PID controller using a weighted sensor position
- Add an automatic sensor calibration routine at startup
- Handle junctions and sharp turns (e.g. all sensors black)

## Author

**Swayam Khantwal** – [GitHub @Swayam7024](https://github.com/Swayam7024)

## License

This project is licensed under the MIT License – see the [LICENSE](LICENSE) file for details.
