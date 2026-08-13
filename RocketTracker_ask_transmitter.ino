// RocketTracker_ask_transmitter.ino
// https://github.com/AllanGallop/RocketTracker
// 7/22/26 Created: from the RH_ASK "ask_transmitter" example sketch
// and RocketTracker "RocketTracker_Transmitter" example sketch for debugging purposes.
// 7/24/26 Status: Working at 1Hz transmission rate with help from
// radiohead-arduino google group, RocketTracker GitHub project discussion page,
// Arduino forum Projects webpage, discussion on https://www.rocketryforum.com/.
// This version appears to have an issue which requires delays
// after the GPS commands to function correctly.
// This version for 2 std AVR nanos.
// 8/13/26 Status: This version does not have the delays after the GPS commands, 
// stopping GPS listening during the radio broadcast solved the problem.

#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h> // Not actually used but needed to compile
#endif

RH_ASK driver;  // uses at least pin 12 on Arduino nano.
// RH_ASK driver(2000, 4, 5, 0); // ESP8266 or ESP32: do not use pin 11 or 2
// RH_ASK driver(2000, 3, 4, 0); // ATTiny, RX on D3 (pin 2 on attiny85) TX on D4 (pin 3 on attiny85),
// RH_ASK driver(2000, PD14, PD13, 0); STM32F4 Discovery: see tx and rx on Orange and Red LEDS

TinyGPSPlus gps;
//SoftwareSerial serialGPS(4, 5); //TXpin, RXpin
SoftwareSerial serialGPS(7, 8); //TXpin, RXpin

//Mission Playload
struct payloadStruct {
  float longitude = 0.0;
  float latitude  = 0.0;
  float altitude  = 0.0;
  int   sats      = 0;
} Payload;

//Transmitter Buffer
byte txBuffer[sizeof(Payload)] = {0};
int sats;

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

  serialGPS.begin(9600);
  Payload.longitude = 12.345;
  Payload.latitude = 67.890;
  Payload.altitude = 11.123;
  Payload.sats = 8;
  Serial.println("start transmitter");
}

void loop()
{
  while (serialGPS.available() > 0) {
    gps.encode(serialGPS.read());
    //    Serial.println("gps read");
    if (gps.location.isUpdated()) {
      Serial.println("gps updated");
      Serial.print(gps.location.lng(), 6);
      Serial.print("\t");
//      delay(100);
      Serial.print(gps.location.lat(), 6);
      Serial.print("\t");
//      delay(100);
      Serial.print(gps.altitude.meters(), 6);
      Serial.print("\t");
//      delay(200);
      Serial.println(gps.satellites.value());
//      delay(200);

      Payload.longitude = gps.location.lng();
      //      delay(100);
      Payload.latitude  = gps.location.lat();
      //      delay(100);
      Payload.altitude  = gps.altitude.meters();
      //      delay(100);
      Payload.sats      = gps.satellites.value();
      //      delay(100);
      sendPayload();

      // This section for sending simple text:
      //=================================================
      ////  const char *msg = "onetwothreefourfivesixseveneightnineteneleventwelvethirteenfourteenfifteensixteenseventeeneighteennineteentwenty";
      //  const char *msg = "onetwothreefourfivesixseveneightnineten";
      //
      //  driver.send((uint8_t *)msg, strlen(msg));
      //  driver.waitPacketSent();
      //  Serial.println("sent");

      //      Payload.longitude++;
      //      Payload.latitude++;
      //      Payload.altitude++;
      //      Payload.sats = sats++;

      delay(1000);
    }
  }
}

void sendPayload() {

  serialGPS.stopListening();

  //  Comment this out to send only simple text:
  //=================================================
  memcpy(txBuffer, &Payload, sizeof(Payload));  //Copy payload to buffer
  byte pSize = sizeof(Payload);                 //Get sizeof payload
  bool sent = driver.send((uint8_t *)txBuffer, pSize);    //Transmit buffer
  driver.waitPacketSent();  
  
  serialGPS.listen();

  Serial.println(sent ? F("sent") : F("send failed"));

  //  for (int i = 0; i < pSize; i++) {
  //    Serial.println(txBuffer[i]);
  //  }
  //=================================================

}
