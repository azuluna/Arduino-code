int sensor_tanah = A0; 
int sensor_getar =9;
int output_tanah ;

void setup() {
  Serial.begin(9600);
  Serial.println("Larys start");
  pinMode(sensor_getar, INPUT); 
  delay(2000);
  }

void loop() {
//sensor tanah mulai
  output_tanah= analogRead(sensor_tanah);
  output_tanah = map(output_tanah,1023,350,0,100);
  Serial.print("kelembapan Tanah : ");
  Serial.print(output_tanah);
  Serial.println("%");
//sensor tanah bubar

//sensor getar mulai
  long getar =getar_init();
  delay(50);
  if (getar > 0) {
  Serial.println("Getaran terdeteksi!!!");
//  Serial.println(getar);
//sensor getar bubar
  }
  else {
    Serial.println("Tak ada getaran");
    }
  delay(1000);
  }

long getar_init(){
  delay(10);
  long getar=pulseIn (sensor_getar, HIGH);
  return getar;
  }
