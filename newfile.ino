#include <Servo.h>
Servo myservo;
#define val            100
#define DIRB           7
#define PWMB           6
#define PWMA           5   //Motor A's pin
#define DIRA           4   //Motor A's pin
#define SERVOPIN       3//servo's pin

#define SERVOMIN 45      //the angle of servo
#define SERVOMID 90
#define SERVOMAX 135
#define TURNLEFT myservo.write(SERVOMIN)  //turn left
#define TURNMID myservo.write(SERVOMID)   //turn middle
#define TURNRIGHT myservo.write(SERVOMAX)  //turn right
//#define MOTORFOWARD setMotor(155)    //motor foward
//#define MOTORBACK setMotor(-155)     //motor back
//#define MOTORSTOP setMotor(0)        //motor stop

void setup() {
  Serial.begin(9600);
  pinMode(PWMA, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRB, OUTPUT);
  myservo.attach(SERVOPIN);
  SERVOMID;
  delay(300);
}
void(* resetFunc) (void) = 0;
void back(){
  digitalWrite(DIRA,HIGH);
  analogWrite(PWMA,val);
  digitalWrite(DIRB,HIGH);
  analogWrite(PWMB,val);
}
void carstop(){
  digitalWrite(DIRA,HIGH);
  analogWrite(PWMA,0);
  digitalWrite(DIRB,HIGH);
  analogWrite(PWMB,0);
}
void forward(){
  digitalWrite(DIRA,LOW);
  analogWrite(PWMA,val);
  digitalWrite(DIRB,LOW);
  analogWrite(PWMB,val);
}
void loop() {
  if(Serial.available()){
    char temp = Serial.read();
    int angle = 0;  
    angle = Serial.parseInt();
    Serial.print(angle);
        
    if(angle >= 500){
      carstop();
      delay(2000);
      angle = 0;
    }
    if (angle > 45){
        angle = 45;
    }
    if (angle < -45){
        angle = -45;
    }
    angle += 135;
    Serial.print(angle);
    Serial.print('\n');
    //carstop();
    //delay(2000);
    forward();       
        //TURNLEFT;
    myservo.write(angle);
  }



/*********************************************************************
some fucking comment
*********************************************************************/
  delay(50);
}



void setMotor(int m1Speed) //motor
{
  if (m1Speed > 0)
  {
    digitalWrite(DIRA, LOW);
    digitalWrite(DIRB, LOW);
    analogWrite(PWMA, 255 + m1Speed);
    analogWrite(PWMB, 255 + m1Speed);
  }
  else if(m1Speed < 0){
    digitalWrite(DIRA, HIGH);
    digitalWrite(DIRB, HIGH);
    analogWrite(PWMA, 255 - m1Speed);
    analogWrite(PWMB, 255 - m1Speed);
  }else{
    digitalWrite(PWMA, LOW);
    digitalWrite(PWMB, LOW);
    digitalWrite(DIRA, HIGH);
    digitalWrite(DIRB, HIGH);
  }
}
