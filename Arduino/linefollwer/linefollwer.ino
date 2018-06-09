int i[5];
String cmp;
void setup() 
{
  cmp=" ";
}

void loop() 
{
readInput();
setValues();
processValues();
setOutput();
}
void readInput()
{
  inp[0]=analogRead(S1);
  inp[1]=analogRead(S2);
  inp[2]=analogRead(S3);
  inp[3]=analogRead(S4);
  inp[4]=analogRead(S5);
}
void setValues()
{
  cmp=" ";
  for(int i=0;i<5;i++)
  {
    if(inp[i]>ThRESHOLD)
    cmp+="B";
    else
    cmp+="W";
  }
}

