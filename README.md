
# 🚘 TeslaBlinker – Gesture-Controlled Blinkers for Tesla Model 3 Highland

**TeslaBlinker** is a gesture-based turn signal controller designed for the Tesla Model 3 Highland.  
It restores intuitive, eyes‑free blinker operation after Tesla removed the traditional stalk, replacing it with steering wheel touch buttons.

---

## 📌 Why TeslaBlinker?

Tesla’s minimalist design is beautiful, but the removal of the blinker stalk introduces safety concerns — especially in regions with frequent roundabouts (e.g., Europe).  
Touch buttons require visual attention and disrupt natural driving flow. TeslaBlinker solves this by enabling **up/down hand gestures** to trigger blinkers, keeping your eyes on the road.

---

## ✋ Features

- **Gesture Recognition** – Detects up/down hand movements near the steering wheel
- **Time-of-Flight Sensing** – Uses VL53L7CX ToF sensor for precise motion tracking
- **STM32 Control** – Processes gestures and sends commands to the Tesla blinker interface
- **Non-Intrusive** – Works alongside Tesla’s existing controls
- **Fast Response** – 20 Hz scanning for real-time activation

---

## 🛠 Hardware

| Component | Purpose |
|-----------|---------|
| **VL53L7CX ToF Sensor** | 8×8 zone distance sensing via I²C |
| **STM32F401RE Nucleo Board** | Gesture processing & control logic |
| **Testars Button Interface** | Sends blinker commands to Tesla |
| **Wiring & Mounting** | Secure installation near steering wheel |

---

## ⚙️ How It Works

1. **Sensor Grid** – The VL53L7CX captures an 8×8 depth map of the driver’s hand area.
2. **Gesture Detection** – A state machine processes movement:
   - `GESTURE_STATE_WAIT_ENTRY` – Wait for hand entry
   - `GESTURE_STATE_TRACK` – Track movement direction
   - Outputs: `GESTURE_NONE`, `GESTURE_UP`, `GESTURE_DOWN`
3. **Signal Trigger** – STM32 sends the appropriate blinker signal via the Testars interface.

---

## 🎥 Demo Videos

- [Basic Gesture Activation](https://cdn.hackaday.io/files/2039078723957088/482703793-1f94c518-6d01-4f9e-af4d-73e38897b722.mp4)  
- [Real-Time Blinker Control](https://cdn.hackaday.io/files/2039078723957088/482703765-84ad0aca-a5cb-4221-b0f3-957433e6dba5.mp4)  
- [Subtle Gesture Recognition](https://cdn.hackaday.io/files/2039078723957088/482703737-71a49233-56d5-4ddb-befc-c8cad62d33c4.mp4)  

---

## 🚀 Installation

1. **Mount the VL53L7CX sensor** near the steering wheel where it can detect hand gestures.
2. **Connect the sensor** to the STM32F401RE via I²C.
3. **Wire the STM32** to the Testars button interface.
4. **Flash the firmware** to the STM32 (source code in `/src`).
5. **Test gestures** with the car in accessory mode before driving.

---

## 📄 License

This project is released under the [MIT License](LICENSE).

---

## 🙌 Acknowledgements

- Inspired by the need for safer, more intuitive controls in modern EVs
- Built with STM32, VL53L7CX, and the Testars interface
- Project page: [Hackaday.io – TeslaBlinker](https://hackaday.io/project/203907-tesla-blinker)


