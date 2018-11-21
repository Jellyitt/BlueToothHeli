#include <Arduino.h>

#define in1A 3//p
#define in1B 2//d
#define in2A 4//d
#define in2B 5//p


void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(in1A, 0);//top rotor
  digitalWrite(in1B, LOW);
  analogWrite(in2B, 0);//bottom rotor
  digitalWrite(in2A, LOW);


}        
