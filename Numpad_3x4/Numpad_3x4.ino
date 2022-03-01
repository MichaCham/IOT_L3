#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 3; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {27, 28, 32, 31}; 
byte colPins[COLS] = {35 , 36 , 39};  

String valAccept = "#";
String valMdp = "1234";
String mdp = "";
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void VerifMdp(char Key){
  if(Key){
    if(String(Key)==valAccept){
      if(mdp == valMdp){
        Serial.println("Mot de passe bon");
        mdp = "";
      }
      else{
        Serial.println("Mauvais Mot de passe");
        mdp = "";
      }
  }
  
    if (String(Key)!=valAccept){
      mdp = mdp + Key;
      Serial.println(mdp);
    }
  }
}


void setup(){
  Serial.begin(9600);
}
  
void loop(){
char customKey = customKeypad.getKey();
  
  if (customKey){
    VerifMdp(customKey);
  }
}
