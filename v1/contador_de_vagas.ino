#include <Servo.h>

const int TRIG = 3;
const int ECHO = 2;
const int red = 11;
const int green = 12;
const int blue = 13;

Servo servoMotor;

void setup() {
  Serial.begin(115200);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(blue, LOW);
  servoMotor.attach(10);
}

void loop() {
  int distancia = medirDistancia(TRIG, ECHO);    
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println("cm");

  if (distancia <= 15) {
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
    servoMotor.write(0);
    //delay(500);
  }
  else {
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(blue, LOW);
    servoMotor.write(100);
    //delay(500);
  }
  
//  digitalWrite(red, LOW);
//  digitalWrite(green, LOW);
//  digitalWrite(blue, HIGH);
//  delay(500);
}

int medirDistancia(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  return pulseIn(echo,HIGH) / 58;
}
