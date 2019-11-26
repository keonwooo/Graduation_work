void setup() {
pinMode(2, INPUT_PULLUP);  //세로(빨강)
pinMode(3, INPUT_PULLUP);
pinMode(4, INPUT_PULLUP);
pinMode(5, INPUT_PULLUP);
pinMode(6, INPUT_PULLUP);
pinMode(7, INPUT_PULLUP);
pinMode(8, INPUT_PULLUP);
pinMode(9, INPUT_PULLUP);
pinMode(10, INPUT);        //가로(검정)
pinMode(11, INPUT);
pinMode(12, INPUT);
pinMode(13, INPUT);
pinMode(14, INPUT); //A0
pinMode(15, INPUT); //A1
pinMode(16, INPUT); //A2
pinMode(17, INPUT); //A3
pinMode(18, INPUT); //A4
Serial.begin(9600);
}

void scan_rows(uint8_t *rows){
  uint8_t i,j,b;
  for(i=0; i<8; i++){
    if(i)
    {
      pinMode(i+9,INPUT);
    }
    pinMode(i+10,OUTPUT);
    digitalWrite(i+10,LOW);  
    for(j=2; j<=9; j++){
      rows[i]<<=1;
      b=digitalRead(j);
      rows[i]|=b;
      Serial.print(b);
    }
    Serial.println();
  }
}

void loop() {
  if(Serial.available()){
    if(Serial.read()=='a'){
      scan_rows(64);
      Serial.println();
    }
  }
}
