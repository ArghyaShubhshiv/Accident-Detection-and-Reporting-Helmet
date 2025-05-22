# 🪖 Accident Detection and Reporting Helmet – Arduino-Powered Road Safety Gear

[![Arduino](https://img.shields.io/badge/Platform-Arduino-blue?logo=arduino)](https://www.arduino.cc/)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Language: C++](https://img.shields.io/badge/Made%20with-C++-brightgreen)](https://www.arduino.cc/reference/en/)

**Accident Detection and Reporting Helmet** is an Arduino-based smart safety helmet designed to automatically detect bike or motorcycle accidents and immediately alert emergency services via SMS. The system combines accelerometer-based motion analysis, GPS-based location tracking, and GSM messaging for real-time accident reporting — providing crucial assistance when seconds matter.

🏆 *Winner of Best Innovation Project at Alpha Hacks 2021*  
🥉 *Third Prize at Technovity 2020*

---

## 🧠 Features

- 📉 **Accident Detection** using 3-axis analog accelerometer
- 📍 **GPS Coordinates** sent via SMS using GSM module
- 🔔 **Emergency Buzzer** alerts nearby pedestrians
- 📩 **Automated Emergency SMS** to police or guardian number
- ⛔ **False Positive Control** using button-based manual override
- 🧮 **Three-Point Acceleration Check** for reliability

---

## 🛠️ Hardware Components

| Component            | Pin Used             | Function                            |
|----------------------|----------------------|-------------------------------------|
| Arduino UNO/Nano     | —                    | Microcontroller                     |
| Accelerometer (3-Axis)| A1 (Z), A3 (X), A4 (Y)| Measures impact/jerk                |
| GSM Module (SIM800L) | TX: D2, RX: D3       | Sends SMS alerts                    |
| GPS Module           | TX: D11, RX: D10     | Fetches real-time location          |
| Push Button          | D13                  | Manual cancel/reset SOS             |
| Buzzer               | D4                   | Audible alert for nearby help       |

---

## 📐 Working Logic

1. Helmet continuously monitors acceleration from X, Y, and Z axes.
2. If sudden large deviation is detected (possible accident), it rechecks to eliminate noise.
3. On second confirmation, it buzzes and waits briefly.
4. If not cancelled manually using the button, it:
   - Fetches current GPS coordinates.
   - Sends an emergency SMS with location to the nearest police station (or guardian).
5. Buzzer continues to sound as a distress signal.

---

## 🚀 Setup Instructions

1. **Connect All Components**  
   Wire up accelerometer, GPS, GSM, buzzer, and button as per the table above.

2. **Upload the Code**  
   - Open `Helmet_Accident_Alert.ino` in Arduino IDE  
   - Select the appropriate board and COM port  
   - Upload and power up the system

3. **Testing Flow**  
   - Move the helmet gently – no alert should trigger  
   - Apply a sharp movement or drop – system should detect  
   - Press button during countdown to cancel alert  
   - If not cancelled, system will send SMS to pre-configured number

---

## 🛡️ Safety Logic Chart

| Trigger Type        | Sensor Used         | Threshold/Condition         | Action Taken                 |
|---------------------|---------------------|-----------------------------|------------------------------|
| Sudden Impact       | Accelerometer       | ±30% deviation from average | Alert sequence triggered     |
| GPS Fix             | GPS Module          | Auto-acquire if available   | Coordinates fetched          |
| Manual Cancel       | Button (D13)        | LOW input on pin            | Stops buzzer, cancels alert  |
| SMS Alert           | GSM Module (SIM800) | On valid GPS + no cancel    | Sends message to `+91100`    |

---

## 🛠️ Future Enhancements

- 📲 Add voice feedback module (DFPlayer Mini)
- 📊 Upload data logs to cloud (via ESP8266)
- 🔋 Add battery monitoring system for long rides
- 📱 Mobile app to configure emergency contacts and alert settings
- 🌙 Nighttime visibility LEDs for added safety

---

## 👨‍🔧 Authors & Contributors

- [Arghya Shubhshiv](https://github.com/ArghyaShubhshiv)
- [Rushil Rawat](https://github.com/RushilRawat)
- [Arnav Bansal](https://github.com/ArnavBansal11)

---

## 📜 License

This project is licensed under the [MIT License](LICENSE).
