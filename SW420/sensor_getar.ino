int sensor_getar =9;

void setup(){
  pinMode(sensor_getar, INPUT); 
  Serial.begin(9600);
  Serial.println("Larys Start");
}
void loop(){
  long getar =getar_init();
  delay(50);
  Serial.print("Getaran : ");
  Serial.println(getar);
}

long getar_init(){
  delay(10);
  long getar=pulseIn (sensor_getar, HIGH);
  return getar;
}
