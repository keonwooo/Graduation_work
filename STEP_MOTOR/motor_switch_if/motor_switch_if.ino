int Index;
int Button = 12;

void setup() 
{
  Serial.begin(9600);
  pinMode(6, OUTPUT); //Enable
  pinMode(5, OUTPUT); //Step
  pinMode(4, OUTPUT); //Direction
  pinMode(Button, INPUT_PULLUP);

  digitalWrite(6,LOW);
}

void loop() 
{
  int SW = digitalRead(Button);
  Serial.println(SW);

  if(SW == 1) {
    for(Index = 0; Index < 200; Index++)
    {
      digitalWrite(4,HIGH);
      digitalWrite(5,HIGH);
      delayMicroseconds(500);
      digitalWrite(5,LOW);
      delayMicroseconds(500);
    }
  }
}
