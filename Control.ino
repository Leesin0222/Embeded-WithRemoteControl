void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  attachInterrupt(0, remoconISR, FALLING);
  
  for(int i = 0; i<8;i++)
    pinMode(i+4, OUTPUT);
  
  for(int i = 0; i<2;i++){
    for(int j = 0;j<8;j++)
      digitalWrite(4+j, HIGH);
    delay(337);
    for(int j = 0;j<8;j++)
      digitalWrite(4+j, LOW);
    delay(337);
  }
}

void loop() {

}
int remocount;
unsigned long micro[50];
unsigned int diff[33];
int databit[32];
byte databyte = 0;
unsigned int numhex[10]={0x16, 0x0C, 0x18, 0x5E, 0x08, 0x1C, 0x5A, 0x42, 0x52, 0x4A};
int remonum;

int fnd[8] = {0,0,0,0,1,1,0,1};

void remoconISR() {
  micro[remocount] = micros();
  
  if(remocount > 0){
    diff[remocount-1] = micro[remocount] - micro[remocount-1];

    if(diff[remocount-1] > 12500&& diff[remocount-1] < 14500)
      remocount = 1;
      
    if(diff[remocount-1] > 10500&& diff[remocount-1] < 12500){
      remocount = -1;
      //Serial.println("R");
      
      //Serial.println(remonum);
      }
  }
  remocount++;

  
  if(remocount == 34){
    remocount = 0;
    /*
    for(int i = 0; i<34;i++){
      Serial.print(i); 
      Serial.print(" : "); 
      Serial.println(micro[i]);
    }
    */
    for(int i = 0; i<32;i++){
      if(diff[i+1] > 1000 && diff[i+1] < 1500){
        databit[i] = 0;
      }
      else if(diff[i+1] > 2000 && diff[i+1] < 2500){
        databit[i] = 1;
      }
    }

    for(int i = 0; i<8;i++){
      databyte= databyte >> 1;
      
      if(databit[16+i]==1){
        databyte |= 0x80;
      }

    }
    Serial.println(databyte, HEX);
    
    for(int i = 0; i<10;i++){
      if(numhex[i] == (unsigned char)databyte){
        Serial.println(i);
        remonum = i;
        Fndnum(i);
        break;
      }
    }
  }
}

void Fndnum(int num){
  switch(num){
  case 0:
    digitalWrite(4, 0);
    digitalWrite(5, 0);
    digitalWrite(6, 0);
    digitalWrite(7, 1);
    digitalWrite(8, 0);
    digitalWrite(9, 0);
    digitalWrite(10, 0);
    digitalWrite(11, 1);
    break;
  case 1:
    digitalWrite(4, 1);
    digitalWrite(5, 1);
    digitalWrite(6, 0);
    digitalWrite(7, 1);
    digitalWrite(8, 1);
    digitalWrite(9, 0);
    digitalWrite(10, 1);
    digitalWrite(11, 1);
    break;
  case 2:
    digitalWrite(4, 0);
    digitalWrite(5, 0);
    digitalWrite(6, 1);
    digitalWrite(7, 1);
    digitalWrite(8, 0);
    digitalWrite(9, 0);
    digitalWrite(10, 1);
    digitalWrite(11, 0);
    break;
  case 3:
    digitalWrite(4, 1);
    digitalWrite(5, 0);
    digitalWrite(6, 0);
    digitalWrite(7, 1);
    digitalWrite(8, 0);
    digitalWrite(9, 0);
    digitalWrite(10, 1);
    digitalWrite(11, 0);
    break;
  case 4:
    digitalWrite(4, 1);
    digitalWrite(5, 1);
    digitalWrite(6, 0);
    digitalWrite(7, 1);
    digitalWrite(8, 1);
    digitalWrite(9, 0);
    digitalWrite(10, 0);
    digitalWrite(11, 0);
    break;
  case 5:
    digitalWrite(4, 1);
    digitalWrite(5, 0);
    digitalWrite(6, 0);
    digitalWrite(7, 1);
    digitalWrite(8, 0);
    digitalWrite(9, 1);
    digitalWrite(10, 0);
    digitalWrite(11, 0);
    break;
  case 6:
    digitalWrite(4, 0);
    digitalWrite(5, 0);
    digitalWrite(6, 0);
    digitalWrite(7, 1);
    digitalWrite(8, 0);
    digitalWrite(9, 1);
    digitalWrite(10, 0);
    digitalWrite(11, 0);
    break;
  case 7:
    digitalWrite(4, 1);
    digitalWrite(5, 1);
    digitalWrite(6, 0);
    digitalWrite(7, 1);
    digitalWrite(8, 0);
    digitalWrite(9, 0);
    digitalWrite(10, 0);
    digitalWrite(11, 1);
    break;
  case 8:
    digitalWrite(4, 0);
    digitalWrite(5, 0);
    digitalWrite(6, 0);
    digitalWrite(7, 1);
    digitalWrite(8, 0);
    digitalWrite(9, 0);
    digitalWrite(10, 0);
    digitalWrite(11, 0);
    break;
  case 9:
    digitalWrite(4, 1);
    digitalWrite(5, 0);
    digitalWrite(6, 0);
    digitalWrite(7, 1);
    digitalWrite(8, 0);
    digitalWrite(9, 0);
    digitalWrite(10, 0);
    digitalWrite(11, 0);
    break;
    }
}
