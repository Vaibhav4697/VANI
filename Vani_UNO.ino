#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#define FLEX1 A0
#define FLEX2 A1
#define FLEX3 A2
#define FLEX4 A3
#define FLEX5 A4
#define MODE1 7
#define MODE2 8
#define VOLUME A5
#define TRIGGER 13
const int rs = 12, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void setup() {
  // put your setup code here, to run once:
  pinMode(MODE1, INPUT);
  pinMode(MODE2, INPUT);
  pinMode(FLEX1, INPUT);
  pinMode(FLEX2, INPUT);
  pinMode(FLEX3, INPUT);
  pinMode(FLEX4, INPUT);
  pinMode(FLEX5, INPUT);
  pinMode(VOLUME,INPUT);
  pinMode(TRIGGER, OUTPUT);

  Serial.begin(115200);
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));

  lcd.begin(16,2);
  lcd.print("welcome");
  delay(2000);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  int gestureArray[32][5] = {
  {1, 1, 1, 1, 1}, // No Gesture
  {1, 1, 1, 1, 0}, //B
  {1, 1, 1, 0, 1}, //C
  {1, 1, 1, 0, 0}, //D
  {1, 1, 0, 1, 1}, //E
  {1, 1, 0, 1, 0}, //F
  {1, 1, 0, 0, 1}, //G
  {1, 1, 0, 0, 0}, //H
  {1, 0, 1, 1, 1}, //I
  {1, 0, 1, 1, 0}, //J
  {1, 0, 1, 0, 1}, //K
  {1, 0, 1, 0, 0}, //L
  {1, 0, 0, 1, 1}, //M
  {1, 0, 0, 1, 0}, //N
  {1, 0, 0, 0, 1}, //O
  {1, 0, 0, 0, 0}, //P
  {0, 1, 1, 1, 1}, //Q
  {0, 1, 1, 1, 0}, //R
  {0, 1, 1, 0, 1}, //S
  {0, 1, 1, 0, 0}, //T
  {0, 1, 0, 1, 1}, //U
  {0, 1, 0, 1, 0}, //V
  {0, 1, 0, 0, 1}, //W
  {0, 1, 0, 0, 0}, //X
  {0, 0, 1, 1, 1}, //Y
  {0, 0, 1, 1, 0}, //Z
  {0, 0, 1, 0, 1}, //1
  {0, 0, 1, 0, 0}, //2
  {0, 0, 0, 1, 1}, //3
  {0, 0, 0, 1, 0}, //4
  {0, 0, 0, 0, 1}, //5
  {0, 0, 0, 0, 0}, //A
};

String characterArray[32] = {
  " ",
  "B",
  "C",
  "D",
  "E",
  "F",
  "G",
  "H",
  "I",
  "J",
  "K",
  "L",
  "M",
  "N",
  "O",
  "P",
  "Q",
  "R",
  "S",
  "T",
  "U",
  "V",
  "W",
  "X",
  "Y",
  "Z",
  "1",
  "2",
  "3",
  "4",
  "5",
  "A"
};
String wordArray[32] = {
  " ",
  "Calm",
  "Sick",
  "Weapon",
  "Police",
  "Direction",
  "Yes",
  "Help Me!!",
  "Call",
  "Water",
  "Thank You!!",
  "Male",
  "Female",
  "Transport",
  "No",
  "Me",
  "Hi, Hello!!",
  "Food",
  "Good",
  "Blessed",
  "Danger!!",
  "Hospital Emergency!!",
  "Animal",
  "You",
  "Beautiful",
  "Small",
  "Bad",
  "Angry",
  "Big",
  "Like It!!",
  "Washroom",
  "Stop/ Hold/ Wait!!"
};

   int soundVolume=analogRead(VOLUME);
   soundVolume=map(soundVolume,0,1023,0,30);
   soundVolume=constrain(soundVolume,0,30);
   myDFPlayer.volume(soundVolume);
  int flex1 = analogRead(FLEX1);
  int flex2 = analogRead(FLEX2);
  int flex3 = analogRead(FLEX3);
  int flex4 = analogRead(FLEX4);
  int flex5 = analogRead(FLEX5);

  if(flex1 <= 500){
    flex1 = 0;
  }
  else{
    flex1 = 1;
  }

  if(flex2 <= 500){
    flex2 = 0;
  }
  else{
    flex2 = 1;
  }

  if(flex3 <= 500){
    flex3 = 0;
  }
  else{
    flex3 = 1;
  }

  if(flex4 <= 500){
    flex4 = 0;
  }
  else{
    flex4 = 1;
  }

  if(flex5 <= 500){
    flex5 = 0;
  }
  else{
    flex5 = 1;
  }
  int gestureNumber;
  for(int i = 0; i < 32; i++){
    if(flex1 == gestureArray[i][0] && flex2 == gestureArray[i][1] && flex3 == gestureArray[i][2] && flex4 == gestureArray[i][3] && flex5 == gestureArray[i][4]){
      gestureNumber = i;
    }
  }

 if(digitalRead(MODE1)==HIGH)
 { Serial.println(characterArray[gestureNumber]);
  lcd.clear();
  lcd.print(characterArray[gestureNumber]);
  myDFPlayer.play(gestureNumber);
  delay(3000);
 
 }
 if(digitalRead(MODE2)==HIGH)
 { Serial.println(wordArray[gestureNumber]);
  lcd.clear();
  lcd.print(wordArray[gestureNumber]);
  if(gestureNumber == 8){
    digitalWrite(TRIGGER, HIGH);
  }
  else{
    digitalWrite(TRIGGER, LOW );
  }
 if(gestureNumber != 0){
  gestureNumber+=31;
 myDFPlayer.play(gestureNumber);
  }
  delay(3000);
 
 }
}
