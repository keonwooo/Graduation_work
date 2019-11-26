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

const int origin = 1;
//
void setup(){
  Serial.begin(115200);
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

void motor_ori(){
  
  if(digitalRead(Buttoncol)==1){
  digitalWrite(dircol,HIGH);
  digitalWrite(stcol, LOW); delayMicroseconds(200);  
  digitalWrite(stcol,HIGH); delayMicroseconds(200);
  }
  if(digitalRead(Buttoncol)==0){
    Serial.println("원점찍고 기준점으로 이동");
    for(int y=0; y<7000; y=y+1){
      digitalWrite(dircol,LOW);
      digitalWrite(stcol,HIGH); delayMicroseconds(200);
      digitalWrite(stcol,LOW); delayMicroseconds(200);
    }
    digitalWrite(encol,HIGH);
  }
  if(digitalRead(Buttonrow)==1) {
    digitalWrite(dirrow,HIGH);
    digitalWrite(strow,LOW); delayMicroseconds(200);
    digitalWrite(strow,HIGH); delayMicroseconds(200);
  }
  
  if(digitalRead(Buttonrow)==0){
    for(int x=0; x<1500; x=x+5){
      digitalWrite(dirrow,LOW);
      digitalWrite(strow,HIGH); delayMicroseconds(200);
      digitalWrite(strow,LOW); delayMicroseconds(200);
    }
    digitalWrite(enrow,HIGH);
  }
}


void loop(){

  int matrix[8][8];
  
  motor_ori();
  //원점으로 이동하는 함수

  if(Serial.available()){

    int start = Serial.parseInt();

    for(int i=0; i<8; i++){
      for(int j=0; j<8; j++){
        matrix[i][j] = i*10+j+11;

        if(matrix[i][j]==start){

          int quot = start/10;   //  몫   가로 
          int remain = start%10; //나머지 세로

          if(origin==quot){
            if(origin==remain){
              Serial.println(String(matrix[i][j])+"위치");
            }

            else{
              Serial.println(String(matrix[i][j])+"위치");
              digitalWrite(enrow,LOW);
              digitalWrite(dirrow,LOW);
              delay(20);
              for(int x=0; x<remain*400; x=x+1){
                digitalWrite(strow,HIGH); delayMicroseconds(200);
                digitalWrite(strow,LOW); delayMicroseconds(200);
              }
            }
            digitalWrite(enrow,HIGH);
          }

          else if(origin==remain){
            Serial.println(String(matrix[i][j])+"위치");
            digitalWrite(encol,LOW);   //세로모터 enable ON
            digitalWrite(dircol,HIGH); //세로모터 아래쪽
            delay(20);
            for(int y=0; y<quot*400; y=y+1){
              digitalWrite(stcol,HIGH); delayMicroseconds(200);
              digitalWrite(stcol,LOW); delayMicroseconds(200);
            }
            digitalWrite(encol,HIGH);
          }

          else{
            Serial.println(String(matrix[i][j])+"위치");
            digitalWrite(encol,LOW); //세로모터 enable ON
            digitalWrite(enrow,LOW); //가로모터 enable ON
            digitalWrite(dirrow,LOW); //가로방향 오른쪽
            digitalWrite(dircol,HIGH); //세로방향 아래쪽
            delay(20);
            for(int y= 0; y<quot*400; y=y+1){
              digitalWrite(stcol,HIGH); delayMicroseconds(200);
              digitalWrite(stcol,LOW); delayMicroseconds(200);
            }
            for(int x= 0; x<remain*400; x=x+1){
              digitalWrite(strow,HIGH); delayMicroseconds(200);
              digitalWrite(strow,LOW); delayMicroseconds(200);
            }
            digitalWrite(enrow,HIGH); //가로모터 enable OFF
            digitalWrite(encol,HIGH); //세로모터 enable OFF
          }
        }
      }
    }
  }
}
