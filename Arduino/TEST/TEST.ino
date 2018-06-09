#define  THRESHOLD 350
#define  S1     A0
#define  S2     A1
#define  S3     A2
#define  S4     A3
#define  S5     A4
#define  a1     8
#define  a2     9
#define  b1     12
#define  b2     13
#define  a_pwm  11
#define  b_pwm  10
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
    Serial.begin(9600);
   }

void loop()
   {
     Serial.println("wasdfghjk");
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
      Serial.print(cmp_value);
      Serial.print("\t");
   }

void processValues()   
   {
     if(cmp_value=="BBWBB" || cmp_value=="BWWWB" || cmp_value=="WWWWW")
       gofwd();
     else if(cmp_value=="BBWWB" || cmp_value=="BBBWW" || cmp_value=="BBBWB"|| cmp_value=="BWWWW"||cmp_value=="BBWWW")
       goright();
     else if(cmp_value=="BWWBB"|| cmp_value=="WWBBB" || cmp_value=="BWBBB" || cmp_value=="WWWWB" || cmp_value=="WWWBB")
       goleft();
     
     else
     stopM();
        }

void gofwd()
   {
     digitalWrite(a1,HIGH);
     digitalWrite(a2,LOW);
     digitalWrite(b1,HIGH);
     digitalWrite(b2,LOW);
     analogWrite(a_pwm,180);
     analogWrite(b_pwm,180);
     delay(50);
     Serial.print("GOING forward");
   }

void goleft()

   {
     digitalWrite(a1,HIGH);
     digitalWrite(a2,LOW);
     digitalWrite(b1,HIGH);
     digitalWrite(b2,LOW);
     analogWrite(a_pwm,100);
     analogWrite(b_pwm,180);
     delay(50);
     Serial.print("GOING left");
   }  


void goright()
   {
     digitalWrite(a1,HIGH);
     digitalWrite(a2,LOW);
     digitalWrite(b1,HIGH);
     digitalWrite(b2,LOW);
     analogWrite(a_pwm,180);
     analogWrite(b_pwm,100);
     delay(50);
     Serial.print("GOING right");
   }


   void stopM()
   {
     digitalWrite(a1,HIGH);
     digitalWrite(a2,LOW);
     digitalWrite(b1,HIGH);
     digitalWrite(b2,LOW);
     analogWrite(a_pwm,0);
     analogWrite(b_pwm,0);
     delay(50);
     Serial.print("stop");;
   }
     
    
