int leftsensor=2;
int nearleftsensor=3;
int centresensor_left=4;
int centresensor_right=5;
int nearrightsensor=6;
int rightsensor=7;
int ls,rs,csl,csr,nrs,nls;
int s=0b00000000;
float f;
float a;
int in1=8;
int in2=9;
int in3=12;
int in4=13;
int en1=11;
int en2=10;
int button =A5;
int led =A1;
void setup()
{
  
  pinMode(in1,OUTPUT);
  digitalWrite(in1,LOW);
  pinMode(in2,OUTPUT);
  digitalWrite(in2,LOW);
  pinMode(in3,OUTPUT);
  digitalWrite(in3,LOW);
  pinMode(in4,OUTPUT);
  digitalWrite(in4,LOW);
  pinMode(en1,OUTPUT);
  pinMode(en2,OUTPUT);
    digitalWrite(en1,HIGH);
    digitalWrite(en2,HIGH);
  pinMode(leftsensor,INPUT_PULLUP);
  pinMode(nearleftsensor,INPUT_PULLUP);
  pinMode(nearrightsensor,INPUT_PULLUP);
  pinMode(rightsensor,INPUT_PULLUP);
  pinMode(centresensor_left,INPUT_PULLUP);
  pinMode(centresensor_right,INPUT_PULLUP);
  Serial.begin(9600);
pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
pinMode(button,OUTPUT);
}



void loop()
{
  
  
while (1)
{
  sensor_read();
  if (s==0)
  {   //digitalWrite(button,HIGH);
          Serial.print(a);
        a=a;  
  ls=rs=nrs=nls=1;
}
  else
  { 
    f=((1.00*ls)+(2.00*nls)+(3.00*csl)+(4.00*csr)+(5.00*nrs)+(6.00*rs))/(ls+nls+csl+csr+nrs+rs+0.00);
    a=f;
     //Serial.print(f);
  }
  
  
  if(f ==3.50)
  { straight();}
  else if(f < 3.5)
  {
    if((ls+nls)==2 )
      {
        full_left();
      }
      else
      {
         slight_left();
      }
  }
  else if(a > 3.5)
   {
      if((rs+nrs)==2)
      {
         full_right();
      }
      else
      {
         slight_right();
      }
   }
   
   
   delay(50);
   mot_stop();
   delay(20);
}
}



//functions 
int sensor_read()
    { 
        ls=(digitalRead(leftsensor));
        nls=(digitalRead(nearleftsensor));
        csl=(digitalRead(centresensor_left));
        csr=(digitalRead(centresensor_right));
        rs=(digitalRead(rightsensor));
        nrs=(digitalRead(nearrightsensor));
        s=(ls+nls+csl+csr+rs+nrs);

  
/*  Serial.print("\t");
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
  Serial.print("\n");*/
        
    }   
    
//////motor logic functions
int slight_right()
    {
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);
      
     }
int full_right()
    {
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,HIGH);
      
    }
int slight_left()
    {
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
    }
int full_left()
    {
      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
    }
 int straight()
    {
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
    }
 int mot_stop() 
    {
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);
    }
