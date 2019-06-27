//VCC to 5V,
//GND to GND,
//SCL to A5,
//SDA to A4,
//ADO to GND,
//INT to digital pin 2.

#include<Wire.h>
//MPU6050
const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int minVal=265;
int maxVal=402;
double x;
double y;
double z;
float x1;
float y1;
float z1;

//soil moisture
int sensor_tanah = A3; 
int output_tanah ;

//SW420
int sensor_getar =5;
String output_getar;

//Rotary encoder
#define outputA 6 //CLK
#define outputB 7 //DT
int counter = 0; 
int aState;
int aLastState; 

//millis
double jeda1,jeda2=0;
void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  pinMode (outputA,INPUT);
  pinMode (outputB,INPUT);
  Serial.begin(9600);
  pinMode(sensor_getar, INPUT);
  aLastState = digitalRead(outputA);
  Serial.println("System start");  
//  delay(1000);
}
void loop(){
  jeda1 = millis();

//rotary mulai
   aState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB) != aState) { 
       counter ++;
     } else {
       counter --;
     }
     Serial.print("Position: ");
     Serial.println(counter);
   } 
   aLastState = aState; // Updates the previous state of the outputA with the current state
//rotary bubar

  if(jeda1-jeda2 >= 5000){
    
      //  MPU6050 mulai
      Wire.beginTransmission(MPU_addr);
      Wire.write(0x3B);
      Wire.endTransmission(false);
      Wire.requestFrom(MPU_addr,14,true);
      AcX=Wire.read()<<8|Wire.read();
      AcY=Wire.read()<<8|Wire.read();
      AcZ=Wire.read()<<8|Wire.read();
      int xAng = map(AcX,minVal,maxVal,0,180);
      int yAng = map(AcY,minVal,maxVal,0,180);
      int zAng = map(AcZ,minVal,maxVal,0,180);
    
      x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
      x1 = x;
      if (x >= 180) {
        x1 = x - 360;
      }
      
      y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
      y1 = y;
      if (y >= 180) {
        y1 = y - 360;
      }
      z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
      z1 = z;
      if (z >= 180) {
        z1 = z - 360;
    }
    // MPU6050 Bubar
    
    //sensor tanah mulai
      output_tanah= analogRead(sensor_tanah);
      output_tanah = map(output_tanah,1023,350,0,100);
    //sensor tanah bubar
  
    //sensor getar mulai
      char getar =getar_init();
    //  delay(50);
      if (getar > 0) {
        output_getar = "ada-getaran";
      }
      else {
        output_getar = "tidak-ada-getaran";
      }
  
    Serial.println(x1 + String(" ") + y1 + String(" ") + z1 + String(" ") + output_tanah + String(" ") + output_getar + String(" ") + counter + String(" ") +  String("Node-01"));
    //  delay(5000);
    jeda2=jeda1;
    }
  }

long getar_init(){
  delay(10);
  long getar=pulseIn (sensor_getar, HIGH);
  return getar;
  }
