// RocketTracker_ask_receiver.ino
// https://github.com/perigalacticon/RocketTracker_Project/
// 7/22/26 Created: from the RadioHead library: https://github.com/PaulStoffregen/RadioHead 
// RH_ASK "ask_receiver" example sketch and RocketTracker library: https://github.com/AllanGallop/RocketTracker  
// "RocketTracker_Receiver" example sketch for debugging purposes.
// 7/24/26 Status: Working at 1Hz transmission rate with help from radiohead-arduino google group, 
// RocketTracker GitHub project discussion page, Arduino forum Projects webpage, discussion 
// on https://www.rocketryforum.com/.
// This version appears to have an issue which requires delays after the GPS commands to function correctly.
// This version is for 2 std AVR nanos.
// 8/13/26 Status: This version does not have the delays after the GPS commands, 
// stopping GPS listening during the radio broadcast solved the problem.

#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h> // Not actually used but needed to compile
#endif

RH_ASK driver; // uses at least pin 11 on Arduino nano.

// RH_ASK driver(2000, 4, 5, 0); // ESP8266 or ESP32: do not use pin 11 or 2
// RH_ASK driver(2000, 3, 4, 0); // ATTiny, RX on D3 (pin 2 on attiny85) TX on D4 (pin 3 on attiny85),
// RH_ASK driver(2000, PD14, PD13, 0); STM32F4 Discovery: see tx and rx on Orange and Red LEDS

//Mission Playload
struct payloadStruct {
  float longitude = 0.0;
  float latitude  = 0.0;
  float altitude  = 0.0;
  int   sats      = 0;
} Payload;

void setup()
{
#ifdef RH_HAVE_SERIAL
  Serial.begin(9600);	  // Debugging only
#endif
  if (!driver.init())
#ifdef RH_HAVE_SERIAL
    Serial.println("init failed");
#else
    ;
#endif
  Serial.println("start receiver");
}

void loop()
{
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);
  if (driver.recv(buf, &buflen)) // Non-blocking
  {
    memcpy(&Payload, buf, sizeof(Payload));
    //    Serial.println("test");
    //    Serial.print(Payload.latitude,6);
    //    Serial.print(",");
    //    Serial.print(Payload.longitude,6);
    //    Serial.print(",");
    //    Serial.print(Payload.altitude,6);
    //    Serial.print(",");
    //    Serial.print(Payload.sats);
    //    Serial.print("\r\n");

    // for plot:
    Serial.print(Payload.latitude, 6);
    Serial.print(",");
    Serial.println(Payload.longitude, 6);

  }

  // This section for sending simple text:
  //=================================================
  //  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  //  uint8_t buflen = sizeof(buf);
  //
  //  if (driver.recv(buf, &buflen)) // Non-blocking
  //  {
  //    int i;
  //
  //    // Message with a good checksum received, dump it.
  //    driver.printBuffer("Got:", buf, buflen);
  //  }

}
