#include "Arduino_SensorKit.h"
int lightCal;
int lightVal;
void setup() {
  Serial.begin(9600);
  Environment.begin();
  Oled.begin();
  Oled.setFlipMode(false);
  lightCal = analogRead(0);
  
}

void loop() {

  lightVal = analogRead(0);
  Serial.println(lightVal);
  Oled.setFont(u8x8_font_chroma48medium8_r); 
  Oled.setCursor(0, 3);
  Oled.print("Temp: ");
  Oled.println(Environment.readTemperature());
  Oled.print("Humidity: ");
  Oled.println(Environment.readHumidity());
  
  Serial.print("Temperature = ");
  Serial.print(Environment.readTemperature()); //print temperature
  Serial.println(" C");
  Serial.print("Humidity = ");
  Serial.print(Environment.readHumidity()); //print humidity
  Serial.println(" %");
  delay(2000);
}
