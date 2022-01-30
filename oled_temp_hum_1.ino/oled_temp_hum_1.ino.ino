#include "Arduino_SensorKit.h"

const int r_1 = 11;
const int g_1 = 13;
const int b_1 = 12;
const int r_2 = 8;
const int g_2 = 9;
const int b_2 = 10;
const int redTemp = 6;
const int blueTemp = 4;
const int greenHum = 7;
const int yellowHum = 5;

const int *allPins[10] = {&r_1, &g_1, &b_1, &r_2, &g_2, &b_2, &redTemp, &blueTemp, &greenHum, &yellowHum};

void setup() {
  Serial.begin(9600);
  Environment.begin();
  Oled.begin();
  Oled.setFlipMode(false);

  for(int i=0; i<sizeof(allPins)/sizeof(allPins[0]); i++) {
    pinMode(*allPins[i], OUTPUT);
  }
}

void loop() {

  
  float currTemp = Environment.readTemperature();
  float currHum = Environment.readHumidity();
  digitalWrite(r_1, LOW);
  digitalWrite(g_1, HIGH);
  digitalWrite(b_1, LOW);
  if (currTemp > 15.0){
    digitalWrite(redTemp, HIGH);
  }
  else{
    digitalWrite(redTemp, LOW);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
  }
  if (currTemp < 10.0){
    digitalWrite(blueTemp, HIGH);
  }
  else{
    digitalWrite(blueTemp, LOW);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
  }


  if (currHum > 70){
    digitalWrite(greenHum, HIGH);
  }
  else{
    digitalWrite(greenHum, LOW);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
  }
  if (currHum < 30){
    digitalWrite(yellowHum, HIGH);
  }
  else{
    digitalWrite(yellowHum, LOW);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
  }






  Oled.setFont(u8x8_font_chroma48medium8_r); 
  Oled.setCursor(0, 3);
  Oled.print("Temp: ");
  Oled.println(currTemp);
  Oled.print("Humidity: ");
  Oled.println(currHum);
  
  Serial.print("Temperature = ");
  Serial.print(Environment.readTemperature()); //print temperature
  Serial.println(" C");
  Serial.print("Humidity = ");
  Serial.print(Environment.readHumidity()); //print humidity
  Serial.println(" %");
  delay(1000);
}
