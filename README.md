# 🚗 Obstacle Avoiding and Line Following Car

Arduino-based smart robotic car that combines obstacle avoidance using ultrasonic sensors and line following using IR sensors.
The robot uses an HC-SR04 ultrasonic sensor for obstacle detection and IR sensors for line tracking while controlling DC motors through an L293D motor driver.

---

## ✨ Features

- Obstacle avoidance using ultrasonic sensor
- Line following using IR sensors
- Autonomous navigation
- Servo-mounted ultrasonic scanning
- Differential drive movement
- Real-time serial monitor debugging

---

## 📸 Working Model

<img width="716" height="534" src="https://github.com/user-attachments/assets/3683bd69-ed57-4ce7-867a-6a71dfe53669" />


---

## 🔌 Circuit Diagram

<img width="822" height="654" src="https://github.com/user-attachments/assets/354ee3d3-9421-4e02-b4a1-0723ca685655" />


---

## 🧩 Block Diagram

<img width="990" height="576" src="https://github.com/user-attachments/assets/5d4f5e76-62c1-4cd9-a75a-a84c4b306984" />


---

## ⚙️ How It Works

### 🚘 Line Following

The robot uses two IR sensors:
- Left IR sensor
- Right IR sensor

These sensors detect the black line and guide the robot movement.

| Left Sensor | Right Sensor | Action |
|---|---|---|
| 0 | 0 | Move Forward |
| 0 | 1 | Turn Left |
| 1 | 0 | Turn Right |
| 1 | 1 | Stop |

---

### 🚧 Obstacle Avoidance

The HC-SR04 ultrasonic sensor continuously measures distance.

- If an obstacle is detected within 15 cm:
  - Robot stops
  - Servo rotates ultrasonic sensor left and right
  - Distances are compared
  - Robot moves toward the clearer path

The servo-mounted sensor enables dynamic path scanning for better navigation.

---

## 🛠️ Components Used

- Arduino Uno
- HC-SR04 Ultrasonic Sensor
- IR Sensors
- Servo Motor
- L293D Motor Driver Shield
- DC Motors
- Robot Chassis
- Wheels
- Breadboard
- Jumper Wires
- Battery

---

## 💻 Arduino Code

The complete Arduino logic is available in:

```bash
smart_car.ino
```

---

## 🚀 Applications

- Autonomous robotic navigation
- Obstacle detection systems
- Warehouse automation concepts
- Smart vehicle prototypes
- Educational robotics projects
