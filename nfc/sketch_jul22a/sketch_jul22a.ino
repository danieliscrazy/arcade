#define UNO 14
#include "config.h"
AdafruitIO_Feed *nfc = io.feed("nfc");
int varnamehere = 1;

void setup() {
  pinMode(UNO, INPUT);
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

  if (digitalRead(UNO) == HIGH) {
    if (varnamehere == 1) {
      Serial.println(varnamehere);
      varnamehere = 0;
    }
  }
  if (digitalRead(UNO) == LOW) {
    if (varnamehere == 0) {
      Serial.println(varnamehere);
      varnamehere = 1;
    }
  }
}