void setup() 
{
pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
pinMode(10, OUTPUT);
}

void loop() 
{
  digitalWrite(2, HIGH);
  digitalWrite(7, LOW);
  delay(500);
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(8, LOW);
  delay(500);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(9, LOW);
  delay(500);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(10, LOW);
  delay(500);
  digitalWrite(5, LOW);
}
