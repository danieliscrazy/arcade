#include <SPI.h>
#include <MFRC522.h>
#include "config.h"

#define RST_PIN 4
#define SS_PIN 5

MFRC522 mfrc522(SS_PIN, RST_PIN);
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
  SPI.begin();
  mfrc522.PCD_Init();
  delay(4);
  mfrc522.PCD_DumpVersionToSerial();
  Serial.println(F("Scan for UID."));
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!mfrc522.PICC_IsNewCardPresent()) {

    return;
  }
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  String userid;
  String last;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    userid += String(mfrc522.uid.uidByte[i], HEX);
  }
  if (userid == last)
    Serial.println("same");
  return;
  Serial.println(userid);
  if (userid == "4e54722467680") {
    Serial.print("sending value -> ");
    Serial.println("yes");
    nfc->save("yes");
  }
  if (userid != "4e54722467680") {
    Serial.print("sending value -> ");
    Serial.println("no");
    nfc->save("no");
  }
  last = userid;
}