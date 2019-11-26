/*
 * 원점으로 가는 모터 제어 부분
*/
int Buttoncol=3;
int Buttonrow=12;
//
int flagrow=1;
int flagcol=1;
//
void setup(){
  Serial.begin(9600);
  pinMode(6,OUTPUT); //Enable
  pinMode(5,OUTPUT); //Step
  pinMode(4,OUTPUT); //Direction   col
  pinMode(Buttoncol,INPUT_PULLUP);
  
  pinMode(9,OUTPUT); //Enable
  pinMode(8,OUTPUT); //Step
  pinMode(7,OUTPUT); //Direction   row
  pinMode(Buttonrow,INPUT_PULLUP);
  
  digitalWrite(6,LOW);
  digitalWrite(9,LOW);
  
}
//
void loop(){
  if(digitalRead(Buttoncol)==1){
    digitalWrite(4,HIGH); // 반시계방향?
    digitalWrite(5,LOW ); delayMicroseconds(200);  
    digitalWrite(5,HIGH); delayMicroseconds(200);
  }
  if(digitalRead(Buttoncol)==0){
    digitalWrite(6,HIGH);
  }
  if(digitalRead(Buttonrow)==1) {
    digitalWrite(7,HIGH);
    digitalWrite(8,LOW); delayMicroseconds(200);
    digitalWrite(8,HIGH); delayMicroseconds(200);
  }
  
  if(digitalRead(Buttonrow)==0){
    digitalWrite(9,HIGH);
  }
}
