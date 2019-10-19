#include <LiquidCrystal_I2C.h> //20x4
#include <Keypad.h> //4x4
#include <Wire.h> // Library for I2C communication

#define HIGH 1
#define LOW 0

//TTL Gates
#define QuadNAND "7400"
#define QuadNOR "7402"
#define QuadAND "7408"
#define QuadOR "7432"
#define HexaNOT "7404"

//define LCD pins

//keypad
const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

//A -> Enter //B -> Back
//C-> EraseAll //D -> think!

//insert the decided pins 
int Pin14[14]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};             // 14 Pin IC
int Pin16[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};        //16 Pin IC

String IC_Val = "";

void setup(){
  // Initiate the LCD:
  LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  //  to set the LCD I2C address
  // Initialize the Keypad
  Keypad key = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
  
  lcd.init();
  lcd.backlight();
  
  Wire.begin();  
  Serial.begin(9600);

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("IC TESTER...");
  delay(1500);
  lcd.setCursor(0, 2);
  lcd.print("Press 0 to continue");
  delay(500);
}
  
void loop(){
  char pressedKey = key.getKey();
  if (pressedKey){
    if(pressedKey == "A"){
      //take the string value
      if(IC_Val == QuadNAND){
        QuadNAND();
      }
      else if(IC_Val == QuadNOR){
        QuadNOR();
      }
      else if(IC_Val == QuadAND){
        QuadAND();
      }
      else if(IC_Val == QuadOR){
        QuadOR();
      }
      else if(IC_Val == HexaNOT){
        HexaNOT();
      }
      else{
        //IC does not exist
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("IC NOT FOUND!");
      }
    }
    else if (pressedKey == "B"){
      //delete the last element in the string
    }
    else if(pressedKey == "C"{
      //delete the entire string
    }
    else{
      //append the value to the IC_Val string
      IC_Val += pressedKey;
    }
  }
  else{
    //what to do if no key is pressed
    //wait for keypress
  }
  
}

void QuadNAND(){
  
}
void QuadNOR(){
  
}
void QuadAND(){
  
}
void QuadOR(){
  
}
void HexaNOT(){
  
}
