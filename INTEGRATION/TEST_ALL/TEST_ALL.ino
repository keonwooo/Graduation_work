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

void motor_move(){

  char ch = Serial.read();
  
  switch (ch) {
    
    case'a':
    Serial.println("원점");
    digitalWrite(encol,LOW);
    digitalWrite(enrow,LOW);
    motor_switch();
    break;
    
    case'b':
    Serial.println("기준점으로 이동");
    digitalWrite(encol,LOW); //세로모터 enable ON
    digitalWrite(enrow,LOW); //가로모터 enable ON
    digitalWrite(dirrow,LOW); //가로방향 시계방향
    digitalWrite(dircol,LOW); //세로방향 시계방향
    
    for(int y= 0; y<7000; y=y+1){
      digitalWrite(stcol,HIGH); delayMicroseconds(200);
      digitalWrite(stcol,LOW); delayMicroseconds(200);
    }
    for(int x= 0; x<1500; x=x+5){
      digitalWrite(strow,HIGH); delayMicroseconds(200);
      digitalWrite(strow,LOW); delayMicroseconds(200);
    }  
    digitalWrite(enrow,HIGH); //가로모터 enable OFF
    digitalWrite(encol,HIGH); //세로모터 enable OFF
    break;

    case'c':
    Serial.println("가로+1");
    digitalWrite(enrow,LOW);
    digitalWrite(dirrow,LOW);
    for(int x= 0; x<1000; x=x+5){
      digitalWrite(strow,HIGH); delayMicroseconds(500);
      digitalWrite(strow,LOW); delayMicroseconds(500);
    }
    digitalWrite(enrow,HIGH);
    delayMicroseconds(200);
    break;

    case'd':
    Serial.println("가로-1");
    digitalWrite(enrow,LOW);
    digitalWrite(dirrow,HIGH);
    for(int x= 0; x<1000; x=x+5){
      digitalWrite(strow,HIGH); delayMicroseconds(500);
      digitalWrite(strow,LOW); delayMicroseconds(500);
    }
    digitalWrite(enrow,HIGH);
    delayMicroseconds(200);
    break;

    case'e':
    Serial.println("세로+1");
    digitalWrite(encol,LOW);
    digitalWrite(dircol,LOW);
    for(int x= 0; x<1000; x=x+5){
      digitalWrite(stcol,HIGH); delayMicroseconds(500);
      digitalWrite(stcol,LOW); delayMicroseconds(500);
    }
    digitalWrite(encol,HIGH);
    delayMicroseconds(200);
    break;

    case'f':
    Serial.println("세로-1");
    digitalWrite(encol,LOW);
    digitalWrite(dircol,HIGH);
    for(int x= 0; x<1000; x=x+5){
      digitalWrite(stcol,HIGH); delayMicroseconds(500);
      digitalWrite(stcol,LOW); delayMicroseconds(500);
    }
    digitalWrite(encol,HIGH);
    delayMicroseconds(200);
    break;

    case'g':
    Serial.println("가로+0.5");
    digitalWrite(enrow,LOW);
    digitalWrite(dirrow,LOW);
    for(int x= 0; x<500; x=x+5){
      digitalWrite(strow,HIGH); delayMicroseconds(500);
      digitalWrite(strow,LOW); delayMicroseconds(500);
    }
    digitalWrite(enrow,HIGH);
    delayMicroseconds(200);
    break;

    case'h':
    Serial.println("가로-0.5");
    digitalWrite(enrow,LOW);
    digitalWrite(dirrow,HIGH);
    for(int x= 0; x<500; x=x+5){
      digitalWrite(strow,HIGH); delayMicroseconds(500);
      digitalWrite(strow,LOW); delayMicroseconds(500);
    }
    digitalWrite(enrow,HIGH);
    delayMicroseconds(200);
    break;

    case'i':
    Serial.println("세로+0.5");
    digitalWrite(encol,LOW);
    digitalWrite(dircol,LOW);
    for(int x= 0; x<500; x=x+5){
      digitalWrite(stcol,HIGH); delayMicroseconds(500);
      digitalWrite(stcol,LOW); delayMicroseconds(500);
    }
    digitalWrite(encol,HIGH);
    delayMicroseconds(200);
    break;

    case'j':
    Serial.println("세로-0.5");
    digitalWrite(encol,LOW);
    digitalWrite(dircol,HIGH);
    for(int x= 0; x<500; x=x+5){
      digitalWrite(stcol,HIGH); delayMicroseconds(500);
      digitalWrite(stcol,LOW); delayMicroseconds(500);
    }
    digitalWrite(encol,HIGH);
    delayMicroseconds(200);
    break;   
  }
}

void loop(){

  int matrix[8][8];
  
  for(int i=0; i<8; i++){
    for(int j=0; j<8; j++){
      matrix[i][j] = i*10+j+11;
    }
  }
  
  motor_switch();
  //원점으로 이동하는 함수
  
  motor_move();
  //입력에 따라 정해진 만큼 모터 이동시키는 함수

/*  String start = Serial.readString();
  for(int i=0; i<8; i++){
    for(int j=0; j<8; j++){
      if(start==String(matrix[i][j])){
        Serial.println("됨");
      }
    }
  }
  */
}
