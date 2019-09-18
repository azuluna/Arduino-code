#include <PubSubClient.h>
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define FIREBASE_HOST "ltfproject.firebaseio.com"
#define FIREBASE_AUTH "HBHG9XZogcUe90vWAwZH2KqSESe4ldylWnbcrOSE"  
#define WIFI_SSID "Wifi Belakang"
#define WIFI_PASSWORD "bismillahaja"

const long utcOffsetInSeconds = 25200;
char daysOfTheWeek[7][12] = {"Ahad", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "time.windows.com", utcOffsetInSeconds);

const int TRIG_PIN = 12;
const int ECHO_PIN = 13;

unsigned long lastMillis = 0;
long duration, distanceCm, distanceIn;
  
void setup() {
  Serial.begin(9600);
  WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println ("");
  Serial.println ("WiFi Connected!");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);
  timeClient.begin(); 
}
void loop() {
  timeClient.update();
  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  //Serial.println(timeClient.getFormattedTime());

  
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN,HIGH);
 
  // convert the time into a distance
  distanceCm = duration / 29.1 / 2 ;
  distanceIn = duration / 74 / 2;
 
  if (distanceCm <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distanceCm);
    Serial.print("cm");
    Serial.println();
  }

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["tinggi"] = distanceCm;
  Firebase.push("Hydroponic", root);
  
  delay(1000);
}
