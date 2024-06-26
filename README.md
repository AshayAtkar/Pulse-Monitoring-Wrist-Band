# Pulse-Monitoring-Wrist-Band
The Pulse Monitoring Wrist Band, based on ESP32 – C3, merges ancient Ayurvedic NADI PARIKSHAN with modern tech. Worn like a watch on the left hand, it captures Vata, Pitta, and Kapha waveforms in real time. The GUI is used for accurate and insightful evaluations of the obtained waveforms.
# Components required and their description
1) MAX30102 Pulse Oximeter and Heart Rate Sensor
<img src="https://github.com/AshayAtkar/Pulse-Monitoring-Wrist-Band/assets/120382546/14a8c619-8f75-4cfe-8c33-fa848e53ca23" alt="Image" width="250">


This is the sensing unit of the watch. MAX30102 is an integrated pulse oximeter and heart rate sensor which works on the principle of Photoplethysmography (PPG). The IC in the above module consists of two LED's (Red and IR), a photodiode and low noise analog signal processing circuit. The LED's emit light towards the skin and the photodetector detects the intensity of light which is reflected back towards it. Dissolved Oxygen in the blood plays a crutial role in deciding the amount of light absorbed by the flowing blood. Using this the dissolved oxygen is measured. The oxygenated hemoglobin (HbO2) in the arterial blood has the characteristic of absorbing IR light. The redder the blood (the higher the hemoglobin), the more IR light is absorbed. As the blood is pumped through the arteries, it creates a waveform at the output of photodiode.

2) XIAO ESP32 C3
<img src="https://github.com/AshayAtkar/Pulse-Monitoring-Wrist-Band/assets/120382546/468d889c-c00a-4d7c-a1ad-266eb8a485dd" alt="Image" width="350">

ESP32 C3 is a microcontroller board. It consists of a powerful 32-bit RISC-V processor with built in WiFi and Bluetooth Low Energy (BLE) connectivity. It is used in this project because of its compact size. It collects data from the three sensors using the PCA9548 multiplexer and sends the data to Firebase as well as the GUI. It also consists of an inbuilt battery charging IC which makes this product rechargeable.

2) PCA9548 Multiplexing IC
<img src="https://github.com/AshayAtkar/Pulse-Monitoring-Wrist-Band/assets/120382546/d3c1cef9-1169-4d3a-ba40-fceef5df3caf" alt="Image" width="350">

The PCA9548 is an integrated circuit that acts as an 8-channel I2C multiplexer. It allows us to connect up to 8 I2C devices to a single I2C bus on our microcontroller. The I2C device which needs to be communicated is choosen using a , which then routes the I2C signals to the selected device. This is useful when you have limited I2C bus pins on your microcontroller but want to connect multiple I2C sensors or other devices.
