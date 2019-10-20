#include <LiquidCrystal_I2C.h> //20x4
#include <Keypad.h> //4x4
#include <Wire.h> // Library for I2C communication

//#define HIGH 1
//#define LOW 0

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

//input A and B of truth table
const char *A[] = {"LOW","LOW","HIGH","HIGH"};
const char *B[] = {"LOW","HIGH","LOW","HIGH"};

const char *OR_output[4] = {"LOW","HIGH","HIGH","HIGH"};
const char *NAND_output[4] = {"HIGH","HIGH","HIGH","LOW"};
const char *NOR_output[4] = {"HIGH","LOW","LOW","LOW"};
const char *AND_output[4] = {"LOW","LOW","LOW","HIGH"};


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

//define input and ouptut pins for each IC
void QuadNAND(){
//Gate 1: //i/p 1: 
          //i/p 2:
          //o/p 1:
//Gate 2: //i/p 1: 
          //i/p 2:
          //o/p 1:
//Gate 3: //i/p 1: 
          //i/p 2:
          //o/p 1:
//Gate 4: //i/p 1: 
          //i/p 2:
          //o/p 1:
//input array = [] -> pin definition
//output array = [] -> pin definition
//Set VCC and GROUND
//set pinmode as output for i/p array
//and input for o/p array
//call check TT(i/p array, size of input array, o/p array, size of output array)
 
}
void QuadNOR(){}
void QuadAND(){}
void QuadOR(){}
void HexaNOT(){}

void checkTT(int IC_input[],int n,int IC_output[],int m, char expected_op[]){
  //IC_input -> array of IC's i/p pins
  //n -> size of the array

  //gateStatus -> 1: good, 0-> faulty
  int gateStatus[m] = {};

  //send o/p on i/p pins
  for(int i = 0; i < (n-1); i++){
    for(int j = 0; j < m; j++){  //m-> o/p = conditions..0 to 3
      digitalWrite(IC_input[i],A[j]);
      digitalWrite(IC_input[i+1],B[j]);
      delay(300);
      if(digitalRead(IC_output[j]) == expected_op[j] ){
        //continue
        gateStatus[j] = 1;
      }
      else{
        //Gate is faulty...move to the next gate
        gateStatus[j] = 0;
        break;
      }
     }
   }

  displayStatus(gateStatus[],m);
}

void displayStatus(int gateStatus[],q){
  //print the status of each gate on LCD
}
