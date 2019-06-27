#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);  

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

int deviceCount = 0;
float tempC;

float sensor_tanah1 = A0; 
float output_tanah1 ;

float sensor_tanah2 = A1; 
float output_tanah2 ;

float sensor_tanah3 = A2; 
float output_tanah3 ;

void setup(void)
{
  sensors.begin();  // Start up the library
  Serial.begin(9600);
  
  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  deviceCount = sensors.getDeviceCount();
  Serial.print(deviceCount, DEC);
  Serial.println(" devices.");
  Serial.println("");
}

void loop(void)
{ 
  // Send command to all the sensors for temperature conversion
  sensors.requestTemperatures(); 
  
  // Display temperature from each sensor
  for (int i = 0;  i < deviceCount;  i++)
  {
    Serial.print("Temperature ");
    Serial.print(i+1);
    Serial.print("  : ");
    tempC = sensors.getTempCByIndex(i);
    Serial.print(tempC);
    Serial.print((char)176);//shows degrees character
    Serial.print("C  |  ");
    Serial.print(DallasTemperature::toFahrenheit(tempC));
    Serial.print((char)176);//shows degrees character
    Serial.println("F");
  }

  //sensor tanah #1
  output_tanah1 = analogRead(sensor_tanah1);
  output_tanah1 = map(output_tanah1,1023,350,0,100);
  Serial.print("Soil Humidity 1: ");
  Serial.print(output_tanah1);
  Serial.println("%");
//sensor tanah bubar

//sensor tanah #2
  output_tanah2 = analogRead(sensor_tanah2);
  output_tanah2 = map(output_tanah2,1023,350,0,100);
  Serial.print("Soil Humidity 2: ");
  Serial.print(output_tanah2);
  Serial.println("%");
//sensor tanah bubar

//sensor tanah #3
  output_tanah3 = analogRead(sensor_tanah3);
  output_tanah3 = map(output_tanah3,1023,350,0,100);
  Serial.print("Soil Humidity 3: ");
  Serial.print(output_tanah3);
  Serial.println("%");
//sensor tanah bubar
  
  Serial.println("");
  delay(1000);
}
