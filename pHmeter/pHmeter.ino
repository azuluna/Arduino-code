//pHmeter A0
//Servo1 D6
//Servo2 D7

#include <AntaresESP8266HTTP.h>
#include <ESP8266WiFi.h>
#include <Servo.h>

//Antares
#define ACCESSKEY "5c66928e0960dcfd:cf4b377fdcfe1e30"
#define WIFISSID "hamdan"
#define PASSWORD ""
#define projectName "aeroponik"
#define deviceName "aeroponik"

//pH meter
#define SensorPin A0            //pH meter Analog output to Arduino Analog Input 0
#define Offset 0.3              //deviation compensate
#define samplingInterval 20
#define printInterval 800
#define ArrayLenth  40          //times of collection

//Servo
Servo servo1;
Servo servo2;

//pH meter
int pHArray[ArrayLenth];        //Store the average value of the sensor feedback
int pHArrayIndex = 0;

//Antares
AntaresESP8266HTTP antares(ACCESSKEY);

void setup(void)
{
  Serial.begin(115200);

  //Antares
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID, PASSWORD);

  //pH meter
  Serial.println("pH meter experiment!");    //Test the serial monitor

  //Servo
  servo1.attach(12);
  servo2.attach(13);
}

void loop(void)
{
  //pH meter
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue, voltage;
  if (millis() - samplingTime > samplingInterval)
  {
    pHArray[pHArrayIndex++] = analogRead(SensorPin);
    if (pHArrayIndex == ArrayLenth)pHArrayIndex = 0;
    voltage = avergearray(pHArray, ArrayLenth) * 5.0 / 1024;
    pHValue = 3.5 * voltage + Offset;
    samplingTime = millis();
  }
  if (millis() - printTime > printInterval)  //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
  {
    Serial.print("Voltage:");
    Serial.print(voltage, 2);
    Serial.print("pH value: ");
    Serial.println(pHValue, 2);
    printTime = millis();
  }


  //Servo
  int pos;

  if (pHValue >= 8) {
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      servo1.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      servo1.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
  if (pHValue <= 6) {
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      servo2.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      servo2.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }


  //Antares
  antares.add("Kadar pH", pHValue);
  antares.send(projectName, deviceName);
}


double avergearray(int* arr, int number) {
  int i;
  int max, min;
  double avg;
  long amount = 0;
  if (number <= 0) {
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if (number < 5) { //less than 5, calculated directly statistics
    for (i = 0; i < number; i++) {
      amount += arr[i];
    }
    avg = amount / number;
    return avg;
  } else {
    if (arr[0] < arr[1]) {
      min = arr[0]; max = arr[1];
    }
    else {
      min = arr[1]; max = arr[0];
    }
    for (i = 2; i < number; i++) {
      if (arr[i] < min) {
        amount += min;      //arr<min
        min = arr[i];
      } else {
        if (arr[i] > max) {
          amount += max;    //arr>max
          max = arr[i];
        } else {
          amount += arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount / (number - 2);
  }//if
  return avg;
}
