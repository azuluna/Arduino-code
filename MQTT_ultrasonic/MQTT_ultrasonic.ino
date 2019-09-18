
// This example uses an Adafruit Huzzah ESP8266
// to connect to shiftr.io.
//
// You can check on your device after a successful
// connection here: https://shiftr.io/try.
//
// by Joël Gähwiler
// https://github.com/256dpi/arduino-mqtt

const int TRIG_PIN = 12;
const int ECHO_PIN = 13;

#include <ESP8266WiFi.h>
#include <MQTT.h>

const char ssid[] = "BTP-Gd.A-Barat-tenant";
const char pass[] = "bandung0708";

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;
long duration, distanceCm, distanceIn;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("node1", "AccessNet", "accessnet")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  //client.subscribe("/hello");
  // client.unsubscribe("/hello");
}

/*void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
}*/

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);
  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.
  // You need to set the IP address directly.
  client.begin("128.199.141.4", net);
//  client.onMessage(messageReceived);

  connect();
}

void loop() {
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }

  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
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
    Serial.print(distanceIn);
    Serial.print("in, ");
    Serial.print(distanceCm);
    Serial.print("cm");
    Serial.println();
    client.publish("status", String(distanceCm));
  }
  delay(1000);
  //client.publish("ambil/in", String(distanceIn));
  
}



