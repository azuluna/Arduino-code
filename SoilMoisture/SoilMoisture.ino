int sensor_tanah = A0; 
int output_tanah ;

void setup() {
  Serial.begin(9600);
  Serial.println("Larys start"); 
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
  }
