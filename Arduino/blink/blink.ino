void setup() 
{
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(12, LOW);
  digitalWrite(9, LOW);
}

void loop() 
{
  digitalWrite(13, HIGH);
  digitalWrite(10, LOW);
  delay(1000);
  digitalWrite(13, LOW);
  digitalWrite(10, HIGH);
  delay(1000);
}
