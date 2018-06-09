#define  THRESHOLD 500
#define  S1     A0
#define  S2     A1
#define  S3     A2
#define  S4     A3
#define  S5     A4
#define  a1     4
#define  a2     5
#define  b1     6
#define  b2     7
#define  a_pwm  3
#define  b_pwm  9
int A[5],i;
String cmp_value;

void setup()
   {
    pinMode(a1,OUTPUT);
    pinMode(a2,OUTPUT);
    pinMode(b1,OUTPUT);
    pinMode(b2,OUTPUT);
    pinMode(a_pwm,OUTPUT);
    pinMode(b_pwm,OUTPUT);
    cmp_value="";
   }
void loop()
   {
     readInput();
     setValues();
     processValues();
   }
void readInput()
   {
     A[0]=analogRead(S1);
     A[1]=analogRead(S2);
     A[2]=analogRead(S3);
     A[3]=analogRead(S4);
     A[4]=analogRead(S5);
   }
void setValues()
   {
     cmp_value="";
     for(i=0;i<5;i++)
      {
       if(A[i]>THRESHOLD)
      cmp_value+="W";
     else
      cmp_value+="B"; 
      }
   }
void processValues()   
   {
     if(cmp_value=="BBWBB")
       gofwd();
     else if(cmp_value=="BBWWB")
       goright();
     else if(cmp_value=="BWWBB")
       goleft();
     else if(cmp_value=="WWWBB")
       gosharpleft();
     else if(cmp_value=="BBWWW")
     gosharpright();
   }
void gofwd()
   {
     digitalWrite(a1,HIGH);
     digitalWrite(a2,LOW);
     digitalWrite(b1,HIGH);
     digitalWrite(b2,LOW);
     analogWrite(a_pwm,255);
     analogWrite(b_pwm,255);
     delay(100);
   }
void goleft()

   {
     digitalWrite(a1,HIGH);
     digitalWrite(a2,LOW);
     digitalWrite(b1,HIGH);
     digitalWrite(b2,LOW);
     analogWrite(a_pwm,100);
     analogWrite(b_pwm,255);
     delay(100);
   }  
void gosharpleft()
   {
     digitalWrite(a1,LOW);
     digitalWrite(a2,HIGH);
     digitalWrite(b1,HIGH);
     digitalWrite(b2,LOW);
     analogWrite(a_pwm,100);
     analogWrite(b_pwm,255);
     delay(100);
   }
void goright()
   {
     digitalWrite(a1,HIGH);
     digitalWrite(a2,LOW);
     digitalWrite(b1,HIGH);
     digitalWrite(b2,LOW);
     analogWrite(a_pwm,255);
     analogWrite(b_pwm,100);
     delay(100);
   }
void gosharpright()
   {
     digitalWrite(a1,HIGH);
     digitalWrite(a2,LOW);
     digitalWrite(b1,HIGH);
     digitalWrite(b2,LOW);
     analogWrite(a_pwm,255);
     analogWrite(b_pwm,255);
     delay(100);
   }
    
   
