#define A 4
#define B 3

void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  int a0 = analogRead(A0);
  int a1 = analogRead(A1);
  Serial.print("A1 = ");
  Serial.print(a1);
  Serial.print(" | A0 = ");
  Serial.println(a0);

  // BA = 00 => 0
  if (a1 < 500 && a0 < 500) {
    digitalWrite(B, LOW);
    digitalWrite(A, LOW);
  } 
  else if (a1 < 500 && a0 >= 500) { //BA = 01 => 1
    digitalWrite(B, LOW);
    digitalWrite(A, HIGH);
  }
  else if (a1 >= 500 && a0 < 500) { //BA = 10 => 1
    digitalWrite(B, LOW);
    digitalWrite(A, HIGH);
  }
  else { //BA = 11 => 2
    digitalWrite(B, HIGH);
    digitalWrite(A, LOW);
  }

}
