# ParticleMQTTblinds
This repository holds documentation and code to enable you to use a particle photon to control your standard 2" blinds.

In order to use this code you will need to add the MQTTblinds.ino, MQTT.cpp and MQTT.h to the Particle IDE as a new app.  
**Please be aware that Particle recently updated their firmware and libraries to be more compatible with arduino.  This is a great thing, but it can give you fits as it did me when flashing.  I spent too much time before I realized I was defaulting to the new 0.6.1 firmware and libraries where my photon was actually at 0.5.3.  

For this project I used a futaba S3003 and a shaft coupler with a set pin from servo city.
The servo is attached to the photon from the vin, the ground and attached for command logic on pin A4.
