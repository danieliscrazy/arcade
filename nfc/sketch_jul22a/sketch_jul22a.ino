#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;
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
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    userid += String(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println(userid);
  if (userid == "4e54722467680"){
    Serial.println("yes");
  }
  if (userid != "4e54722467680"){
    Serial.println("no");
  }
}
