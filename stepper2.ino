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

#define SERVOPIN A5

#define MOTOR_STEP 4095

//Servo Setup
Servo         servo;
int           Steps = 0;
int           angle = 0;

//Step Motor Setup
long          time;
unsigned long last_time;
unsigned long currentMillis;
int           steps_left  = MOTOR_STEP;
boolean       Direction   = true;

String command;

void setup(){
  Serial.begin(9600);
  
  Serial.println("Start program ...");
  
  servo.attach(SERVOPIN);

  initStepMotor(M1IN1, M1IN2, M1IN3, M1IN4);
  initStepMotor(M2IN1, M2IN2, M2IN3, M2IN4);
  initStepMotor(M3IN1, M3IN2, M3IN3, M3IN4);
}

void loop(){

  if(Serial.available()){
        command = Serial.readStringUntil('/n');
        Serial.println("command:  " + command + "!");
        CommandHandler(command);  
  }
}

void CommandHandler(String cmd){

switch(cmd[0]){
  case 's':
    Serial.println("Command Servo");
    switch(cmd[1]){
      case 'o':
        Serial.println("Command mode oopen for command Servo");
              for(angle = 0; angle < 180; angle++){
                servo.write(angle);
              }
        break;
        
      case 'c':
        Serial.println("Command mode close for command Servo");
              for(angle = 180; angle > 0; angle--){
                servo.write(angle);
              }
        break;
        
      default:
        Serial.println("Unknown command mode for command Servo");
    }
    break;
    
  case 'm':
    Serial.println("Command motor");
    switch(cmd[1]){
      case 't':
        Direction = true;
        stepMotorCommand(cmd);
        break;
      
      case 'f':
        Direction = false;
        stepMotorCommand(cmd);
        break;
        
      default:
        Serial.println("Unknown command mode for command Motor");
    }
    break;
    
  default:
  Serial.println("Unknown command");
}
}

void stepMotorCommand(String cmdMotor){
  int stepsMotor = readStep(cmdMotor);
    switch(cmdMotor[2]){
      case '1':
        Serial.println("Motor 1");
        setupMotors(1, stepsMotor);
        break;
      case '2':
        Serial.println("Motor 2");
        setupMotors(2, stepsMotor);
        break;
      case '3':
      Serial.println("Motor 3");
        setupMotors(3, stepsMotor);
        break;
      default:
        Serial.println("Unknown command mode for command Motor");
  }
  steps_left = MOTOR_STEP;
}

void setupMotors(int namberMotor, int steps_left){
  if (steps_left == 0){
    Serial.println("stepsMotor = 0");
    return; 
  }
  
  if(namberMotor == 1){
    controlMotor(steps_left, M1IN1, M1IN2, M1IN3, M1IN4);
  }
  if(namberMotor == 2){
    controlMotor(steps_left, M2IN1, M2IN2, M2IN3, M2IN4);
  }
  if(namberMotor == 3){
    controlMotor(steps_left, M3IN1, M3IN2, M3IN3, M3IN4);
  }
}

void controlMotor(int steps_left, int IN1, int IN2, int IN3, int IN4){
  while(steps_left>0){
    currentMillis = micros();
    if(currentMillis-last_time>=1000){
      stepper(1, IN1, IN2, IN3, IN4);
      time=time+micros()-last_time;
      last_time=micros();
      steps_left--;
    }
  }
}

int readStep(String cmd){  
  String stringStep = cmd.substring(3);
  return stringStep.toInt();  
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
