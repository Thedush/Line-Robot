int pin_s2=2;
int pin_s3=3;
int pin_s4=4;
int pin_s5=5;
int pin_s6=6;
int pin_s7=7;
int s1= 0,s2=0,s3=0,s4=0,s5=0,s6=0,s7=0;
void setup() 
{//configure pins as an input and enable the internal pull-up resistor
  
  pinMode(pin_s2,INPUT_PULLUP);
  pinMode(pin_s3,INPUT_PULLUP);
   pinMode(pin_s4,INPUT_PULLUP);
  pinMode(pin_s5,INPUT_PULLUP);
 pinMode(pin_s6,INPUT_PULLUP);
  pinMode(pin_s7,INPUT_PULLUP);
   Serial.begin(9600);
}

void loop()
{
  //read the sensor value into a variable
  
   s2=!digitalRead(pin_s2);
   s3=!digitalRead(pin_s3);
   s4=!digitalRead(pin_s4);
   s5=!digitalRead(pin_s5);
   s6=!digitalRead(pin_s6);
   s7=!digitalRead(pin_s7);
   //print out the value in serial board
 Serial.print(s2);
  Serial.print("\t");
  Serial.print(s3);
  Serial.print("\t");
  Serial.print(s4);
  Serial.print("\t");
  Serial.print(s5);
  Serial.print("\t");
  Serial.print(s6);
  Serial.print("\t");
  Serial.print(s7);
  Serial.print("\n");
  delay(100);
}
