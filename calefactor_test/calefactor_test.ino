const int cal = 9;

void setup(){
  pinMode(cal, OUTPUT);
  
}

void loop(){
  analogWrite(cal,0);
  /*for(i = 0; i < 256; i++){
    analogWrite(calefactor,i);
    delay(20);
  }
  for(i = 255; i >= 0; i--){
    analogWrite(calefactor,i);
    delay(20);
  }*/
}
