#include <Adafruit_AHTX0.h>   // Library for AHT10

const byte MQ4_Pin = A0;
const int R_0 = 1472;

const int lowest = 49 ;
const int highest = 969; 
const int pureGas = 1000000 ; 

Adafruit_AHTX0 AHT10;
float AHT10_Humidity, AHT10_Temp;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  if (!AHT10.begin()) {
    // If the sensor fails to initialize, stay in a loop (or print error message)
    while (1) delay(10);
  }
    Serial.flush();
    Serial.println("Temp Humid MethanePPM");
}

void loop() {
  // put your main code here, to run repeatedly:
  Get_AHT10_Data();
  //Serial.print("Temperature: ");
  Serial.print(AHT10_Temp);
  Serial.print(" ");
    
  //Serial.print("Humidity: ");
  Serial.print(AHT10_Humidity);
  Serial.print(" ");

  //Serial.print("Methane PPM: ");
  Serial.print(getMethanePPM());

  // Separate readings with a blank line for clarity in Serial Plotter
  Serial.println();

  delay(1000);
}

void Get_AHT10_Data(){
  sensors_event_t Humidity, Temp;
  AHT10.getEvent(&Humidity, &Temp);
  AHT10_Humidity = Humidity.relative_humidity;
  AHT10_Temp = Temp.temperature;
}

// float getMethanePPM(){
//   float a0 = analogRead(A0);
//   float v_o = a0 * 5 /1023;
//   float R_S = (5 - v_o) * 1000 / v_o;
//   float PPM = pow(R_S/R_0, -2.95) * 1000;
//   return PPM;
// }

float getMethanePPM(){
  float x = analogRead(A0);
  float k = log(pureGas) / highest;
  float PPM = pow(10, k * (x - lowest));
  return PPM;
}