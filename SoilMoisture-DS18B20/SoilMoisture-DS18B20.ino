float sensor_tanah1 = A0; 
float output_tanah1 ;

float sensor_tanah2 = A1; 
float output_tanah2 ;

float sensor_tanah3 = A2; 
float output_tanah3 ;

void setup() {
  Serial.begin(9600);
  Serial.println("Larys start");
  delay(2000);
  }

void loop() {
//sensor tanah #1
  output_tanah1 = analogRead(sensor_tanah1);
  output_tanah1 = map(output_tanah1,1023,350,0,100);
  Serial.print("kelembapan Tanah 1: ");
  Serial.print(output_tanah1);
  Serial.println("%");
//sensor tanah bubar

//sensor tanah #2
  output_tanah2 = analogRead(sensor_tanah2);
  output_tanah2 = map(output_tanah2,1023,350,0,100);
  Serial.print("kelembapan Tanah 2: ");
  Serial.print(output_tanah2);
  Serial.println("%");
//sensor tanah bubar

//sensor tanah #3
  output_tanah3 = analogRead(sensor_tanah3);
  output_tanah3 = map(output_tanah3,1023,350,0,100);
  Serial.print("kelembapan Tanah 3: ");
  Serial.print(output_tanah3);
  Serial.println("%");
//sensor tanah bubar
  }
