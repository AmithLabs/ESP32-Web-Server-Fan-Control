# ESP32 Web Server Fan Control

[![Watch the video](https://img.youtube.com/vi/YOUR_VIDEO_ID/0.jpg)](https://youtu.be/YOUR_VIDEO_ID)

📺 **Watch the Full Build Video on YouTube**
https://youtu.be/YOUR_VIDEO_ID

---

## Project Overview

This project demonstrates a simple and attractive **ESP32 Web Server Fan Control System** using WiFi and a relay module.

The ESP32 creates its own **WiFi Access Point (AP Mode)**, so no external WiFi router is required. A mobile phone can connect directly to the ESP32 WiFi and control the fan using a browser-based interface.

The system provides a professional mobile-friendly control page with:

* TURN ON button
* TURN OFF button
* RGB LED status indication

When the fan is OFF, the onboard NeoPixel RGB LED glows **RED**.

When the fan is ON, the onboard NeoPixel RGB LED glows **GREEN**.

This project is ideal for learning **ESP32 Web Server, Relay Control, Smart Home Basics, and IoT System Design**.

The full build process is available on the **AmithLabs YouTube channel**.

---

## Main Features

* ESP32 WiFi Access Point Mode (No Router Needed)
* Mobile Browser Fan ON/OFF Control
* Relay-Based Safe Fan Switching
* Onboard RGB LED Status Indicator
* Attractive Responsive Web Interface
* Smartphone Friendly UI
* Simple Smart Home Automation Project

---

## Hardware Components

* ESP32-S3 Dev Board
* 1 Channel Relay Module
* DC Fan (Recommended for Testing)
* Power Supply
* Jumper Wires
* Mobile Phone
* Adafruit NeoPixel Library

---

## Pin Configuration

| Component       | ESP32 Pin |
| --------------- | --------- |
| Relay Module IN | GPIO 4    |
| Onboard RGB LED | GPIO 48   |

---

## System Operation

1. ESP32 powers on and creates its own WiFi network.
2. Mobile phone connects to the ESP32 WiFi:
   **ESP32_FAN_CONTROL**
3. User opens browser and enters:
   **192.168.4.1**
4. A web control page appears with ON and OFF buttons.
5. Pressing **TURN ON** activates the relay and turns the fan ON.
6. RGB LED changes to **GREEN** indicating active status.
7. Pressing **TURN OFF** deactivates the relay and turns the fan OFF.
8. RGB LED changes to **RED** indicating standby status.

---

## Arduino Code

The complete ESP32 program is included in this repository:

```text
ESP32_Web_Server_Fan_Control.ino
```

This code controls:

* WiFi Access Point Creation
* Web Server Interface
* Relay ON/OFF Control
* NeoPixel RGB LED Status
* Mobile Browser UI

---

## Project Images

```text
project-preview.jpg
circuit-diagram.jpg
```

---

## Required Library

Install the following library from Arduino IDE:

```text
Adafruit NeoPixel
```

Library Path:

```text
Sketch → Include Library → Manage Libraries
```

Search:

```text
Adafruit NeoPixel
```

---

## WiFi Access Point Details

```text
SSID: ESP32_FAN_CONTROL
Password: 12345678
Default IP: 192.168.4.1
```

---

## YouTube Channel

This project was created for the **AmithLabs** YouTube channel.

Subscribe for more DIY electronics, smart automation projects, and creative engineering builds.

---

## Disclaimer

This project is created for **educational and demonstration purposes only**.

Please use proper safety precautions when working with relays, power supplies, and electrical loads.

For beginners, it is recommended to test first using a low-voltage DC fan before working with higher voltage appliances.

---

## Author

**Amith Wijekoon**
Automation & Electrical Engineering Specialist
Creator of the **AmithLabs** YouTube Channel
