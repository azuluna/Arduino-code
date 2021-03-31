#include <ESP8266WiFi.h>
#include <EasyNTPClient.h>
#include <WiFiUdp.h>
#include <stdio.h>
#include <time.h>

const char *ssid     = "yudhiesriyono";
const char *password = "yudhie20";

WiFiUDP udp;

EasyNTPClient ntpClient(udp, "pool.ntp.org", (7 * 60 * 60));

long eltime, reftime, curtime;
int tahun, bulan, tanggal, jam, menit, detik;
String stamp;
void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  reftime = ntpClient.getUnixTime();
}

void loop() {
  curtime = ntpClient.getUnixTime();
  eltime = (curtime - reftime);
  time_t rawtime = ntpClient.getUnixTime();
  struct tm  ts;
  char       buf[80];

  // Format time, "ddd yyyy-mm-dd hh:mm:ss zzz"
  ts = *localtime(&rawtime);
  strftime(buf, sizeof(buf), "%A %Y-%m-%d %H:%M:%S", &ts);
  stamp = ("%s\n", buf);
  Serial.print("stamp :");
  Serial.println(stamp);
  Serial.print("elapsed :");
  Serial.print(curtime);
  Serial.print(" ");
  Serial.print(reftime);
  Serial.print(" ");
  Serial.println(eltime);
  delay(2000);
}
