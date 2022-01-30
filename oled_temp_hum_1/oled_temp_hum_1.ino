#include "Arduino_SensorKit.h"

const int r_1 = 11;
const int g_1 = 12;
const int b_1 = 13;
const int r_2 = 10;
const int g_2 = 8;
const int b_2 = 9;
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

void setRGB_1(int red)
  {
    analogWrite(r_1, red);
    digitalWrite(g_1, LOW);
    digitalWrite(b_1, HIGH);
  }
void setRGB_2(int red, int blue) //temp
  {
    analogWrite(r_2, red);
    digitalWrite(g_2, HIGH);
    analogWrite(b_2, blue);
  }

void rgb1_off(){
    digitalWrite(r_1, HIGH);
    digitalWrite(g_1, HIGH);
    digitalWrite(b_1, HIGH);
}
void rgb2_off(){
    digitalWrite(r_2, HIGH);
    digitalWrite(g_2, HIGH);
    digitalWrite(b_2, HIGH);
}

void update_fsm() {
  switch (curr_state) {
    case sProgram:
      rgb1_off();
      rgb2_off();
      // Get max and min temperature
      Serial.println("Input maximum temperature (Celcius)");
      max_temp = Serial.parseInt();
  
      Serial.println("Input minimum temperature (Celcius)");
      min_temp = Serial.parseInt();

      // Error if min_temp >= max_temp, reprompt user
      while(min_temp >= max_temp) {
        Serial.print("Error: Min temp:");
        Serial.print(min_temp);
        Serial.print(" >= Max temp: ");
        Serial.println(max_temp);
        
        Serial.println("Input maximum temperature (Celcius)");
        max_temp = Serial.parseInt();
    
        Serial.println("Input minimum temperature (Celcius)");
        min_temp = Serial.parseInt();
      }

      // Get max and min humidity
      Serial.println("Input maximum humidity (%)");
      max_humid = Serial.parseInt();
  
      Serial.println("Input minimum humidity (%)");
      min_humid = Serial.parseInt();

      // Error if min_humid >= max_humid, reprompt user
      while(min_humid >= max_humid) {
        Serial.print("Error: Min humidity:");
        Serial.print(min_humid);
        Serial.print(" >= Max humidity: ");
        Serial.println(max_humid);
        
        Serial.println("Input maximum humidity (%)");
        max_humid = Serial.parseInt();
    
        Serial.println("Input minimum humidity (%)");
        min_humid = Serial.parseInt();
      }
  
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
        rgb2_off();
        digitalWrite(redTemp, HIGH);
        digitalWrite(blueTemp, LOW);
      }
      else if (curr_temp < (float)min_temp) {
        rgb2_off();
        digitalWrite(redTemp, LOW);
        digitalWrite(blueTemp, HIGH);
      }
      else{
        digitalWrite(redTemp, LOW);
        digitalWrite(blueTemp, LOW);
        float temp_range = max_temp - min_temp;
        float dist_to_max_temp = max_temp - curr_temp;
        int red = (dist_to_max_temp/temp_range)*255;
        int blue = 255-red;

        setRGB_2(red, blue);
      }
     

   
      if (curr_humid > (float)max_humid){
        rgb1_off();
        digitalWrite(greenHum, HIGH);
        digitalWrite(yellowHum, LOW);
      }
      else if (curr_humid < (float)min_humid){
        rgb1_off();
        digitalWrite(greenHum, LOW);
        digitalWrite(yellowHum, HIGH);
      }
      else{
        digitalWrite(greenHum, LOW);
        digitalWrite(yellowHum, LOW);
        float humid_range = max_humid - min_humid;
        float dist_to_max_humid = max_humid - curr_humid;
        int red = (dist_to_max_humid/humid_range)*255-255;

        setRGB_1(red);
      }


      Oled.setFont(u8x8_font_chroma48medium8_r); 
      Oled.setCursor(0, 1);
      Oled.println("Hack @ Brown");
      Oled.println("2022");
      Oled.println("");
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
