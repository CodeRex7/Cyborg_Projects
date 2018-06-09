void setup() 
{
 pinMode(A7, INPUT); 
 Serial.begin(9600);
}

void loop() 
{
int x=analogRead(A7);
Serial.println(x);
delay(200);
}
