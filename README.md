# RocketTracker_Project
GPS + Radio coms project for locating model rockets.  Ongoing project files.  Currently developed for AVR Nano MCUs.

https://github.com/perigalacticon/RocketTracker_Project/

7/22/26 Created: from the RadioHead library: https://github.com/PaulStoffregen/RadioHead 

7/24/26 Status: Working at 1Hz transmission rate with help from radiohead-arduino google group, 
RocketTracker GitHub project discussion page, Arduino forum Projects webpage, discussion 
on https://www.rocketryforum.com/.  This version appears to have an issue which requires delays after the GPS commands to function correctly.  This version is for 2 std AVR nanos.

8/13/26 Status: This version does not have the delays after the GPS commands, stopping GPS listening during the radio broadcast solved the problem.

Hardware:  

GPS:  "GoouuuTech GT-U7 Module, NEO-6M"
https://www.amazon.com/dp/B084MK8BS2?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1
Is working easily with TinyGPS++ library.

Radios:  "QCCAN 433mhz RF Transmitter and Receiver with Support ASK / OOK modulation"
https://www.amazon.com/dp/B0BLTSSMXH?ref=ppx_yo2ov_dt_b_fed_asin_title
Are working easily with the RadioHead library - based on RH_ASK driver example. 

Libraries required:
SoftwareSerial
TinyGPS++
RadioHead/RH_ASK
SPI

I got about 110m range maximum on flat ground but it started dropping out frequently around 100m.

See the RocketTracker library for the python app with map GPS location plotting.
