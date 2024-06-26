# Pulse-Monitoring-Wrist-Band
The Pulse Monitoring Wrist Band, based on ESP32 – C3, merges ancient Ayurvedic NADI PARIKSHAN with modern tech. Worn like a watch on the left hand, it captures Vata, Pitta, and Kapha waveforms in real time. The GUI is used for accurate and insightful evaluations of the obtained waveforms.
# Components required and their description
1) MAX30102 Pulse Oximeter and Heart Rate Sensor
<img src="https://github.com/AshayAtkar/Pulse-Monitoring-Wrist-Band/assets/120382546/14a8c619-8f75-4cfe-8c33-fa848e53ca23" alt="Image" width="250">


This is the sensing unit of the watch. MAX30102 is an integrated pulse oximeter and heart rate sensor which works on the principle of Photoplethysmography (PPG). The IC in the above module consists of two LED's (Red and IR), a photodiode and low noise analog signal processing circuit. The LED's emit light towards the skin and the photodetector detects the intensity of light which is reflected back towards it. Dissolved Oxygen in the blood plays a crutial role in deciding the amount of light absorbed by the flowing blood. Using this the dissolved oxygen is measured. The oxygenated hemoglobin (HbO2) in the arterial blood has the characteristic of absorbing IR light. The redder the blood (the higher the hemoglobin), the more IR light is absorbed. As the blood is pumped through the arteries, it creates a waveform at the output of photodiode.

2) XIAO ESP32 C3
<img src="https://github.com/AshayAtkar/Pulse-Monitoring-Wrist-Band/assets/120382546/468d889c-c00a-4d7c-a1ad-266eb8a485dd" alt="Image" width="350">

ESP32 C3 is a microcontroller board. It consists of a powerful 32-bit RISC-V processor with built in WiFi and Bluetooth Low Energy (BLE) connectivity. It is used in this project because of its compact size. It collects data from the three sensors using the PCA9548 multiplexer and sends the data to Firebase as well as the GUI. It also consists of an inbuilt battery charging IC which makes this product rechargeable.

3) PCA9548 Multiplexing IC
<img src="https://github.com/AshayAtkar/Pulse-Monitoring-Wrist-Band/assets/120382546/d3c1cef9-1169-4d3a-ba40-fceef5df3caf" alt="Image" width="250">

The PCA9548 is an integrated circuit that acts as an 8-channel I2C multiplexer. It allows us to connect up to 8 I2C devices to a single I2C bus on our microcontroller. The I2C device which needs to be communicated is choosen using a 8 bit command given to the multiplexer IC, which then routes the I2C signals to the selected device. This is useful when the I2C addresses of the connected devices are same. In this project 3 same sensors with same addresses are used, therefore I2C multiplexer IC is required.

4) FPC connector and cable
<img src="https://github.com/AshayAtkar/Pulse-Monitoring-Wrist-Band/assets/120382546/5520d8df-a6e0-4006-ae35-bd2e5bae2222" alt="Image" width="150">
<img src="https://github.com/AshayAtkar/Pulse-Monitoring-Wrist-Band/assets/120382546/3fcca4b1-3366-4bce-9337-e6d5bdc4fa1c" alt="Image" width="150">

Flexible printed cable (FPC) is a compact and efficient way to make connections between PCB's. In this project we have made two PCB designs. One for holding the three sensors on the radial artery (below the wrist) and the other for holding the ESP32 C3 and I2C multiplexer IC on the top of the wrist. The FPC cable is used to make a efficient connection between these two PCB's.

5) Rechargeable Lithium Ion Battery (3.7V, 450mAH) (To provide power to the required components)
<img src="https://github.com/AshayAtkar/Pulse-Monitoring-Wrist-Band/assets/120382546/4635044f-c8c7-43e9-b66c-adca65898e13" alt="Image" width="250">

6) Switch (For switching on the watch)
<img src="https://github.com/AshayAtkar/Pulse-Monitoring-Wrist-Band/assets/120382546/dfa8b2c9-638e-4caf-be58-173aea3fbe71" alt="Image" width="250">

# PCB 3D Images

1) Top PCB
<img src="https://github.com/AshayAtkar/Pulse-Monitoring-Wrist-Band/assets/120382546/df95613b-bb2d-4b77-b86e-02ae88480e36" alt="Image" width="250">
<img src="https://github.com/AshayAtkar/Pulse-Monitoring-Wrist-Band/assets/120382546/dcb9d047-8098-4703-b33d-59864ab3093c" alt="Image" width="250" height="396">

2) Bottom PCB
<img src="https://github.com/AshayAtkar/Pulse-Monitoring-Wrist-Band/assets/120382546/30460564-0564-406d-bcfe-df796ec0756a" alt="Image" width="250">
<img src="https://github.com/AshayAtkar/Pulse-Monitoring-Wrist-Band/assets/120382546/f52f525b-f0b2-4ec0-af23-8cba8cb12e8d" alt="Image" width="250" height="291">

# Some Images of Pulse-Monitoring-Wrist-Band

1) Working Demonstration
<img src="https://github.com/AshayAtkar/Pulse-Monitoring-Wrist-Band/assets/120382546/4991f3b0-efbb-4064-960d-0f79f88188a9" alt="Image" width="350">

2) Final Product
<img src="https://github.com/AshayAtkar/Pulse-Monitoring-Wrist-Band/assets/120382546/0bb63e0c-a251-48cf-9a13-61f0b7db5b5c" alt="Image" width="650">
