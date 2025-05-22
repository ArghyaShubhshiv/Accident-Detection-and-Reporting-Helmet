# 🪖 Accident Detection and Reporting Helmet – Upgraded Smart Safety System

[![Arduino](https://img.shields.io/badge/Platform-Arduino-blue?logo=arduino)](https://www.arduino.cc/)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Language: C++](https://img.shields.io/badge/Made%20with-C++-brightgreen)](https://www.arduino.cc/reference/en/)

**Accident Detection and Reporting Helmet** is a next-gen Arduino-powered smart helmet designed to detect road accidents in real-time and automatically notify emergency contacts via SMS with live GPS coordinates. It incorporates false-positive mitigation, a cancel window, multi-contact alerting, and optional voice alerts — offering a reliable, life-saving safety system for solo riders.

🏆 *Winner of Best Innovation Project at Alpha Hacks 2021*  
🥉 *Third Prize at Technovity 2020*

---

## 🧠 Features (Upgraded)

- 📉 **Rolling Average Acceleration Detection** to reduce false triggers
- ⏱️ **10-Second Cancel Timer** before SOS is sent (manual override button)
- 📍 **GPS Fix Verification** to avoid sending null/zero coordinates
- 📡 **SMS Alerts to Multiple Emergency Contacts**
- 🔋 **Battery Voltage Pin Ready** (for low battery alert logic)
- 🔴🟢🔄 **LED Indicators** for alert, safe, and GPS acquiring states
- 📣 **Voice Playback Compatible** via DFPlayer Mini (e.g., “Please help!”)
- 🧱 **Modular Code Structure** for easy upgrades and debugging

---

## 🛠️ Hardware Components

| Component              | Pin Used             | Function                               |
|------------------------|----------------------|----------------------------------------|
| Arduino UNO/Nano       | —                    | Microcontroller                         |
| Accelerometer (3-Axis) | A3 (X), A4 (Y), A1 (Z)| Detects sudden movement                |
| GSM Module (SIM800L)   | TX: D2, RX: D3       | Sends SMS with GPS data                |
| GPS Module             | TX: D11, RX: D10     | Acquires latitude and longitude        |
| Push Button            | D13                  | Cancels false SOS alerts               |
| Buzzer                 | D4                   | Alerts nearby people                   |
| LED (Green)            | D6                   | Safe/Ready indicator                   |
| LED (Red)              | D7                   | Accident alert indicator               |
| LED (Blinking)         | D5                   | GPS fix in progress                    |
| DFPlayer Mini (optional)| TX/RX               | Voice alert playback                   |
| Battery Voltage Input  | A5                   | Battery monitoring (optional)          |

---

## 📐 How It Works

1. Continuously monitors acceleration in X, Y, and Z axes.
2. Uses a **rolling average** to filter out false triggers.
3. If abnormal movement detected:
   - Buzzer and red LED activate.
   - 10-second window allows user to cancel alert via button.
4. If not cancelled:
   - Waits for valid GPS fix.
   - Sends live location via SMS to all configured contacts.
   - Optional: Plays voice alert using DFPlayer Mini.
5. Green LED remains on during safe/idle mode.

---

## 🚀 Setup Instructions

1. **Connect Components**
   - Wire all sensors, LEDs, buzzer, and modules as per table above.

2. **Upload Code**
   - Open `AccidentHelmet.ino` in Arduino IDE.
   - Select the board and COM port.
   - Upload the code.

3. **Test**
   - Move normally → No SOS
   - Simulate strong jerk/drop → SOS triggers after 10s unless cancelled
   - LED indicators and buzzer will guide interaction

---

## 📊 Safety Logic Summary

| Event              | Trigger            | Response                           |
|--------------------|--------------------|------------------------------------|
| Sudden Acceleration| ±30% deviation     | Start SOS Sequence                 |
| Cancel Pressed     | Button (D13)       | Abort alert, reset system          |
| Valid GPS Fix      | GPS (TinyGPS)      | Fetch lat/lon for SMS              |
| No Cancel          | Timeout after 10s  | Send SMS + play voice alert        |
| Low Battery (opt.) | A5 < threshold     | (To be added) Alert + LED flash    |

---

## 🧠 Future Enhancements

- 📱 Android companion app for contact management and live tracking
- 📡 ESP32 version with Wi-Fi/Cloud integration
- 🔋 Smart charging & battery logging system
- 🔊 Automatic voice alerts in regional languages
- 📍 Live mapping with accident logs (Google Maps integration)

---

## 👨‍🔧 Contributors

- [Rushil Rawat](https://github.com/RushilRawat)   
- [Arghya Shubhshiv](https://github.com/ArghyaShubhshiv)  
- [Arnav Bansal](https://github.com/ArnavBansal11)

---

## 📜 License

This project is licensed under the [MIT License](LICENSE).
