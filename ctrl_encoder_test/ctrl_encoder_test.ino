#include"Encoder.h"

float t = 22;
const int pinA = A2;
const int pinB = A3;
Encoder enc(pinA,pinB);

void setup() {
  Serial.begin (9600);
}

void loop() {
  int re = enc.read();
  Serial.println(re);
  
}

