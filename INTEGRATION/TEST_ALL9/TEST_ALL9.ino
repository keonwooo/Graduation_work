/*
 * 처음 시작하면 모터가 원점찍고 기준점(A1)으로 이동
 * 옮길 말의 위치와 옮길 위치를 입력하면
 * 계산에 의해 말 이동시킴
*/
int Buttoncol=15;
int Buttonrow=12;
//x-y모터 스위치

int enrow = 9;
int strow = 8;
int dirrow = 7;
int encol = 6;
int stcol = 5;
int dircol = 4;
//x-y모터

int relay = 11;
//전자석

const int origin = 1;
const int Line8 = 8;
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

  digitalWrite(relay, HIGH);

  Serial.setTimeout(20);
  
  scan_rows(129);
}
//

void scan_rows(uint8_t *rows){
  
  uint8_t z,u,b;
  
  for(z=0; z<8; z++){
    if(z)
    {
      pinMode(z+29,INPUT);
    }
    pinMode(z+30,OUTPUT);
    digitalWrite(z+30,LOW);  
    for(u=22; u<=29; u++){
      rows[z]<<=1;
      b=digitalRead(u);
      rows[z]|=1;
      Serial.print(" ");
      Serial.print(b);
      
    }
    Serial.println();
  }
}

void motor_ori(){
  
  if(digitalRead(Buttoncol)==1){
  digitalWrite(dircol,HIGH);
  digitalWrite(stcol,LOW); delayMicroseconds(200);  
  digitalWrite(stcol,HIGH); delayMicroseconds(200);
  }
  if(digitalRead(Buttoncol)==0){
    Serial.println("원점찍고 기준점으로 이동");
    for(int y=0; y<7368; y++){
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
    for(int x=0; x<700; x++){
      digitalWrite(dirrow,LOW);
      digitalWrite(strow,HIGH); delayMicroseconds(200);
      digitalWrite(strow,LOW); delayMicroseconds(200);
    }
    digitalWrite(enrow,HIGH);
  }
}

void motor_halfLD(){
  digitalWrite(encol,LOW); //세로모터 enable ON
  digitalWrite(enrow,LOW); //가로모터 enable ON
  digitalWrite(dirrow,HIGH); //가로방향 왼쪽
  digitalWrite(dircol,HIGH); //세로방향 아래쪽

  delay(300);
    
  for(int y= 0; y<512; y++){
    digitalWrite(stcol,HIGH); delayMicroseconds(200);
    digitalWrite(stcol,LOW); delayMicroseconds(200);
    }
    for(int x= 0; x<512; x++){
      digitalWrite(strow,HIGH); delayMicroseconds(200);
      digitalWrite(strow,LOW); delayMicroseconds(200);
    }
    digitalWrite(enrow,HIGH); //가로모터 enable OFF
    digitalWrite(encol,HIGH); //세로모터 enable OFF
    //반칸반칸 이동시키는 소스
}

void motor_halfRU(){
  digitalWrite(encol,LOW); //세로모터 enable ON
  digitalWrite(enrow,LOW); //가로모터 enable ON
  digitalWrite(dirrow,LOW); //가로방향 오른쪽
  digitalWrite(dircol,LOW); //세로방향 위쪽

  delay(300);
    
  for(int y= 0; y<512; y++){
    digitalWrite(stcol,HIGH); delayMicroseconds(200);
    digitalWrite(stcol,LOW); delayMicroseconds(200);
    }
    for(int x= 0; x<512; x++){
      digitalWrite(strow,HIGH); delayMicroseconds(200);
      digitalWrite(strow,LOW); delayMicroseconds(200);
    }
    digitalWrite(enrow,HIGH); //가로모터 enable OFF
    digitalWrite(encol,HIGH); //세로모터 enable OFF
    //반칸반칸 이동시키는 소스
}

void motor_halfLU(){
  digitalWrite(encol,LOW); //세로모터 enable ON
  digitalWrite(enrow,LOW); //가로모터 enable ON
  digitalWrite(dirrow,HIGH); //가로방향 왼쪽
  digitalWrite(dircol,LOW); //세로방향 위쪽

  delay(300);
    
  for(int y= 0; y<512; y++){
    digitalWrite(stcol,HIGH); delayMicroseconds(200);
    digitalWrite(stcol,LOW); delayMicroseconds(200);
    }
    for(int x= 0; x<512; x++){
      digitalWrite(strow,HIGH); delayMicroseconds(200);
      digitalWrite(strow,LOW); delayMicroseconds(200);
    }
    digitalWrite(enrow,HIGH); //가로모터 enable OFF
    digitalWrite(encol,HIGH); //세로모터 enable OFF
    //반칸반칸 이동시키는 소스
}

void motor_halfRD(){
  digitalWrite(encol,LOW); //세로모터 enable ON
  digitalWrite(enrow,LOW); //가로모터 enable ON
  digitalWrite(dirrow,LOW); //가로방향 오른쪽
  digitalWrite(dircol,HIGH); //세로방향 아래쪽

  delay(300);
    
  for(int y= 0; y<512; y++){
    digitalWrite(stcol,HIGH); delayMicroseconds(200);
    digitalWrite(stcol,LOW); delayMicroseconds(200);
    }
    for(int x= 0; x<512; x++){
      digitalWrite(strow,HIGH); delayMicroseconds(200);
      digitalWrite(strow,LOW); delayMicroseconds(200);
    }
    digitalWrite(enrow,HIGH); //가로모터 enable OFF
    digitalWrite(encol,HIGH); //세로모터 enable OFF
    //반칸반칸 이동시키는 소스
}

void loop(){

  int matrix[8][8];

  pinMode(22, INPUT_PULLUP);  //세로(빨강)
  pinMode(23, INPUT_PULLUP);
  pinMode(24, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  pinMode(27, INPUT_PULLUP);
  pinMode(28, INPUT_PULLUP);
  pinMode(29, INPUT_PULLUP);
  pinMode(30, INPUT);        //가로(검정)
  pinMode(31, INPUT);
  pinMode(32, INPUT);
  pinMode(33, INPUT);
  pinMode(34, INPUT); //A0
  pinMode(35, INPUT); //A1
  pinMode(36, INPUT); //A2
  pinMode(37, INPUT); //A3
  pinMode(38, INPUT); //A4
  
  motor_ori();
  //원점으로 이동하는 함수

  if(Serial.available()){

    String start = Serial.readString();
    char firsttext = start.charAt(0)-64;  //문자를 숫자로 변환
    char firstnum = start.charAt(1)-48;
    char secondtext = start.charAt(2)-64;
    char secondnum = start.charAt(3)-48;

    int first = (firsttext*10)+firstnum;
    int second = (secondtext*10)+secondnum;

    int Aquot = firsttext;
    int Aremain = firstnum;

    int Bquot = secondtext;
    int Bremain = secondnum;

    int Aqaa = Aquot-1;
    int Araa = Aremain-1;

    int Mquot = Aquot - Bquot;
    int Mremain = Aremain - Bremain;

    int quotabs = abs(Mquot);
    int remainabs = abs(Mremain);
    
    for(int i=0; i<8; i++){
      for(int j=0; j<8; j++){
        matrix[i][j] = i*10+j+11;

        if(matrix[i][j]==first){

          if(origin==Aquot){
            if(origin==Aremain){
              Serial.println(String(start.charAt(0))+String(start.charAt(1))+"위치에서");
            }

            else{
              Serial.println(String(start.charAt(0))+String(start.charAt(1))+"위치에서");
              digitalWrite(enrow,LOW);
              digitalWrite(dirrow,LOW);
              delay(50);
              for(int x=0; x<Araa*1024; x++){
                digitalWrite(strow,HIGH); delayMicroseconds(200);
                digitalWrite(strow,LOW); delayMicroseconds(200);
              }
            }
            digitalWrite(enrow,HIGH);
          }

          else if(origin==Aremain){
            Serial.println(String(start.charAt(0))+String(start.charAt(1))+"위치에서");
            digitalWrite(encol,LOW);   //세로모터 enable ON
            digitalWrite(dircol,HIGH); //세로모터 아래쪽
            delay(50);
            for(int y=0; y<Aqaa*1024; y++){
              digitalWrite(stcol,HIGH); delayMicroseconds(200);
              digitalWrite(stcol,LOW); delayMicroseconds(200);
            }
            digitalWrite(encol,HIGH);
          }

          else{
            Serial.println(String(start.charAt(0))+String(start.charAt(1))+"위치에서");
            digitalWrite(encol,LOW); //세로모터 enable ON
            digitalWrite(enrow,LOW); //가로모터 enable ON
            digitalWrite(dirrow,LOW); //가로방향 오른쪽
            digitalWrite(dircol,HIGH); //세로방향 아래쪽
            delay(50);
            for(int y= 0; y<Aqaa*1024; y++){
              digitalWrite(stcol,HIGH); delayMicroseconds(200);
              digitalWrite(stcol,LOW); delayMicroseconds(200);
            }
            for(int x= 0; x<Araa*1024; x++){
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
    
    digitalWrite(relay,LOW); //전자석 ON

    if(Line8==Aquot){
      if(Line8==Bquot){

        motor_halfLU();
        delay(1000);
        Serial.println(String(start.charAt(2))+String(start.charAt(3))+"위치로 이동");
        
        for(int i=0; i<8; i++){
          for(int j=0; j<8; j++){
            if(matrix[i][j]==second){
              if(Mremain<0){
                digitalWrite(enrow,LOW);  //가로모터 enable ON
                digitalWrite(dirrow,LOW);//가로모터 오른쪽
                delay(50);
                for(int x=0; x<remainabs*1024; x++){
                  digitalWrite(strow,HIGH); delayMicroseconds(200);
                  digitalWrite(strow,LOW); delayMicroseconds(200);
                }
                digitalWrite(enrow,HIGH);
              }
              else if(Mremain>0){
                digitalWrite(enrow,LOW);  //가로모터 enable ON
                digitalWrite(dirrow,HIGH);//가로모터 왼쪽
                delay(50);
                for(int x=0; x<remainabs*1024; x++){
                  digitalWrite(strow,HIGH); delayMicroseconds(200);
                  digitalWrite(strow,LOW); delayMicroseconds(200);
                }
                digitalWrite(enrow,HIGH);
              }
            }
          }
        }
        motor_halfRD();
      }
      
      else{

        motor_halfLU();
        delay(1000);
        Serial.println(String(start.charAt(2))+String(start.charAt(3))+"위치로 이동");
        
        for(int i=0; i<8; i++){
          for(int j=0; j<8; j++){
            if(matrix[i][j]==second){
              if(Mquot>0){
                digitalWrite(encol,LOW);  //세로모터 enable ON
                digitalWrite(dircol,LOW);//세로방향 위쪽
                delay(50);
                for(int y=0; y<(quotabs-1)*1024; y++){
                  digitalWrite(stcol,HIGH); delayMicroseconds(200);
                  digitalWrite(stcol,LOW); delayMicroseconds(200);
                }
                digitalWrite(encol,HIGH); //세로모터 enable OFF
              }
              
              if(Mremain<0){
                digitalWrite(enrow,LOW);  //가로모터 enable ON
                digitalWrite(dirrow,LOW);//가로모터 오른쪽
                delay(50);
                for(int x=0; x<remainabs*1024; x++){
                  digitalWrite(strow,HIGH); delayMicroseconds(200);
                  digitalWrite(strow,LOW); delayMicroseconds(200);
                }
                digitalWrite(enrow,HIGH);
              }
              else if(Mremain>0){
                digitalWrite(enrow,LOW);  //가로모터 enable ON
                digitalWrite(dirrow,HIGH);//가로모터 왼쪽
                delay(50);
                for(int x=0; x<remainabs*1024; x++){
                  digitalWrite(strow,HIGH); delayMicroseconds(200);
                  digitalWrite(strow,LOW); delayMicroseconds(200);
                }
                digitalWrite(enrow,HIGH);
              }
            }
          }
        }
        motor_halfRU();
      }
    }
    
    else{
      if(Line8==Bquot){

        motor_halfLD();
        delay(1000);
        Serial.println(String(start.charAt(2))+String(start.charAt(3))+"위치로 이동");
        
        for(int i=0; i<8; i++){
          for(int j=0; j<8; j++){
            if(matrix[i][j]==second){
              if(Mquot<0){
                digitalWrite(encol,LOW); //세로모터 enable ON
                digitalWrite(dircol,HIGH); //세로모터 아래쪽
                delay(50);
                for(int y=0; y<(quotabs-1)*1024; y++){
                  digitalWrite(stcol,HIGH); delayMicroseconds(200);
                  digitalWrite(stcol,LOW); delayMicroseconds(200);
                }
                digitalWrite(encol,HIGH); //세로모터 enable OFF
              }
              
              if(Mremain<0){
                digitalWrite(enrow,LOW);  //가로모터 enable ON
                digitalWrite(dirrow,LOW);//가로모터 오른쪽
                delay(50);
                for(int x=0; x<remainabs*1024; x++){
                  digitalWrite(strow,HIGH); delayMicroseconds(200);
                  digitalWrite(strow,LOW); delayMicroseconds(200);
                }
                digitalWrite(enrow,HIGH);
              }
              else if(Mremain>0){
                digitalWrite(enrow,LOW);  //가로모터 enable ON
                digitalWrite(dirrow,HIGH);//가로모터 왼쪽
                delay(50);
                for(int x=0; x<remainabs*1024; x++){
                  digitalWrite(strow,HIGH); delayMicroseconds(200);
                  digitalWrite(strow,LOW); delayMicroseconds(200);
                }
                digitalWrite(enrow,HIGH);
              }
            }
          }
        }
        motor_halfRD();
      }
      
      else{
        
        motor_halfLD();
        delay(1000);
        Serial.println(String(start.charAt(2))+String(start.charAt(3))+"위치로 이동");

        for(int i=0; i<8; i++){
          for(int j=0; j<8; j++){
            if(matrix[i][j]==second){
              if(Mquot<0){
                digitalWrite(encol,LOW); //세로모터 enable ON
                digitalWrite(dircol,HIGH); //세로모터 아래쪽
                delay(50);
                for(int y=0; y<quotabs*1024; y++){
                  digitalWrite(stcol,HIGH); delayMicroseconds(200);
                  digitalWrite(stcol,LOW); delayMicroseconds(200);
                }
                digitalWrite(encol,HIGH); //세로모터 enable OFF
              }
              else if(Mquot>0){
                digitalWrite(encol,LOW);  //세로모터 enable ON
                digitalWrite(dircol,LOW);//세로방향 위쪽
                delay(50);
                for(int y=0; y<quotabs*1024; y++){
                  digitalWrite(stcol,HIGH); delayMicroseconds(200);
                  digitalWrite(stcol,LOW); delayMicroseconds(200);
                }
                digitalWrite(encol,HIGH); //세로모터 enable OFF
              }
              if(Mremain<0){
                digitalWrite(enrow,LOW);  //가로모터 enable ON
                digitalWrite(dirrow,LOW);//가로모터 오른쪽
                delay(50);
                for(int x=0; x<remainabs*1024; x++){
                  digitalWrite(strow,HIGH); delayMicroseconds(200);
                  digitalWrite(strow,LOW); delayMicroseconds(200);
                }
                digitalWrite(enrow,HIGH);
              }
              else if(Mremain>0){
                digitalWrite(enrow,LOW);  //가로모터 enable ON
                digitalWrite(dirrow,HIGH);//가로모터 왼쪽
                delay(50);
                for(int x=0; x<remainabs*1024; x++){
                  digitalWrite(strow,HIGH); delayMicroseconds(200);
                  digitalWrite(strow,LOW); delayMicroseconds(200);
                }
                digitalWrite(enrow,HIGH);
              }
            }
          }
        }
        motor_halfRU();
      }
    }
    delay(3000);
    digitalWrite(relay,HIGH); //전자석 OFF
    delay(500); //0.5초 뒤에 원점찍고 기준점으로
    digitalWrite(encol,LOW);
    digitalWrite(enrow,LOW);
    motor_ori();
    scan_rows(129);
  }
}
