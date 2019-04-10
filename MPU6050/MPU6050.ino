//VCC to 5V(MPU-6050 works with 3.3V but GY-521 increases it to 5V.),
//GND to GND,
//SCL to A5,
//SDA to A4,
//ADO to GND,
//INT to digital pin 2.

#include<Wire.h>

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int minVal=265;
int maxVal=402;

double x;
double y;
double z;
int x1;
int y1;
int z1;
void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
}
void loop(){
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
//       z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
//       z1 = z;
//       if (z >= 180) {
//        z1 = z - 360;
//        }

     Serial.print("AngleX= ");
     Serial.println(x1);

     Serial.print("AngleY= ");
     Serial.println(y1);

//     Serial.print("AngleZ= ");
//     Serial.println(z1);
     Serial.println("-----------------------------------------");
     delay(1000);
}
