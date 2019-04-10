#include <SPI.h>;
#include <MFRC522.h>;

#define pinSS 10
#define pinReset 9
MFRC522 RFID(pinSS, pinReset);
int led = 2;

void setup () {
  Serial.begin(9600);
  pinMode(led, OUTPUT);

  SPI.begin();

  RFID.PCD_Init();

  Serial.println("Scan card");

  Serial.println();
}

void loop() {
  if (! RFID.PICC_IsNewCardPresent()) {
    return;
  }

   if (! RFID.PICC_ReadCardSerial()) {
    return;
   }

   Serial.println("ID: ");
   String content = "";
   byte letter;
   for (byte i = 0; i < RFID.uid.size; i++) {
    Serial.print(RFID.uid.uidByte[i] < 0x0? " 0" : " ");
    Serial.print(RFID.uid.uidByte[i], HEX);
    content.concat(String(RFID.uid.uidByte[i] < 0x0? " 0" : " "));
    content.concat(String(RFID.uid.uidByte[i], HEX));
   }
   if(content.concat(String(RFID.uid.uidByte[1] == "xx xx xx xx"))) {
    digitalWrite (led, HIGH);
    delay(2000);
    digitalWrite(led, LOW);
   }
   else {
    digitalWrite(led, LOW);
   }
   Serial.println();
   delay(2500);
}

//KTM hamdan 80 A8 5C 90
//KTP hamdan 4 54 4E BA E2 2A 80
