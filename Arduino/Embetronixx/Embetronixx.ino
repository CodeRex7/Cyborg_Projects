#define  THRESHOLD 400
#define  S1     A4
#define  S2     A3
#define  S3     A2
#define  S4     A1
#define  S5     A0
#define  a1     8
#define  a2     9
#define  b1     12
#define  b2     13
#define  a_pwm  10
#define  b_pwm  11
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
     Serial.println("hi NeMeSiS :D :D :D");
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
        Serial.print(A[i]);
        Serial.print("\t");
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
     else if(cmp_value=="BBWWW" || cmp_value=="BBBWW" || cmp_value=="BBBWB"|| cmp_value=="BBWWB")
       goright();
     else if(cmp_value=="WWWBB"|| cmp_value=="WWBBB" || cmp_value=="BWBBB"|| cmp_value=="BWWBB")
       goleft();
     else if(cmp_value=="WWWWB")
       gosharpleft();
     else if(cmp_value=="BWWWW")
     gosharpright();
     else
     stopM();
        }

void gofwd()
   {
     digitalWrite(a1,HIGH);
     digitalWrite(a2,LOW);
     digitalWrite(b1,HIGH);
     digitalWrite(b2,LOW);
     analogWrite(a_pwm,130);
     analogWrite(b_pwm,130);
     delay(40);
     Serial.print("GOING forward\n");
   }

void goleft()

   {
     digitalWrite(a1,HIGH);
     digitalWrite(a2,LOW);
     digitalWrite(b1,HIGH);
     digitalWrite(b2,LOW);
     analogWrite(a_pwm,80);
     analogWrite(b_pwm,130);
     delay(25);
     Serial.print("GOING left\n");
        }  


void goright()
   {
     digitalWrite(a1,HIGH);
     digitalWrite(a2,LOW);
     digitalWrite(b1,HIGH);
     digitalWrite(b2,LOW);
     analogWrite(a_pwm,130);
     analogWrite(b_pwm,80);
     delay(25);
     Serial.print("GOING right\n");
   }


   void stopM()
   {
     digitalWrite(a1,HIGH);
     digitalWrite(a2,LOW);
     digitalWrite(b1,HIGH);
     digitalWrite(b2,LOW);
     analogWrite(a_pwm,0);
     analogWrite(b_pwm,0);
     delay(100);
     Serial.print("stop\n");
   }
     
     void gosharpright()
     {
       digitalWrite(a1,HIGH);
       digitalWrite(a2,LOW);
       digitalWrite(b1,HIGH);
       digitalWrite(b2,LOW);
       analogWrite(a_pwm,150);
       analogWrite(b_pwm,150);
       delay(60);
       do
       {
         digitalWrite(a1,HIGH);
     digitalWrite(a2,LOW);
     digitalWrite(b1,LOW);
     digitalWrite(b2,HIGH);
     analogWrite(a_pwm,120);
     analogWrite(b_pwm,100);
     delay(50);
     readInput();
     setValues();
     Serial.print("GOING SHARP RIGHT\n");
      digitalWrite(a1,HIGH);
     digitalWrite(a2,LOW);
     digitalWrite(b1,HIGH);
     digitalWrite(b2,LOW);
     analogWrite(a_pwm,0);
     analogWrite(b_pwm,0);
     delay(50);
     if(cmp_value=="BWWWB"||cmp_value=="BBWBB")
           break;
       }while (1);
      allign();
     }
     
     void gosharpleft()
     {
       digitalWrite(a1,HIGH);
       digitalWrite(a2,LOW);
       digitalWrite(b1,HIGH);
       digitalWrite(b2,LOW);
       analogWrite(a_pwm,150);
       analogWrite(b_pwm,150);
       delay(60);
       do
       {
         digitalWrite(b1,HIGH);
     digitalWrite(b2,LOW);
     digitalWrite(a1,LOW);
     digitalWrite(a2,HIGH);
     analogWrite(a_pwm,120);
     analogWrite(b_pwm,100);
      delay(50);
     readInput();
     setValues();
     Serial.print("GOING SHARP LEFT\n");
     digitalWrite(a1,HIGH);
     digitalWrite(a2,LOW);
     digitalWrite(b1,HIGH);
     digitalWrite(b2,LOW);
     analogWrite(a_pwm,0);
     analogWrite(b_pwm,0);
     delay(50);
     if(cmp_value=="BWWWB" || cmp_value=="BBWBB")
           break;
       }while (1);
       allign();
     }
     
     void allign()
     {
       readInput();
       setValues();
       if(cmp_value=="BBWBB" || cmp_value=="BWWWB" || cmp_value=="WWWWW")
       {
         digitalWrite(a1,HIGH);
     digitalWrite(a2,LOW);
     digitalWrite(b1,HIGH);
     digitalWrite(b2,LOW);
     analogWrite(a_pwm,75);
     analogWrite(b_pwm,75);
     delay(50);
       }
     else if(cmp_value=="BBWWW" || cmp_value=="BBBWW" || cmp_value=="BBBWB"|| cmp_value=="BBWWB"||cmp_value=="BWWWW")
       {
         digitalWrite(a1,HIGH);
     digitalWrite(a2,LOW);
     digitalWrite(b1,HIGH);
     digitalWrite(b2,LOW);
     analogWrite(a_pwm,75);
     analogWrite(b_pwm,50);
     delay(50);
       }
     else if(cmp_value=="WWWBB"|| cmp_value=="WWBBB" || cmp_value=="BWBBB"|| cmp_value=="BWWBB"|| cmp_value=="WWWWB")
       {
         digitalWrite(a1,HIGH);
     digitalWrite(a2,LOW);
     digitalWrite(b1,HIGH);
     digitalWrite(b2,LOW);
     analogWrite(a_pwm,50);
     analogWrite(b_pwm,75);
     delay(50);
       }
       
     }
