# Pulse-Monitoring-Wrist-Band
The Pulse Monitoring Wrist Band, based on ESP32 – C3, merges ancient Ayurvedic NADI PARIKSHAN with modern tech. Worn like a watch on the left hand, it captures Vata, Pitta, and Kapha waveforms in real time. The GUI is used for accurate and insightful evaluations of the obtained waveforms.
# Components required and their description
1) MAX30102 Pulse Oximeter and Heart Rate Sensor
<img src="https://github.com/AshayAtkar/Pulse-Monitoring-Wrist-Band/assets/120382546/14a8c619-8f75-4cfe-8c33-fa848e53ca23" alt="Image" width="250">


This is the sensing unit of the watch. MAX30102 is an integrated pulse oximeter and heart rate sensor which works on the principle of Photoplethysmography (PPG). The IC in the above module consists of two LED's (Red and IR), a photodiode and low noise analog signal processing circuit. The LED's emit light towards the skin and the photodetector detects the intensity of light which is reflected back towards it. Dissolved Oxygen in the blood plays a crutial role in deciding the amount of light absorbed by the flowing blood. Using this the dissolved oxygen is measured. The oxygenated hemoglobin (HbO2) in the arterial blood has the characteristic of absorbing IR light. The redder the blood (the higher the hemoglobin), the more IR light is absorbed. As the blood is pumped through the arteries, it creates a waveform at the output of photodiode.
