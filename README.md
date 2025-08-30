
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





### <b>TeslaBlinker description</b>

This application uses the VL53L7cx TOF sensor to control the blinker lights in a Tesla model 3. A UP / DOWN gesture results in a single / double pulse that can be used to drive the blinker lights.
<br><b>The testphase</b>
![blinker](https://github.com/user-attachments/assets/9deb0a11-a677-45ee-b117-7e86621f29aa)

![theelektronics](https://github.com/user-attachments/assets/da919bb6-c1d6-4474-89f2-2d382df4f3d4)

<b>The in car build</b>

![IMG_6154b](https://github.com/user-attachments/assets/fc776640-0011-496e-9683-14ad6b671036)
![IMG_6152b](https://github.com/user-attachments/assets/e4702c61-bded-45b9-a690-68622e1b46b5)

<b>Demo with gesture</b>

https://github.com/user-attachments/assets/1f94c518-6d01-4f9e-af4d-73e38897b722

https://github.com/user-attachments/assets/84ad0aca-a5cb-4221-b0f3-957433e6dba5

https://github.com/user-attachments/assets/71a49233-56d5-4ddb-befc-c8cad62d33c4

<b> Schematic </b>
<img width="2628" height="1354" alt="TeslaBlinkerCircuit" src="https://github.com/user-attachments/assets/cd7e70f9-ed8b-44d6-ad95-f11c7ae21a26" />

The application uses the following default serial settings:

  - Baud Rate: 460800
  - Data Bits: 8
  - Parity: None
  - Stop Bits: 1

### <b>Hardware and Software environment</b>

  - TeslaBlinker runs on STM32 Nucleo board with VL53L7cx sensor connected
  - If you power the Nucleo board via USB 3.0 port, check that you have flashed the last firmware version of
    the ST-Link v2 on the Nucleo board. In order to flash the latest firmware version of the 
	ST-Link v2, you can use the STM32 ST Link Utility.
ADDITIONAL_COMP : VL53L7CX https://www.st.com/en/product/vl53l7cx.html

### <b>How to use it ?</b>

To ensure the program operates correctly, execute the following steps:
 - WARNING: before opening the project with any toolchain be sure your folder
   installation path is not too in-depth since the toolchain may report errors
   after building.
 - Open STM32CubeIDE.
 - Rebuild all files and load your image into target memory.
 - Run the example.
 - Alternatively, you can download the pre-built binaries in "Binary" 
   folder included in the distributed package.

### <b>License</b>

G-DC
This software is provided AS-IS.

</div>
