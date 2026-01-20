# Ro_Bo_Rho 🤖

https://youtu.be/U_M9MBmvYFg?si=RW9zrAKIW7oP7VRz

Firmware for the Manual Robot participating in the **ABU Robocon 2025** competition. This project is designed for the **STM32F407** microcontroller to control a 4-wheel omnidirectional robot.

---

## 🚀 Getting Started

To open and edit the project, please locate the project file named:
> **`mark_1`**

Open this file using your preferred IDE (e.g., STM32CubeIDE, Keil uVision) to access the source code and hardware configuration.

---

## 🎮 Joystick Communication (ESP-NOW)

The robot communicates with the controller using the **ESP-NOW** protocol via the `Joy(esp32/joy)` function. 

**Dependency:**
You must install the following library for the ESP32 receiver/transmitter:
* [**espnow_ROBOT** by Knnthiti](https://github.com/Knnthiti/espnow_ROBOT.git)

---

## ⚙️ Kinematics & Movement

The robot utilizes a **4-wheel Omni-directional drive system**. It accepts velocity vectors ($V_x, V_y, V_z$) to calculate individual wheel speeds.

* **Movement Model:** The mathematical model for the kinematics is based on the Mecanum/Omni wheel theory.
* **Reference:** You can study the movement logic here: [Omni/Mecanum Wheel Tutorial](https://ecam-eurobot.github.io/Tutorials/mechanical/mecanum.html)

---
