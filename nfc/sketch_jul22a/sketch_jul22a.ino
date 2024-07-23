// RST/Reset   Pin 0
// SPI SS      Pin 15
// SPI MOSI    Pin 13
// SPI MISO    Pin 12
// SPI SCK     Pin 14
// Ground      Ground
// 3.3V        3.3V

#include "config.h"
AdafruitIO_Feed *nfc = io.feed("nfc");
void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.print("Connecting to Adafruit IO");
  io.connect();
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());
}

void loop() {
  io.run();
  if (Serial.available() > 0) {  // Start of Copilot generated Code
    String signal = Serial.readStringUntil('\n');
    signal.trim(); 
    if (signal == "yes" || signal == "no") {
      bool state = (signal == "yes");
      Serial.print("Sending signal -> ");
      Serial.println(state ? "yes" : "no");
      nfc->save(state);
    }  // End of Copilot generated Code
  }
}