void setup(){
  Serial.begin(9600);
}

void loop(){
  int matrix[8][8];
  String pt[8][8] =
    {
     {"A1","A2","A3","A4","A5","A6","A7","A8"},
     {"B1","B2","B3","B4","B5","B6","B7","B8"},
     {"C1","C2","C3","C4","C5","C6","C7","C8"},
     {"D1","D2","D3","D4","D5","D6","D7","D8"},
     {"E1","E2","E3","E4","E5","E6","E7","E8"},
     {"F1","F2","F3","F4","F5","F6","F7","F8"},
     {"G1","G2","G3","G4","G5","G6","G7","G8"},
     {"H1","H2","H3","H4","H5","H6","H7","H8"}
    };

  for(int i=0; i<8; i++){
    for(int j=0; j<8; j++){
      matrix[i][j] = i*10+j+11;
    }
  }
  
/*  for(int i=0; i<8; i++){
    for(int j=0; j<8; j++){
      Serial.print("["+String(i)+"]["+String(j)+"]:"+String(matrix[i][j])+" ");
      Serial.print(pt[i][j]+" ");
    }
    Serial.println();
  }
  while(true);
*/
if(Serial.available()){
  String a=Serial.readString();
if(a=="11"){
  Serial.println("A1");
}
else if(a=="12"){
  Serial.println("A2");
}
}
}
