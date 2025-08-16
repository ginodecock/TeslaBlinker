### <b>TeslaBlinker description</b>

This application uses the VL53L7cx TOF sensor to control the blinker lights in a Tesla model 3. A UP / DOWN gesture results in a single / double pulse that can be used to drive the blinker lights.

![blinker](https://github.com/user-attachments/assets/9deb0a11-a677-45ee-b117-7e86621f29aa)

![theelektronics](https://github.com/user-attachments/assets/da919bb6-c1d6-4474-89f2-2d382df4f3d4)

The application uses the following default serial settings:

  - Baud Rate: 460800
  - Data Bits: 8
  - Parity: None
  - Stop Bits: 1

### <b>Hardware and Software environment</b>

  - TeslaBlinker runs on STM32 Nucleo boards with VL53L7cx sensor connected
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
:::

:::
:::
