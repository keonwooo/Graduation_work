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
//x-y모터 스위치

int enrow = 9;
int strow = 8;
int dirrow = 7;
int encol = 6;
int stcol = 5;
int dircol = 4;
//x-y모터

int relay = 2;
//전자석

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

  pinMode(relay, OUTPUT);
}
//

void motor_ori(){
  
  if(digitalRead(Buttoncol)==1){
  digitalWrite(dircol,HIGH);
  digitalWrite(stcol,LOW); delayMicroseconds(200);  
  digitalWrite(stcol,HIGH); delayMicroseconds(200);
  }
  if(digitalRead(Buttoncol)==0){
    Serial.println("원점찍고 기준점으로 이동");
    for(int y=0; y<7400; y=y+1){
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
    for(int x=0; x<700; x=x+1){
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
    int first = start/100;    //숫자 4자리를 받아와서 앞에 두자리(말의 위치)
    int second = start%100;   //숫자 4자리를 받아와서 뒤에 두자리(이동할 위치)
    
    int Aquot = first/10;     //A  몫   가로 
    int Aremain = first%10;   //A 나머지 세로

    int Bquot = second/10;    //B  몫   가로
    int Bremain = second%10;  //B 나머지 세로

    int Aqaa = Aquot-1;       //가로
    int Araa = Aremain-1;     //세로

    for(int i=0; i<8; i++){
      for(int j=0; j<8; j++){
        matrix[i][j] = i*10+j+11;

        if(matrix[i][j]==first){

          if(origin==Aquot){
            if(origin==Aremain){
              Serial.println(String(matrix[i][j])+"위치");
            }

            else{
              Serial.println(String(matrix[i][j])+"위치");
              digitalWrite(enrow,LOW);
              digitalWrite(dirrow,LOW);
              delay(50);
              for(int x=0; x<Aremain*928; x=x+1){
                digitalWrite(strow,HIGH); delayMicroseconds(200);
                digitalWrite(strow,LOW); delayMicroseconds(200);
              }
            }
            digitalWrite(enrow,HIGH);
          }

          else if(origin==Aremain){
            Serial.println(String(matrix[i][j])+"위치");
            digitalWrite(encol,LOW);   //세로모터 enable ON
            digitalWrite(dircol,HIGH); //세로모터 아래쪽
            delay(50);
            for(int y=0; y<Aquot*928; y=y+1){
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
            delay(50);
            for(int y= 0; y<Aquot*928; y=y+1){
              digitalWrite(stcol,HIGH); delayMicroseconds(200);
              digitalWrite(stcol,LOW); delayMicroseconds(200);
            }
            for(int x= 0; x<Aremain*928; x=x+1){
              digitalWrite(strow,HIGH); delayMicroseconds(500);
              digitalWrite(strow,LOW); delayMicroseconds(500);
            }
            digitalWrite(enrow,HIGH); //가로모터 enable OFF
            digitalWrite(encol,HIGH); //세로모터 enable OFF
          }
        }
      }
    }
    delay(3000); // 말의위치에 도착해서 3초 기다리고 전자석 키고 이동
    
    digitalWrite(relay,HIGH); //전자석 ON

    int Mquot = Aquot - Bquot;
    int Mremain = Aremain - Bremain;

    int quotabs = abs(Mquot)+1;
    int remainabs = abs(Mremain)+1;

    digitalWrite(encol,LOW); //세로모터 enable ON
    digitalWrite(enrow,LOW); //가로모터 enable ON
    digitalWrite(dirrow,LOW); //가로방향 오른쪽
    digitalWrite(dircol,HIGH); //세로방향 아래쪽

    delay(50);
    
    for(int y= 0; y<464; y=y+1){
      digitalWrite(stcol,HIGH); delayMicroseconds(200);
      digitalWrite(stcol,LOW); delayMicroseconds(200);
    }
    for(int x= 0; x<464; x=x+1){
      digitalWrite(strow,HIGH); delayMicroseconds(200);
      digitalWrite(strow,LOW); delayMicroseconds(200);
    }
    digitalWrite(enrow,HIGH); //가로모터 enable OFF
    digitalWrite(encol,HIGH); //세로모터 enable OFF
    //반칸반칸 이동시키는 소스
    delay(3000);

    for(int i=0; i<8; i++){
      for(int j=0; j<8; j++){
        if(matrix[i][j]==second){
          
          if(Mquot<0){
            digitalWrite(encol,LOW); //세로모터 enable ON
            digitalWrite(dircol,HIGH); //세로모터 아래쪽
            delay(50);
            for(int y=0; y<quotabs*928; y=y+1){
              digitalWrite(stcol,HIGH); delayMicroseconds(200);
              digitalWrite(stcol,LOW); delayMicroseconds(200);
            }
            digitalWrite(encol,HIGH); //세로모터 enable OFF
          }
          else if(Mquot>0){
            digitalWrite(encol,LOW);  //세로모터 enable ON
            digitalWrite(dircol,LOW);//세로방향 위쪽
            delay(50);
            for(int y=0; y<quotabs*928; y=y+1){
              digitalWrite(stcol,HIGH); delayMicroseconds(200);
              digitalWrite(stcol,LOW); delayMicroseconds(200);
            }
            digitalWrite(encol,HIGH); //세로모터 enable OFF
          }
          else {
            Serial.println("행 동일");
          }
          if(Mremain<0){
            digitalWrite(enrow,LOW);  //가로모터 enable ON
            digitalWrite(dirrow,LOW);//가로모터 오른쪽
            delay(50);
            for(int x=0; x<remainabs*928; x=x+1){
              digitalWrite(strow,HIGH); delayMicroseconds(200);
              digitalWrite(strow,LOW); delayMicroseconds(200);
            }
            digitalWrite(enrow,HIGH);
          }
          else if(Mremain>0){
            digitalWrite(enrow,LOW);  //가로모터 enable ON
            digitalWrite(dirrow,HIGH);//가로모터 왼쪽
            delay(50);
            for(int x=0; x<remainabs*928; x=x+1){
              digitalWrite(strow,HIGH); delayMicroseconds(200);
              digitalWrite(strow,LOW); delayMicroseconds(200);
            }
            digitalWrite(enrow,HIGH);
          }
          else{
            Serial.println("열 동일");
          }
        }
      }
    }
    
    digitalWrite(encol,LOW); //세로모터 enable ON
    digitalWrite(enrow,LOW); //가로모터 enable ON
    digitalWrite(dirrow,HIGH); //가로방향 왼쪽
    digitalWrite(dircol,LOW); //세로방향 위쪽

    delay(50);
    
    for(int y= 0; y<464; y=y+1){
      digitalWrite(stcol,HIGH); delayMicroseconds(200);
      digitalWrite(stcol,LOW); delayMicroseconds(200);
    }
    for(int x= 0; x<464; x=x+1){
      digitalWrite(strow,HIGH); delayMicroseconds(200);
      digitalWrite(strow,LOW); delayMicroseconds(200);
    }
    //반칸반칸 이동시키는 소스
    
    digitalWrite(relay,LOW); //전자석 OFF
    delay(3000); //3초 뒤에 원점찍고 기준점으로
    motor_ori();
  }
}
