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

// Define state enums
typedef enum {
  sProgram = 1,
  sGetData = 2,
  sSetOutput = 3,
} state;

float curr_temp;
float curr_humid;

int max_temp;
int min_temp;
int max_humid;
int min_humid;

// Set starting state to 'Program'
state curr_state = sProgram;

void setup() {
  Serial.begin(9600);
  // One minute read timeout
  Serial.setTimeout(60000);
  while(!Serial);
  Environment.begin();
  Oled.begin();
  Oled.setFlipMode(false);

  for(int i=0; i<sizeof(allPins)/sizeof(allPins[0]); i++) {
    pinMode(*allPins[i], OUTPUT);
  }
}

void loop() {
  update_fsm();
}

void update_fsm() {
  switch (curr_state) {
    case sProgram:
      Serial.println("Input maximum temperature (Celcius)");
      max_temp = Serial.parseInt();
  
      Serial.println("Input minimum temperature (Celcius)");
      min_temp = Serial.parseInt();
  
      Serial.println("Input maximum humidity (%)");
      max_humid = Serial.parseInt();
  
      Serial.println("Input minimum humidity (%)");
      min_humid = Serial.parseInt();
  
      curr_state = sGetData;
      break;
      
    case sGetData:
      curr_temp = Environment.readTemperature();
      curr_humid = Environment.readHumidity();
      Serial.print("Temperature = ");
      Serial.print(curr_temp); //print temperature
      Serial.println(" C");
      Serial.print("Humidity = ");
      Serial.print(curr_humid); //print humidity
      Serial.println(" %");
      delay(2000);
      curr_state = sSetOutput;
      break;
      
    case sSetOutput:
      if (curr_temp > (float)max_temp){
        digitalWrite(redTemp, HIGH);
      }
      else{
        digitalWrite(redTemp, LOW);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
      }
      if (curr_temp < (float)min_temp){
        digitalWrite(blueTemp, HIGH);
      }
      else{
        digitalWrite(blueTemp, LOW);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
      }
    
    
      if (curr_humid > (float)max_humid){
        digitalWrite(greenHum, HIGH);
      }
      else{
        digitalWrite(greenHum, LOW);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
      }
      if (curr_humid < (float)min_humid){
        digitalWrite(yellowHum, HIGH);
      }
      else{
        digitalWrite(yellowHum, LOW);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
      }


      Oled.setFont(u8x8_font_chroma48medium8_r); 
      Oled.setCursor(0, 3);
      Oled.print("Temp: ");
      Oled.println(curr_temp);
      Oled.print("Humidity: ");
      Oled.println(curr_humid);
      
      curr_state = sGetData;
      break;
      
    default:
      Serial.println("Why am I in default??");
  }
  
}
