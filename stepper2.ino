#include <Servo.h>

#define M1IN1 2
#define M1IN2 3
#define M1IN3 4
#define M1IN4 5

#define M2IN1 6
#define M2IN2 7
#define M2IN3 8
#define M2IN4 9

#define M3IN1 10
#define M3IN2 11
#define M3IN3 12
#define M3IN4 13


//Servo Setup
Servo servo;
const int SERVO_PIN = A5;
int Steps = 0;
int angle = 0;

//Step Motor Setup
boolean Direction = true;
unsigned long last_time;
unsigned long currentMillis ;
int steps_left=4095;
long time;

void setup(){
  Serial.begin(9600);
  Serial.println("Start program ...");
  
  servo.attach(SERVO_PIN);

  initStepMotor(M1IN1, M1IN2, M1IN3, M1IN4);
  initStepMotor(M2IN1, M2IN2, M2IN3, M2IN4);
  initStepMotor(M3IN1, M3IN2, M3IN3, M3IN4);
}

void loop(){
  Serial.println("Servo 0 t o180"); 
  for(angle = 0; angle < 180; angle++){
    servo.write(angle);
    delay(5);
  }

  Serial.println("Step motor"); 
  while(steps_left>0){
    currentMillis = micros();
    if(currentMillis-last_time>=1000){
      stepper(1, M3IN1, M3IN2, M3IN3, M3IN4);
      time=time+micros()-last_time;
      last_time=micros();
    steps_left--;
    }
  }
  
  Serial.println(time);
  Serial.println("Wait...!");
  delay(2000);
  Serial.println("Direction:");
  Serial.println(Direction);
  Serial.println("Steps:");
  Serial.println(Steps);
  Direction=!Direction;
  
  steps_left=4095;


  Serial.println("Servo 180 to 0");
  for(angle = 180; angle > 0; angle--){
    servo.write(angle);
    delay(5);
  }
}

void initStepMotor(int IN1, int IN2, int IN3, int IN4){
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void stepper(int xw, int IN1, int IN2, int IN3, int IN4){
  for (int x=0; x<xw; x++){
    switch(Steps){
      case 0:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      break;
      
      case 1:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, HIGH);
      break;
      
      case 2:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      break;
      
      case 3:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      break;
      
      case 4:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
      
      case 5:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
      
      case 6:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
      
      case 7:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      break;
      
      default:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
    }
    SetDirection();
  }
}

void SetDirection(){
  if(Direction == 1){ 
      Steps++;
  }
  if(Direction == 0){ 
    Steps--; 
  }
  if(Steps > 7){
    Steps = 0;
  }
  if(Steps < 0){
    Steps = 7; 
  }
}
