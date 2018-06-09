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
     digitalWrite(a1,LOW);
     digitalWrite(a2,HIGH);
      analogWrite(a_pwm,255);
      delay(3000);
      digitalWrite(a1,HIGH);
     digitalWrite(a2,LOW);
      analogWrite(a_pwm,255);
      delay(3000);
   }
