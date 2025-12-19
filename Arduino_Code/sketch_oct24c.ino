#include <Ultrasonic.h>
Ultrasonic u = Ultrasonic(2, 4);  //Trig,Echo


#include <Servo.h>
Servo s = Servo();

int ENA = 5;
int IN1 = 6;
int IN2 = 7;

int IN3 = 8;
int IN4 = 9;
int ENB = 10;

int white = 11;
int red = 12;
int yellow = 13;

void setup() {
  s.attach(3);  //Servo pin

  //Light
  pinMode(white, OUTPUT);   //White LED 10
  pinMode(red, OUTPUT);     //Red LED 9
  pinMode(yellow, OUTPUT);  //Yellow LED 8

  //Motor A
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  analogWrite(ENA, 250);

  //Motor B
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  analogWrite(ENB, 250);

  s.write(170);
  delay(1000);
  s.write(10);
  delay(1000);
  s.write(90);
  digitalWrite(red, HIGH);

  Serial.begin(9600);  //Serial Monitor
}

void loop() {

  int x = Serial.read();

  int d = u.read();

  if (d < 15) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    digitalWrite(red, HIGH);
  }

  if (x == '6') {
    digitalWrite(white, HIGH);
    digitalWrite(yellow, HIGH);
  }

  if (x == '7') {
    digitalWrite(white, LOW);
    digitalWrite(yellow, LOW);
  }

  //Forward
  if (d > 20) {

    if (x == '1') {

      digitalWrite(red, LOW);

      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);

      if (x == '6') {
        digitalWrite(white, HIGH);
        digitalWrite(yellow, HIGH);
      }
    }
  }

  //Reverse
  if (x == '2') {

    digitalWrite(red, HIGH);
    delay(200);
    digitalWrite(red, LOW);
    delay(200);
    digitalWrite(red, HIGH);
    delay(200);
    digitalWrite(red, LOW);
    delay(100);

    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    if (x == '6') {
      digitalWrite(white, HIGH);
      digitalWrite(yellow, HIGH);
    }

    delay(1200);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    digitalWrite(red, HIGH);
  }

  //Stop
  if (x == '3') {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    digitalWrite(red, HIGH);
  }

  //Turn Right
  if (x == '4') {
    s.write(10);
    delay(300);

    int d2 = u.read();
    if (d2 > 20) {
      // analogWrite(ENA, 85);

      digitalWrite(red, LOW);

      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      delay(500);

      digitalWrite(red, HIGH);

      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      // analogWrite(ENA, 100);
    }
    s.write(90);
  }

  //Turn Left
  if (x == '5') {
    s.write(170);
    delay(300);

    int d2 = u.read();
    if (d2 > 20) {

      // analogWrite(ENA, 85);

      digitalWrite(red, LOW);

      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      delay(500);

      digitalWrite(red, HIGH);

      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      // analogWrite(ENA, 100);
    }

    s.write(90);
  }
}