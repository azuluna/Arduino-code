#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#define Relay_1 5
#define Relay_2 4

// Set these to run example.
#define FIREBASE_HOST "ltfproject.firebaseio.com"
#define FIREBASE_AUTH "HBHG9XZogcUe90vWAwZH2KqSESe4ldylWnbcrOSE"
#define WIFI_SSID "Wifi Belakang"
#define WIFI_PASSWORD "bismillahaja"
int state_1 = 1;
int state_2 = 1;

void setup() {
  Serial.begin(115200);
  pinMode(Relay_1, OUTPUT);
  pinMode(Relay_2, OUTPUT);

  digitalWrite(Relay_1, state_1);
  digitalWrite(Relay_2, state_2);

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

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setInt("Relay_1", 0);
  Firebase.setInt("Relay_2", 0);
}
//int n = 0;
void loop() {
  state_1 = Firebase.getInt("Relay_1");
  state_2 = Firebase.getInt("Relay_2");

  // get value
  Serial.print("Relay_1: ");
  Serial.println(state_1);
  digitalWrite(Relay_1, !state_1);

  // get value
  Serial.print("Relay_2: ");
  Serial.println(state_2);
  digitalWrite(Relay_2, !state_2);

  delay(100);
}
