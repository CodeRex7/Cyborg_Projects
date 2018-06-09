int i,A[5];
void setup() 
{
Serial.begin(9600);  
}

void loop() 
{
 A[0]=analogRead(A7);
 A[1]=analogRead(A6);
 A[2]=analogRead(A5);
 A[3]=analogRead(A4);
 A[4]=analogRead(A3);
   for(i=0;i<5;i++)
   {
      Serial.print(A[i]);
      Serial.print("\t");
   }
      Serial.println();
 delay(500);
}
