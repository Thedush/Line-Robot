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
int in3=10;
int in4=11;
int en1=12;
int en2=13;

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
pinMode(leftsensor,INPUT_PULLUP);
pinMode(nearleftsensor,INPUT_PULLUP);
pinMode(nearrightsensor,INPUT_PULLUP);
pinMode(rightsensor,INPUT_PULLUP);
pinMode(centresensor_left,INPUT_PULLUP);
pinMode(centresensor_right,INPUT_PULLUP);
}
void loop()
{
  digitalWrite(en1,HIGH);
  digitalWrite(en2,HIGH);
    sensor_read();
 if (s==00000)
  {
    a=a;
  }
 else
  { 
    f=((1*ls)+(2*nls)+(3*csl)+(4*csr)+(5*nrs)+(6*rs))/(ls+nls+csl+csr+nrs+rs);
    
    a=3.5-f;
     
   }
if( a==0)
 { straight();
 
 }
else if(a < 0)
{
  if(s==000011 || s==000111)
    {
      full_left();
    }
    else
    {
       slight_left();
    }
 }
else if(a > 0)
 {
    if(s==110000 ||s==111000)
    {
     full_right();
    }
  else
  {
     slight_right();
   }
 }
}
 
int sensor_read()
{ 
  ls=digitalRead(leftsensor);
   nls=digitalRead(nearleftsensor);
  csl=digitalRead(centresensor_left);
  csr=digitalRead(centresensor_right);
  rs=digitalRead(rightsensor);
  nrs=digitalRead(nearrightsensor);
  
   s=s|ls;
   s=s<<1;
   s=s|nls;
   s=s<<1;
   s=s|csl;
   s=s<<1;
   s=s|csr;
   s=s<<1;
   s=s|nrs;
   s=s<<1;
   s=s|rs;
}   
int slight_right()
{
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  delay(20);
}
int full_right()
{
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  delay(50);
}
int slight_left()
{digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(20);
}
int full_left()
{digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  delay(50);
 }
 int straight()
{digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  }
  
