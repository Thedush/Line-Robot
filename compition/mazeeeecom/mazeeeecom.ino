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
int replaystage=0;
int rightNudge;
int buzzer1=0;

#define leapTime 200

#define leftMotor1 8
#define leftMotor2  9
#define Left_Speed  11
#define rightMotor1 12
#define rightMotor2 13
#define Right_Speed 10
int led =A0;
int buzzer=A4;
int button=A3;
int button1=A2;
char path[30] = {};
int pathLength;
int readLength;
  // put your setup code here, to run once:
void setup()
{
  
  pinMode(leftCenterSensor, INPUT_PULLUP);
  pinMode(leftNearSensor, INPUT_PULLUP);
  pinMode(leftFarSensor, INPUT_PULLUP);
  pinMode(rightCenterSensor, INPUT_PULLUP);
  pinMode(rightNearSensor, INPUT_PULLUP);
  pinMode(rightFarSensor, INPUT_PULLUP);
  pinMode(buzzer, INPUT_PULLUP);
  pinMode(button, OUTPUT);
  pinMode(button1, OUTPUT);
  digitalWrite(button,HIGH);
  digitalWrite(button1,LOW);
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(Left_Speed, OUTPUT);
  pinMode(Right_Speed, OUTPUT);
   Start();   
//  pinMode(led, INPUT);
 // Serial.begin(9600);
 /*  while(1) {
  if(checkButton()==1) {   
                        break; }
  }
  */
}

void loop() 
{
   

  
   readSensors();  //starts reading sensor                                                                                   

  //Serial.print("2");
 if(leftFarReading==0 && rightFarReading==0 && 
   (leftCenterReading==1 || rightCenterReading==1) ){ 
 
    straight();                                                                                      
  }

  else{                                                                                            
    leftHandWall();   //if not straight                                                                                 
  }// put your main code here, to run repeatedly:
  }
 


void leftHandWall()  
{
  //using left hand rule

  if( leftFarReading==1 && rightFarReading==1)// if it detect T bend
  {
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(210);
   // readSensors();
    //move inch forward and check
    
        turnLeft();
    
    
  }
  
  if(leftFarReading==1){ // if it detect left  turn left
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(leapTime);
    //readSensors();
    //move inch forward and check
      
        turnLeft();
      }
   
  if(rightFarReading==1)//if right turn right
  {
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    //delay(30);
    //readSensors();
    //move inch forward and check
    
       // turnLeft();
      
    
    delay(leapTime);
    // if not anything move straight
    readSensors();
    if(leftFarReading==0 && leftCenterReading==0 &&
      rightCenterReading==0 && rightFarReading==0){
      turnRight();
      return;
    }
   path[pathLength]='S';// an array to store path
    pathLength++;
    if(path[pathLength-2]=='B')//if the path is LBLR it will check for back and return to correction
    {
    shortPath();
       path[pathLength]='S';
     
     
     }
    straight();
  }
  //if it detects dead end
  readSensors();
  if(leftFarReading==0 && leftCenterReading==0 && rightCenterReading==0 
    && rightFarReading==0 && leftNearReading==0 && rightNearReading==0){
    turnAround();
  }
 
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
 
if(replaystage==0){
    path[pathLength]='L';
    pathLength++;
      if(path[pathLength-2]=='B'){
        shortPath();
       path[pathLength]='L';
      
      }
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
  
  if(replaystage==0){
  path[pathLength]='R'; //if it turn right completely store as R
  //Serial.println("r");
  pathLength++;
    if(path[pathLength-2]=='B'){
      shortPath();
    path[pathLength]='R';
    }
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

void turnAround(){
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(150);
   while(!digitalRead(rightCenterSensor)==0){
     digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(4);
     digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(1);
  }
path[pathLength]='B';
 pathLength++;
  straight();
  }
  void readSensors(){
  
  leftCenterReading  = !digitalRead(leftCenterSensor);
  leftNearReading    = !digitalRead(leftNearSensor);
  leftFarReading     = !digitalRead(leftFarSensor);
  rightCenterReading = !digitalRead(rightCenterSensor);
  rightNearReading   = !digitalRead(rightNearSensor);
  rightFarReading    = !digitalRead(rightFarSensor);  
  buzzer1=digitalRead(buzzer);
// serial printing below for debugging purposes
// Serial.print("\n");
 // Serial.print(  buzzer1);
 while(buzzer1==0)
 {
  stops();
 }
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
void stops()
{
  analogWrite(Left_Speed,0);
  analogWrite(Right_Speed,0);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
   
}
void done()
{
  replaystage=1;
  replay();
 }
void shortPath(){
 int shortDone=0;
  if(path[pathLength-3]=='L' && path[pathLength-1]=='R')//IF THE path is  LBR it has to change to single path B
  {
    pathLength-=3;
    path[pathLength]='B';
    shortDone=1;
  }
   
  if(path[pathLength-3]=='L' && path[pathLength-1]=='S' && shortDone==0)//IF THE path is  LBS it has to change to single path R

  {
    pathLength-=3;
    path[pathLength]='R';
    shortDone=1;
  }
   
  if(path[pathLength-3]=='R' && path[pathLength-1]=='L' && shortDone==0)//IF THE path is  LBR it has to change to single path B
{
    pathLength-=3;
    path[pathLength]='B';
    shortDone=1;
  }
  
   
  if(path[pathLength-3]=='S' && path[pathLength-1]=='L' && shortDone==0)//IF THE path is  SBL it has to change to single path R

  {
    pathLength-=3;
    path[pathLength]='R';
    shortDone=1;
  }
     
  if(path[pathLength-3]=='S' && path[pathLength-1]=='S' && shortDone==0)//IF THE path is  SBS it has to change to single path B

  {
    pathLength-=3;
    path[pathLength]='B';
    shortDone=1;
  }
    if(path[pathLength-3]=='L' && path[pathLength-1]=='L' && shortDone==0)//IF THE path is  LBL it has to change to single path S 

    {
    pathLength-=3;
    path[pathLength]='S';
    shortDone=1;
  }
  
   pathLength++;
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

void Start() 
{
  analogWrite(Left_Speed,150);
  analogWrite(Right_Speed,150);
}
