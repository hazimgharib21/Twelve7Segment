// import EEPROM.h
#include <EEPROM.h>

// initiate variables
int num,data;
int count = 1;
int temporary = 1;
int temp[] = {0,0,0,0,0};

// hex value for numbers 0 - 9
int numHex[] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 103};

const int numDaerah = 12; 
int daerah[numDaerah][4] ={ // {latchPin, dataPin, clockPin, input}
  {23, 25, 21, 8888},
  {50, 48, 52, 8888},
  {44, 42, 46, 8888},
  {38, 36, 40, 8888},
  {34, 30, 32, 8888},
  {26, 24, 28, 8888},
  {53, 51, 22, 8888},
  {47, 45, 49, 8888},
  {41, 39, 43, 8888},
  {35, 33, 37, 8888},
  {29, 27, 31, 8888},
  {19, 20, 18, 8888}
};
void setup() {
  Serial.begin(9600);
  for (int i = 1; i < 54; i++){
    pinMode(i, OUTPUT);
  }
  readData();
  serialDisplay();
}

void loop() {
  if(Serial.available() > 0){
    saveData();
  }
  display();
}

void readData(){
  for(int i = 1; i < 49; i++){
    temp[count] = EEPROM.read(i);
    
  count++;
  
  if(count > 4){
    data = temp[1] * 1000;
    data += temp[2] * 100;
    data += temp[3] * 10;
    data += temp[4];
    daerah[temporary - 1][3] = data;
    temporary++;
    count = 1;
  }
  if(temporary > 12){
    temporary = 1;
  }
  }
  
}

void serialDisplay(){
  for (int i = 0; i < numDaerah; i++){
    Serial.print(i + 1);
    Serial.print(" : ");
    Serial.println(daerah[i][3]);
  }
  Serial.println("Please enter a number: ");
}

void saveData(){
  num = Serial.parseInt();
  Serial.println("Please enter 4 digit number");
  while(Serial.available() == 0);
    
    data = Serial.parseInt();
    Serial.println(data);
  int data1 = num1(data);
  int data2 = num2(data);
  int data3 = num3(data);
  int data4 = num4(data);
  
  EEPROM.write((num * 4) - 3,data1);
  EEPROM.write((num * 4) - 2,data2);
  EEPROM.write((num * 4) - 1,data3);
  EEPROM.write((num * 4),data4);

  daerah[num - 1][3] = data;
  serialDisplay();
  
  
}

void display(){
    for( int i = 0; i < numDaerah; i++){
    // display(daerah[i][0],daerah[i][1],daerah[i][2],daerah[i][3]);
    displayNum1(daerah[i][0],daerah[i][1],daerah[i][2],daerah[i][3]);
  }
  for( int i = 0; i < numDaerah; i++){
    // display(daerah[i][0],daerah[i][1],daerah[i][2],daerah[i][3]);
    displayNum2(daerah[i][0],daerah[i][1],daerah[i][2],daerah[i][3]);
  }
  for( int i = 0; i < numDaerah; i++){
    // display(daerah[i][0],daerah[i][1],daerah[i][2],daerah[i][3]);
    displayNum3(daerah[i][0],daerah[i][1],daerah[i][2],daerah[i][3]);
  }
  for( int i = 0; i < numDaerah; i++){
    // display(daerah[i][0],daerah[i][1],daerah[i][2],daerah[i][3]);
    displayNum4(daerah[i][0],daerah[i][1],daerah[i][2],daerah[i][3]);
  }
  }

void displayNum1(int latchPin, int dataPin, int clockPin, int num){
  int temp=num1(num);

 digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST,128>>8);
  shiftOut(dataPin, clockPin, MSBFIRST,128+numHex[temp]);
  digitalWrite(latchPin, HIGH);
  //delay(1);
}

void displayNum2(int latchPin, int dataPin, int clockPin, int num){
  int temp=num2(num);

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST,256 + 64 >> 8);
  shiftOut(dataPin, clockPin, MSBFIRST,numHex[temp]);
  digitalWrite(latchPin, HIGH);
  //delay(1);
}

void displayNum3(int latchPin, int dataPin, int clockPin, int num){
  int temp=num3(num);

   digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST,512 + 64 >> 8);
  shiftOut(dataPin, clockPin, MSBFIRST,numHex[temp]);
  digitalWrite(latchPin, HIGH);
  //delay(1);
}

void displayNum4(int latchPin, int dataPin, int clockPin, int num){
  int temp=num4(num);

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST,1024 + 64 >> 8);
  shiftOut(dataPin, clockPin, MSBFIRST,numHex[temp]);
  digitalWrite(latchPin, HIGH);
  //delay(1);
}

int num1(int num){
  int num1=num/1000;
  return num1;
}

int num2(int num){
  int num1=num/1000;
  int num2=(num/100)-(num1*10);
  return num2;
}

int num3(int num){
  int num1=num/1000;
  int num2=(num/100)-(num1*10);
  int num3=(num/10)-(num1*100)-(num2*10);
  return num3;
}

int num4(int num){
  int num1=num/1000;
  int num2=(num/100)-(num1*10);
  int num3=(num/10)-(num1*100)-(num2*10);
  int num4=num-(num1*1000)-(num2*100)-(num3*10);
  return num4;
}
