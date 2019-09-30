#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2 // Data wire is plugged into port 9 on the Arduino
#define precision 12 // OneWire precision Dallas Sensor
//int sen_number = 0; // Counter of Dallas sensors

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature.
DeviceAddress T1, T2; // arrays to hold device addresses
void setup(void)
{
  Serial.begin(9600); //Start serial port
  Serial.println("Dallas Temperature IC Control Library");
  // Start up the library
  sensors.begin();
  // locate devices on the bus
  Serial.print("Found: ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" Devices.");
  if (!sensors.getAddress(T1, 0)) Serial.println("Not Found Sensor 1");
  if (!sensors.getAddress(T2, 1)) Serial.println("Not Found Sensor 2");
  // set the resolution to 12 bit per device
  sensors.setResolution(T1, precision);
  sensors.setResolution(T2, precision);
}
// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
// function to print the temperature for a device
void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print(tempC);
}
// function to print a device's resolution
void printResolution(DeviceAddress deviceAddress)
{
}

void printData(DeviceAddress deviceAddress)
{
  printTemperature(deviceAddress);
  Serial.println();
}

void loop(void)
{
  sensors.requestTemperatures();
  Serial.print("Suhu 1: ");
  printData(T1);
  Serial.print("Suhu 2: ");
  printData(T2);
  delay(5000);
}
