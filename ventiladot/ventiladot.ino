#define ventilador 3
#define k 50
#define t_deseada 18

void setup(){
  pinMode(ventilador,OUTPUT);
  analogWrite(ventilador,255);
}

void loop(){
  int vel = 0;
  for(vel = 0; vel < 255; vel++) {
    analogWrite(ventilador,vel);
    delay(100);
  }
  for(vel = 255; vel > 0; vel--){
    analogWrite(ventilador,vel);
    delay(100);
  }
  delay(500);
   
}
