#define leftCenterSensor  4 
#define leftNearSensor    3 
#define leftFarSensor    2  
#define rightCenterSensor 5
#define rightNearSensor    6
#define rightFarSensor    7 

int leftCenterReading;
int leftNearReading;
int leftFarReading;
int rightCenterReading;
int rightNearReading;
int rightFarReading;

int leftNudge;
int replaystage;
int rightNudge;

#define leapTime 200

#define leftMotor1  8
#define leftMotor2  9
#define Left_Speed  11
#define rightMotor1 12
#define rightMotor2 13
#define Right_Speed 10
int led =A0;
#define buzzer A4
#define button A5
char path[30] = {'L','S','R','L','S','L','S','S','R','L','R','R','R','L','L','R','L','L','L','R','D'};
int pathLength;
int readLength=0;

void setup(){
  
  pinMode(leftCenterSensor, INPUT_PULLUP);
  pinMode(leftNearSensor, INPUT_PULLUP);
  pinMode(leftFarSensor, INPUT_PULLUP);
  pinMode(rightCenterSensor, INPUT_PULLUP);
  pinMode(rightNearSensor, INPUT_PULLUP);
  pinMode(rightFarSensor, INPUT_PULLUP);
 Start();   
  pinMode(buzzer, OUTPUT);
  pinMode(button, INPUT);
  digitalWrite(buzzer, LOW);
  
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  digitalWrite(led, HIGH);
  delay(1000);
/* while(1) {
  if(checkButton()==1) {   
                        break; }
  }*/
}
void loop()
{
  replay();
}
void readSensors(){
  
  leftCenterReading  = !digitalRead(leftCenterSensor);
  leftNearReading    = !digitalRead(leftNearSensor);
  leftFarReading     = !digitalRead(leftFarSensor);
  rightCenterReading = !digitalRead(rightCenterSensor);
  rightNearReading   = !digitalRead(rightNearSensor);
  rightFarReading    = !digitalRead(rightFarSensor);  

// serial printing below for debugging purposes

 /* Serial.print("\t");
  Serial.print(  leftFarReading );
  Serial.print("\t");
  Serial.print(leftNearReading );
  Serial.print("\t");
  Serial.print( leftCenterReading);
  Serial.print("\t");
  Serial.print( rightCenterReading);
  Serial.print("\t");
  Serial.print(rightNearReading);
  Serial.print("\t");
  Serial.print(rightFarReading);
  Serial.print("\n");
  */
  

}
void Start() 
{
  analogWrite(Left_Speed,150);
  analogWrite(Right_Speed,150);
}

void turnLeft(){
  
    
 
  while(!digitalRead(rightCenterSensor)==1||!digitalRead(leftCenterSensor)==1){
     digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(2);
     digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(1);
  }
    
  while(!digitalRead(rightCenterSensor)==0){
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(2);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(1);
  }
 
  
}

void turnRight(){

    
  while(!digitalRead(rightCenterSensor)==1){
     digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
    delay(2);
     digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(1);
  }
   while(!digitalRead(rightCenterSensor)==0){
     digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
    delay(2);
     digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(1);
  }
   while(!digitalRead(leftCenterSensor)==0){
     digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
    delay(2);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(1);
  }
  
   
 
}

void straight(){
  if( !digitalRead(leftCenterSensor)==0){
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(1);
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(5);
    return;
  }
  if(!digitalRead(rightCenterSensor)==0){
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(1);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(5);
    return;
  }
  
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(4);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(1);
  
}

void replay(){
   readSensors();
  if(leftFarReading==0 && rightFarReading==0){
    straight();
  }
  else{
    
    if(path[readLength]=='D'){
       digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(100);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
      endMotion();
    }
    if(path[readLength]=='L'){
     digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(leapTime);
      turnLeft();
    }
    if(path[readLength]=='R'){
       digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(110);
    turnRight();
    }
    if(path[readLength]=='S'){
       digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(leapTime);
    straight();
    }
    
    readLength++;
  }
    
  replay();
  
}

void endMotion(){
    digitalWrite(led, LOW);
    delay(500);
    digitalWrite(led, HIGH);
    delay(200);
      digitalWrite(led, LOW);
    delay(200);
    digitalWrite(led, HIGH);
    delay(500);
  endMotion();
}

