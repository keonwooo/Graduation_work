/*
 * 8x8배열 리드스위치 매트릭스
 * 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0
 */

void setup() {
Serial.begin(9600);
}

void scan_rows(uint8_t *rows){
  uint8_t i,j,b;
  for(i=0; i<8; i++){
    if(i)
    {
      pinMode(i+29,INPUT);
    }
    pinMode(i+30,OUTPUT);
    digitalWrite(i+30,LOW);  
    for(j=22; j<=29; j++){
      rows[i]<<=1;
      b=digitalRead(j);
      rows[i]|=1;
      Serial.print(" ");
      Serial.print(b);
      
    }
    Serial.println();
  }
}

void loop() {
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
  
  if(Serial.available()){
    if(Serial.read()=='a'){
      scan_rows(64);
      Serial.println();
    }
  }
}
