int Button=11;
//
int flag=1;
//
void setup(){
  Serial.begin(9600);
  pinMode(6,OUTPUT); //Enable
  pinMode(5,OUTPUT); //Step
  pinMode(4,OUTPUT); //Direction
  pinMode(Button,INPUT_PULLUP);
  digitalWrite(6,LOW);
}
//
void loop(){
  if(flag){
    digitalWrite(4,HIGH); // 반시계방향?
    digitalWrite(5,LOW ); delayMicroseconds(500);  
    digitalWrite(5,HIGH); delayMicroseconds(500);
  }
  //
  if(digitalRead(Button)==0){
    Serial.println("Stop");
    flag=0;
  }
}
