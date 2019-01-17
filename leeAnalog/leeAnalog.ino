#define ventilador 11
#define k          50

/*
  ReadAnalogVoltage
  Reads an analog input on pin 0, converts it to voltage, and prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */
float t_deseada = 20.0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  pinMode(A0,INPUT);
  pinMode(ventilador,OUTPUT);
  analogWrite(ventilador,255);
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
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
  Serial.print("La temperatura es: ");
  Serial.println(temperature);
  Serial.print("El comando calculado: ");
  Serial.println(command);
  Serial.println(" ");
}
