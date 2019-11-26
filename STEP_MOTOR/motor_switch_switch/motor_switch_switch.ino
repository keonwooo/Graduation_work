/*
 * 처음 시작하면 모터가 원점으로 돌아옴
 * 옮길 말의 위치와 옮길 위치를 입력하면
 * a = 원점에서 A1
 * b = x축 한칸 이동
 * c = y축 한칸 이동
 * d = x축 0.5칸 이동
 * e = y축 0.5칸 이동
 * 계산에 의해 말 이동시킴
*/
int Buttoncol=3;
int Buttonrow=12;

int enrow = 9;
int strow = 8;
int dirrow = 7;
int encol = 6;
int stcol = 5;
int dircol = 4;
//
void setup(){
  Serial.begin(9600);
  pinMode(encol,OUTPUT); //Enable
  pinMode(stcol,OUTPUT); //Step
  pinMode(dircol,OUTPUT); //방향 (HIGH반시계) (LOW시계)  col 세로
  pinMode(Buttoncol,INPUT_PULLUP);
  
  pinMode(enrow,OUTPUT); //Enable
  pinMode(strow,OUTPUT); //Step
  pinMode(dirrow,OUTPUT); //Direction   row 가로
  pinMode(Buttonrow,INPUT_PULLUP);
}
//

void motor_switch(){
  
  if(digitalRead(Buttoncol)==1){
  digitalWrite(dircol,HIGH); // 반시계방향
  digitalWrite(stcol, LOW); delayMicroseconds(200);  
  digitalWrite(stcol,HIGH); delayMicroseconds(200);
  }
  if(digitalRead(Buttoncol)==0){
    digitalWrite(encol,HIGH);
  }
  if(digitalRead(Buttonrow)==1) {
    digitalWrite(dirrow,HIGH);
    digitalWrite(strow,LOW); delayMicroseconds(200);
    digitalWrite(strow,HIGH); delayMicroseconds(200);
  }
  
  if(digitalRead(Buttonrow)==0){
    digitalWrite(enrow,HIGH);
  }
}

void loop(){
  
  motor_switch();
  
  char ch = Serial.read();
  
  switch (ch) {
    case'a':
    digitalWrite(encol,LOW); //세로모터 enable ON
    digitalWrite(enrow,LOW); //가로모터 enable ON
    digitalWrite(dirrow,LOW); //가로방향 시계방향
    digitalWrite(dircol,LOW); //세로방향 시계방향
    
    for(int x= 0; x<1000; x=x+5){
      digitalWrite(strow,HIGH); delayMicroseconds(200);
      digitalWrite(strow,LOW); delayMicroseconds(200);
      digitalWrite(stcol,HIGH); delayMicroseconds(200);
      digitalWrite(stcol,LOW); delayMicroseconds(200);
    }  
    digitalWrite(enrow,HIGH); //가로모터 enable OFF
    digitalWrite(encol,HIGH); //세로모터 enable OFF
    Serial.println("원점");
    break;

    case'b':
    Serial.println("가로 한칸+1");
    digitalWrite(enrow,LOW);
    digitalWrite(dirrow,LOW);
    for(int x= 0; x<1000; x=x+5){
      digitalWrite(strow,HIGH); delayMicroseconds(500);
      digitalWrite(strow,LOW); delayMicroseconds(500);
    }
    digitalWrite(enrow,HIGH);
    delayMicroseconds(200);
    break;

    case'c':
    Serial.println("세로 한칸+1");
    digitalWrite(encol,LOW);
    digitalWrite(dircol,LOW);
    for(int x= 0; x<1000; x=x+5){
      digitalWrite(stcol,HIGH); delayMicroseconds(500);
      digitalWrite(stcol,LOW); delayMicroseconds(500);
    }
    digitalWrite(encol,HIGH);
    delayMicroseconds(200);
    break;
  }
}
