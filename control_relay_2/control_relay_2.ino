#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

//Relay
#define relay_1 5
#define relay_2 4

//Firebase
#define FIREBASE_HOST "vertical-garden-project.firebaseio.com"
#define FIREBASE_AUTH "FIHGNRi2tFbyezMZrSFjGbErax28MdTDA839h6wY"
#define WIFI_SSID "Wifi Belakang"
#define WIFI_PASSWORD "bismillahaja"

//Relay
String air_1;

void setup(void)
{
  Serial.begin(115200); //Start serial port

  //Relay
  pinMode(relay_1, OUTPUT);
  pinMode(relay_2, OUTPUT);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  //Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.set("air/relay_1", "0");
  Firebase.set("air/relay_2", "0");

}

void loop(void)
{
  air_1 = Firebase.getString("air/relay_1");
  if  (air_1 != "0") {
    Serial.println("air nyala");
    digitalWrite(relay_1, HIGH);
  }
  else {
    Serial.println("air tewas");
    digitalWrite(relay_1, LOW);
  }
  //  //Firebase Bubar
}
