void setup() 
{
pinMode(13, OUTPUT);
pinMode(12, OUTPUT);
digitalWrite(12, LOW);
}
int x;
void loop() 
{
 for(x=0;x<255;x++)
 {
   analogWrite(13, x);
   delay(20);
 }
 for(;x>0;x--)
 {
   analogWrite(13, x);
   delay(20);
 }
}
