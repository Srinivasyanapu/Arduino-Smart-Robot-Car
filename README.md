# Arduino-Smart-Robot-Car
An advanced autonomous robot car capable of line following, human following, obstacle detection, and predefined path navigation, designed for diverse applications in healthcare, industry, and security. The robot supports both autonomous and manual Bluetooth control via a smartphone app.

# 🚗 Multi-Purpose Smart Car (Arduino) 🤖  

### 📌 **Project Overview:**  
This project presents a cost-effective autonomous robot with multiple functionalities: **line following**, **human following**, **obstacle detection**, and **predefined path navigation**, designed for real-world applications in **healthcare, industry, and surveillance**.

---
### 🎯 **Objectives:**  
- Develop an **autonomous robotic vehicle** with multi-functional navigation.  
- Implement **obstacle detection and avoidance** mechanisms.  
- Enable **Bluetooth-based manual control** for flexibility.  
- Store predefined paths in **EEPROM** for autonomous navigation.  
- Maintain cost-efficiency using low-cost components.

---
### 🛠️ **Hardware Components:**  
- **Microcontroller:** Arduino UNO (Main Controller)  
- **Motor Driver:** L293D Motor Shield (Controls DC Motors)  
- **Sensors:**   
  - IR Sensors – Line following  
  - PIR Sensor – Human detection  
  - Ultrasonic Sensor (HC-SR04) – Obstacle detection  
- **Communication Module:** Bluetooth Module (HC-05)  
- **Actuators:** SG90 Servo Motor (Sensor Rotation)  
- **Power Supply:** Two 3.7V 18650 Li-ion Batteries with TP4056 Charger  

---
### 💻 **Software Implementation:**  
- **Language:** C++ using Arduino IDE  
- **Functional Modules:**  
  - `line_follower.ino` – Tracks black line routes.  
  - `human_follower.ino` – Follows detected human movements.  
  - `obstacle_avoidance.ino` – Navigates around obstacles.  
  - `predefined_path.ino` – Follows pre-stored routes using EEPROM.  
- **Bluetooth Control:** Integrated with a smartphone application.

---
### 🧪 **Working Principle:**  
- The robot receives commands from the Bluetooth app for manual control or uses pre-programmed paths stored in EEPROM for autonomous navigation.  
- The **ultrasonic sensor** detects obstacles, and the robot adjusts its path accordingly.  
- The **line-following mode** uses IR sensors to detect and follow a black path.  
- In **human-following mode**, the PIR sensor detects motion and follows the person.  

---
### 💡 **Applications:**  
- 🏥 **Healthcare:** Medicine delivery to isolation wards.  
- 🏭 **Industry:** Automated material transport in warehouses.  
- 🚔 **Surveillance:** Security patrolling and remote monitoring.  
- 🏡 **Smart Homes:** Personal assistance and deliveries.  

---
### 🚀 **Future Enhancements:**  
- 🛰️ **GPS Integration:** For long-range navigation.  
- 🧠 **AI Path Planning:** Dynamic route adjustments.  
- 🔋 **Power Management:** Improved battery efficiency.  
- 🎥 **Camera Module:** Live video feed for remote surveillance.

---
### 🚀 **Contributions:**  
- Contributions and suggestions are welcome! Submit a pull request or open an issue to improve the project.
---
- Developed by: **[srinivas] and Team**  
- Institution: **Pragati Engineering College, Surampalem**  
- Department: **Electrical and Electronics Engineering (EEE)**  
- Year: **2024**  

**🔗 Visit the GitHub Repository:** (https://github.com/Srinivasyanapu/Smart-Robot-Car)


