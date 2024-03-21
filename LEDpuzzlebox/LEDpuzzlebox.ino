#include <Servo.h>
Servo myServo;  // create a servo object
const int servoPin = 3;
const int capSensor1 = A2;
const int capSensor2 = A3;
const int capSensor3 = A4;
const int capSensor4 = A5;
const int red1 = 13;
const int green1 = 12;
const int white1 = 11;
const int red2 = 10;
const int green2 = 9;
const int white2 = 8;
const int red3 = 7;
const int green3 = 6;
const int white3 = 5;
const int red4 = 4;
const int green4 = A0;
const int white4 = 2;
int state1 = 0;
int state2 = 0;
int state3 = 0;
int state4 = 0;
int cap1 = 0;
int cap2 = 0;
int cap3 = 0;
int cap4 = 0;
int last1 = 0;
int last2 = 0;
int last3 = 0;
int last4 = 0;
int angle;
String formatted_str;

void setup() {
  Serial.begin(115200);
  myServo.attach(servoPin);
  for (int pinNumber = 2; pinNumber < 14; pinNumber++) {
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, HIGH);
  }
  pinMode(servoPin, OUTPUT);
  pinMode(green4, OUTPUT);
  digitalWrite(green4, HIGH);
}

void loop() {
  cap1 = digitalRead(capSensor1);
  cap2 = digitalRead(capSensor2);
  cap3 = digitalRead(capSensor3);
  cap4 = digitalRead(capSensor4);
  if (cap1 == 1 and last1 == 0){
    state1 += 1;
    angle -= 5;
    if (state1 >3){
      state1 = 0;
    }
  }
  if (state1 >= 1){
    digitalWrite(red1, HIGH);
  }
  else {
    digitalWrite(red1, LOW);
    digitalWrite(green1, LOW);
    digitalWrite(white1, LOW);
  }
  if (state1 >= 2){
    digitalWrite(green1, HIGH);
  }
  if (state1 == 3){
    digitalWrite(white1, HIGH);
  }

  if (cap2 == 1 and last2 == 0){
    state2 += 1;
    angle -= 10;
    if (state2 >3){
      state2 = 0;
    }
  }
  if (state2 >= 1){
    digitalWrite(red2, HIGH);
  }
  else {
    digitalWrite(red2, LOW);
    digitalWrite(green2, LOW);
    digitalWrite(white2, LOW);
  }
  if (state2 >= 2){
    digitalWrite(green2, HIGH);
  }
  if (state2 == 3){
    digitalWrite(white2, HIGH);
  }

  if (cap3 == 1 and last3 == 0){
    state3 += 1;
    angle += 5;
    if (state3 >3){
      state3 = 0;
    }
  }
  if (state3 >= 1){
    digitalWrite(red3, HIGH);
  }
  else {
    digitalWrite(red3, LOW);
    digitalWrite(green3, LOW);
    digitalWrite(white3, LOW);
  }
  if (state3 >= 2){
    digitalWrite(green3, HIGH);
  }
  if (state3 == 3){
    digitalWrite(white3, HIGH);
  }

  if (cap4 == 1 and last4 == 0){
    state4 += 1;
    angle += 10;
    if (state4 >3){
      state4 = 0;
    }
  }
  if (state4 >= 1){
    digitalWrite(red4, HIGH);
  }
  else {
    digitalWrite(red4, LOW);
    digitalWrite(green4, LOW);
    digitalWrite(white4, LOW);
  }
  if (state4 >= 2){
    digitalWrite(green4, HIGH);
  }
  if (state4 == 3){
    digitalWrite(white4, HIGH);
  }

  last1 = cap1;
  last2 = cap2;
  last3 = cap3;
  last4 = cap4;
  if (angle < 0){
    angle = 0;
  }
  if (angle > 180){
    angle = 180;
  }
  myServo.write(angle);
  formatted_str = String(state1)+String(state2)+ String(state3)+ String(state4) + String(angle);      
  Serial.println(formatted_str);
  delay(100);
}
