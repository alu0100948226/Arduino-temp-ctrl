#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int inc = A5, dec = A4;
const int t = A0;
const int ventilador = 10;
const int cicles = 5000;
unsigned long int time = 0;

const int k = 50;

char temp[7];

char msg[16] = {'T','D',' ',' ',' ','.',' ',' ','T','A' ,' ' ,' ',' ','.',' ',' '};


LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int prevDec = 0;
int prevInc = 0;
int currCicle = 0;
unsigned long int tPulsoInc = 0;
unsigned long int tPulsoDec = 0;

int t_deseada = 22;

void float_to_chars(float data, char * r){
  
  int aux = data / 10;
  int entero = data;
  r[0] = aux + 48;
  Serial.println(aux);
  aux = int(data) % 10;
  r[1] = aux + 48;
  int dec = (data - entero) * 100;
  r[3] = (dec / 10) + 48;
  r[4] = (dec % 10) + 48;
}

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(8, 2);
  pinMode(inc, INPUT);
  pinMode(dec, INPUT);
  pinMode(t,   INPUT);
  pinMode(ventilador, OUTPUT);
  analogWrite(ventilador, 255);
  
  // initialize the serial communications:
  Serial.begin(9600);
}

void loop() {
  int currInc = digitalRead(inc);
  int currDec = digitalRead(dec);
  
  if(!prevInc && currInc)
    tPulsoInc = millis();
  else if(prevInc && currInc && (millis() - tPulsoInc) > 1000){
    t_deseada++;
    tPulsoInc = millis();
  }
    
  if(!prevDec && currDec)
    tPulsoDec = millis();
  else if(prevDec && currDec && (millis() - tPulsoDec) > 1000){
    t_deseada--;
    tPulsoDec = millis();
  }
  
  prevInc = currInc;
  prevDec = currDec;
    
  
    
  int sensorValue = analogRead(t);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  voltage /= 11;
  float temperature = voltage*100;
  
  float error = t_deseada - temperature;
  int command = 255 + error*k;
  if (command < 0){
    command = 0;
  } 
  else if(command > 255){
    command = 255;
  }
  
  analogWrite(ventilador,command);
  //float error = t_deseada - temperature;
  
  // when characters arrive over the serial port...
  if ((millis() - time) >= 1000) {
    lcd.clear();
    float_to_chars(temperature, &msg[11]);
    float_to_chars(t_deseada, &msg[3]);
    
    int i = 0;
    for (i=0; i < 16; i++){
      if(i == 8)
        lcd.setCursor(0,1);
      lcd.write(msg[i]);
    }
    time = millis();
    //lcd.write(temperature);
  }
}
