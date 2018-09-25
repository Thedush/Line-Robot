#define Left_Dir1 9
#define Left_Dir2 8
#define Left_Speed  11 
#define Right_Dir1 13
#define Right_Dir2 12
#define Right_Speed 10
int leftsensor=2;
int nearleftsensor=3;
int centresensor_left=4;
int centresensor_right=5;
int nearrightsensor=6;
int rightsensor=7;
int integer=0;
float mem_avg=0;
  

float totalSensor = 0; // Total sensor readings
float avgSensor = 3.5; // Average sensor reading

float Kp = 102.00;   // Max deviation = 6-3.5 = 2.5 ||  255/2.5 = 102
float Ki = 0.00;
float Kd = 1.00;

float error = 0.00;
float previousError = 0.00;
float totalError = 0.00;

float power = 0.00;
int ls,rs,csl,csr,nrs,nls;
int PWM_Right, PWM_Left;

void setup()
{
 Serial.begin(9600);
   pinMode(leftsensor,INPUT_PULLUP);
  pinMode(nearleftsensor,INPUT_PULLUP);
  pinMode(nearrightsensor,INPUT_PULLUP);
  pinMode(rightsensor,INPUT_PULLUP);
  pinMode(centresensor_left,INPUT_PULLUP);
  pinMode(centresensor_right,INPUT_PULLUP);
 
  pinMode(Left_Dir1, OUTPUT);
  pinMode(Left_Dir2, OUTPUT);
  pinMode(Left_Speed, OUTPUT);
  pinMode(Right_Dir1, OUTPUT);
  pinMode(Right_Dir2, OUTPUT);
  pinMode(Right_Speed, OUTPUT);
  
  
  Stop();
  
  Forward();

 }

void loop()
{
   
   PID_program();
   // Serial.print( PWM_Left);
    Serial.println("");
    //Serial.print(PWM_Right);
   
   analogWrite(Left_Speed, PWM_Left);
   analogWrite(Right_Speed, PWM_Right); 

}


void Stop() 
{
  analogWrite(Left_Speed,0);
  analogWrite(Right_Speed, 0);
}
void PID_program()
{ 
   
    readSensor();
   // Serial.print("\t");
    //Serial.print(mem_avg);
    //Serial.print("\t");
   previousError = error; // save previous error for differential 
    error = mem_avg - 3.5; // Count how much robot deviate from center
    totalError += error; // Accumulate error for integral
    
     power = (Kp*error)+(Kd*(error-previousError))+(Ki*totalError);
     
    
    if( power>255 ) { power = 255.0; } 
    if( power<-255.0 ) { power = -255.0; }
    
    if(error<0) // Turn left
    {
      PWM_Right = 255;
      PWM_Left = 255 - abs(int(power));
    }

    else // Turn right
    {
      PWM_Right =255 - abs(int(power));
      PWM_Left = 255;
       
    }
   
}

void readSensor(void) {
   
         ls=!(digitalRead(leftsensor));
        nls=!(digitalRead(nearleftsensor));
        csl=!(digitalRead(centresensor_left));
        csr=!(digitalRead(centresensor_right));
        rs=!(digitalRead(rightsensor));
        nrs=!(digitalRead(nearrightsensor));
       totalSensor=(ls+nls+csl+csr+rs+nrs);
Serial.print("\t");
  Serial.print(ls);
  Serial.print("\t");
  Serial.print(nls);
  Serial.print("\t");
  Serial.print(csl);
  Serial.print("\t");
  Serial.print(csr);
  Serial.print("\t");
  Serial.print(nrs);
  Serial.print("\t");
  Serial.print(rs);
  Serial.print("\n");
  
  
 /*
  if(totalSensor==0)
    {
      
      mem_avg= mem_avg;
    if(mem_avg>3.5)
     {
      mem_avg=6.0;
      }
   else
    {
      mem_avg=1.0;
      }
    Serial.print(mem_avg);
    
    }
    else*/
    
    avgSensor =((1.00*ls)+(2.00*nls)+(3.00*csl)+(4.00*csr)+(5.00*nrs)+(6.00*rs))/(ls+nls+csl+csr+nrs+rs+0.00); ;
    mem_avg = avgSensor;
    
    
     avgSensor=0;
    totalSensor = 0;

}

void Forward()
{
   digitalWrite(Right_Dir1, LOW);
  digitalWrite(Right_Dir2, HIGH);
  digitalWrite(Left_Dir1, LOW);
  digitalWrite(Left_Dir2, HIGH);

}


