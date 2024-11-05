# KeyboardPCB
The project aimed to create a Human Interface Device (HID) using an Arduino microcontroller with the Atmega32U4 chip. The keyboard was to be used for additional keys to a laptop to allow the user easier access to certain characters; adding a numeric numpad. As computers use drivers to understand what external USB devices are trying to communicate, this device was designed and programmed to send ASCI characters through the USB2.0 protocol.

## Comarpison of Atmega328 vs Atmega32U4
Due to HID devices requiring a USB interface a microcontroller using the Atmega 32U4 chip was selected. By comparing the two functional block diagrams below of the two chips, the Atmega 32U4 contains the USB2.0 block that allows the computer to directly communicate via USB to the chip and therefore not requiring a USB-to-Serial converter on board.  

## 3D Model
![keyboard_3dmodel](https://github.com/user-attachments/assets/915baa8a-e792-4141-91b3-1509ea2280c7)
## Schematics
![keyboard_schem](https://github.com/user-attachments/assets/707a8e8f-b024-4502-9650-743d91452241)
## Layout
![keyboard_layout](https://github.com/user-attachments/assets/203e8a48-c484-4385-9271-c221541907dd)
