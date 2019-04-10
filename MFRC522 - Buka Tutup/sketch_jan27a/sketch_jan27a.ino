#include <MFRC522.h> //memasukan Library RFID
#define pinSS 10 //inisialisasi pin SDA RFID
#define pinReset 9 //inisialisasi pin reset RFID
MFRC522 RFID(pinSS, pinReset);
int x=0;

void setup() {
SPI.begin();
RFID.PCD_Init();
Serial.begin(9600);
Serial.println("TAP KTM kamu!");
}

void loop() {
if ( ! RFID.PICC_IsNewCardPresent()) {
return;
}
if ( ! RFID.PICC_ReadCardSerial()) {
return;
}
String content = "";
byte letter;
for (byte i = 0; i < RFID.uid.size; i++)  {
content.concat(String(RFID.uid.uidByte[i] < 0x10 ? " 0" : " "));
content.concat(String(RFID.uid.uidByte[i], HEX));  //menampilkan kartu dalam hex
}
content.toUpperCase();
content.substring(1);

  if (x==0){
    if (content.substring(1) == "25 07 E0 2B") {
      x=1;
      Serial.println("Pintu Tertutup");
      delay(1000);
    }
    else{
      Serial.println("RFID Unknown");
      delay(1000);
    }
  }
  
  if (x==1){
    if (content.substring(1) == "25 07 E0 2B") {
      x=0;
      Serial.println("Pintu Terbuka");
      delay(1000);
    }
    else{
      Serial.println("RFID Unknown");
      delay(1000);
    }
  }
  delay(200);
}
