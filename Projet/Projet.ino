#include <SPI.h> 
#include <MFRC522.h> 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h> 
 
#define RST_PIN 5
#define SS_PIN 53
 
MFRC522 mfrc522(SS_PIN, RST_PIN); // definis ton lecteur 
LiquidCrystal_I2C lcd(0x27,20,21);  // set le LCD
Servo myservo;

byte carte[] = {25,184,21,179};
int nb_essaie;
int prog_state;

/*
 * NumPad Variable
 */
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
String valSupp = "*";
String mdp = "";
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 



/*
 * Fonction d'affichage sur lcd
 * @param : String line1
 * @param : String line2
 */
void Affichage(String line1, String line2){
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print(line1); 
  lcd.setCursor(0,1); 
  lcd.print(line2); 
}

/*
 * Verification de la présence d'une carte
 * return boolean
 */
boolean carte_ici(){
  if (!mfrc522.PICC_IsNewCardPresent()) {
  return false; 
 } 
 
 if (!mfrc522.PICC_ReadCardSerial()) { 
  return false; 
 }
 return true;
 
}

/*
 * Verification de la carte
 * return boolean
 */
boolean verifCard(){
  if( mfrc522.uid.uidByte[0] == carte[0] &&
      mfrc522.uid.uidByte[1] == carte[1] &&
      mfrc522.uid.uidByte[2] == carte[2] &&
      mfrc522.uid.uidByte[3] == carte[3] )
    {
      
    Affichage("Carte","Ok");
    delay(1000);
    Affichage("Rentrez","Mot de passe");
    prog_state = 1;
    delay(1000);
    Affichage("Mot de passe : ",mdp);
    return true;
  }
  else{
    Affichage("Mauvaise Carte","Repassez Carte");
    delay(1000);
    return false;
  }
}

/*
 * Verification de Mot de passe
 * @param : char Key
 */
void VerifMdp(char Key){
  if(Key){
    if(String(Key)==valAccept){
      if(mdp == valMdp){
        Affichage("Mot de passe","Correcte");
        delay(1000);
        mdp = "";
        prog_state = 2;
      }
      else{
        Affichage("Mot de passe","Incorrecte");
        mdp = "";
        nb_essaie = nb_essaie +1 ;
        if(nb_essaie >= 5){
          Affichage("Essaie : ",String(nb_essaie) + "/5");
          delay(1000);
          Affichage("Nombre essaie","depacer");
          delay(1000);
          Affichage("Attendez","30 seconde");
          nb_essaie = 0;
          delay(30000);
          Affichage("BONJOUR","ATTENTE DE CARTE");
          prog_state =0;
          return;
        }
        delay(1000);
        Affichage("Essaie : ",String(nb_essaie) + "/5");
        mdp="";
        delay(1000);
        Affichage("Rentrez","Mot de passe");
        Affichage("Mot de passe : ",mdp);
      }
    }
    
    else{
      mdp = mdp + Key;
      Affichage("Mot de passe : ",mdp);
    }
    
    
  }
}







/*
 * Setup des variables
 */

void setup() { 
  //Initialisation du RFID-Moduls 
  Serial.begin(9600); 
  while (!Serial); 
  SPI.begin();  
  mfrc522.PCD_Init();  
  mfrc522.PCD_DumpVersionToSerial(); //Details des Lesegerätes ausgeben 
  
  //Setup LCD 
  lcd.init();
  lcd.backlight(); 
  boolean carte_lu = false;

  // Envoi du message 
  Affichage("BONJOUR","ATTENTE DE CARTE");

  //nb essaie de lecture de carte
  nb_essaie = 0;

  //état du programme
  prog_state = 0;

  
  
} 

/*
 * Fonction loop()
 */

 
void loop() {

  if(prog_state == 0){
    if(carte_ici()){
      if(!verifCard()){
        nb_essaie = nb_essaie +1;
        Affichage("LECTURE CARTE","Essaie " + String(nb_essaie) +"/5");
      }
      if(nb_essaie>=5){
        Affichage("Nombre essaie","depacer");
        delay(1000);
        Affichage("Attendez","30 seconde");
        nb_essaie = 0;
        delay(30000);
        Affichage("BONJOUR","ATTENTE DE CARTE");
      }
    }
  }

  if(prog_state == 1){
    char customKey = customKeypad.getKey();
    if (customKey){
      VerifMdp(customKey);
    }
  }

  if(prog_state == 2){
    Affichage("Ouverture porte","");
    myservo.attach(9);
    myservo.write(180);
    delay(2000);
    myservo.detach();
    Affichage("Merci","Bonne Journee");
    delay(15000);
    myservo.attach(9);
    myservo.write(-180);
    delay(2000);
    myservo.detach();
    delay(1000);
    Affichage("BONJOUR","ATTENTE DE CARTE");
    prog_state = 0;
  }
}
