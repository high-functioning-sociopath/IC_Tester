#include <LiquidCrystal_I2C.h> //20x4
#include <Keypad.h> //4x4
#include <Wire.h> // Library for I2C communication

//*******************************************************************************************************//
                                              //IC MACROS & DECLARATIONS 
//TTL Gates
#define QuadNAND "7400"
#define QuadNOR "7402"
#define QuadAND "7408"
#define QuadOR "7432"
#define HexaNOT "7404" 
#define QuadD_FF "7475"      //74LS175 IC - Quad Dtype Gated Flip Flop
//*******************************************************************************************************//
                                              // IC_I/O & TRUTH TABLE
                                              
//int Pin14[14]={30,31,32,33,34,35,36,37,38,39,40,41,42,43};             // 14 Pin IC
      //14pin IC -> VCC: pin 31 ///GND : pin 42
//int Pin16[16]={30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45};        //16 Pin IC
      //16pin IC -> VCC: pin 31 ///GND : pin 44

      //^Not necessart....since the pins have already been declared for individual ICs based on i/p and o/p configurations

//input A and B of truth table
const char *A[] = {"LOW","LOW","HIGH","HIGH"};
const char *B[] = {"LOW","HIGH","LOW","HIGH"};

const char *OR_output[4] = {"LOW","HIGH","HIGH","HIGH"};
const char *NAND_output[4] = {"HIGH","HIGH","HIGH","LOW"};
const char *NOR_output[4] = {"HIGH","LOW","LOW","LOW"};
const char *AND_output[4] = {"LOW","LOW","LOW","HIGH"};           
                                 
//*******************************************************************************************************//
                                             //KEYPAD
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

Keypad key = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
                                             
//*******************************************************************************************************//
                                            //LCD_DISPLAY
                                            
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  //  to set the LCD I2C address
                                           
//*******************************************************************************************************//

String IC_Val = "";   //To store the Input IC_Number

void setup(){
   
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
      else if(IC_Val == QuadD_FF){
        QuadD_FlipFlop();
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

//***********************************************************************************************************************//

//define input and ouptut pins for each IC
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


//        VCC   G1_A  G1_B G1_O G3_A  G3_B G3_O  

//          |   |     |     |     |     |     |          
//         -------------------------------------
//         -                                   -
//         ---|                                -
//         ---|         IC 74XX                -
//         ---|                                -
//         ---|                                -
//         -                                   -
//         -------------------------------------
//          |   |     |     |     |     |     |
//        G2_A  G2_B G2_O G4_A  G4_B G4_O   GND

          //G1 - G4 : Gate 1 to 4 of IC 

          
//input array = [] -> pin definition
//output array = [] -> pin definition
//Set VCC and GROUND
//set pinmode as output for i/p array
//and input for o/p array
//call check TT(i/p array, size of input array, o/p array, size of output array)

//***********************************************************************************************************************//

            
void QuadNAND(){
int IC_input[8] = {33,35,30,32,39,41,36,38};    
int IC_output[4] = {37,34,43,40};
int Vcc = 31;
int Gnd = 42;

pinmode(Vcc,OUTPUT);
pinmode(Gnd,OUTPUT);

digitalWrite(Vcc,HIGH);
digitalWrite(Gnd,LOW);

for (int p = 0; p < 8; p++){
  pinmode(IC_input[p],OUTPUT);
  if(p <4){
    pinmode(IC_output[p],INPUT);
  }
}
checkTT(IC_input[],8,IC_output[],4,0,NAND_output[],"logicGate");
}
            
            
            
void QuadNOR(){
    int IC_input[8] = {35,37,32,34,39,41,36,38};    
    int IC_output[4] = {33,30,39,36};
    int Vcc = 31;
    int Gnd = 42;

     pinmode(Vcc,OUTPUT);
     pinmode(Gnd,OUTPUT);

     digitalWrite(Vcc,HIGH);
     digitalWrite(Gnd,LOW);

     for (int p = 0; p < 8; p++){
        pinmode(IC_input[p],OUTPUT);
        if(p <4){
            pinmode(IC_output[p],INPUT);
            }
          }
      checkTT(IC_input[],8,IC_output[],4,0,AND_output[],"logicGate");
      }
            
            
            
            
void QuadAND(){
    int IC_input[8] = {33,35,30,32,39,41,36,38};    
    int IC_output[4] = {37,34,43,40};
    int Vcc = 31;
    int Gnd = 42;

     pinmode(Vcc,OUTPUT);
     pinmode(Gnd,OUTPUT);

     digitalWrite(Vcc,HIGH);
     digitalWrite(Gnd,LOW);

     for (int p = 0; p < 8; p++){
        pinmode(IC_input[p],OUTPUT);
        if(p <4){
            pinmode(IC_output[p],INPUT);
            }
          }
      checkTT(IC_input[],8,IC_output[],4,0,AND_output[],"logicGate");
      }
            
            
void QuadOR(){{
    int IC_input[8] = {33,35,30,32,39,41,36,38};    
    int IC_output[4] = {37,34,43,40};
    int Vcc = 31;
    int Gnd = 42;

     pinmode(Vcc,OUTPUT);
     pinmode(Gnd,OUTPUT);

     digitalWrite(Vcc,HIGH);
     digitalWrite(Gnd,LOW);

     for (int p = 0; p < 8; p++){
        pinmode(IC_input[p],OUTPUT);
        if(p <4){
            pinmode(IC_output[p],INPUT);
            }
          }
      checkTT(IC_input[],8,IC_output[],4,0,OR_output[],"logicGate");
      }
                                
            
void HexaNOT(){}

void QuadD_FlipFlop(){
  //https://www.uni-kl.de/elektronik-lager/417744 - Datasheet
  int Data_Pins[4] = {36,38,39,37}; //D0,D1,D2,D3    
  int Q_op[4] = {32,42,43,33}; // Q0,Q1,Q2,Q3
  int Qbar_op[4] = {34,40,41,35}; // complement of (Q0,Q1,Q2,Q3)
  int Vcc = 31;
  int Gnd = 44;
  int Mreset = 30;
  int clk = 45;
  
  pinmode(Vcc,OUTPUT);
  pinmode(Gnd,OUTPUT);
  pinmode(Mreset,OUTPUT);
  pinmode(clk,OUTPUT);
  
  digitalWrite(Vcc,HIGH);
  digitalWrite(Gnd,LOW);
  digitalWrite(Clk,HIGH);

  for (int p = 0; p < 4; p++){
      pinmode(Data_Pins[p],OUTPUT);
      pinmode(Q_op[p],INPUT);
      pinmode(Qbar_op[p],INPUT);
  }
  checkTT(Data_Pins[],4,IC_output[],4,Qbar_op[],Data_Pins[],"d_ff");
 }
            
            
            

void checkTT(int IC_input[],int n,int IC_output[],int m,int IC_OP2[], char expected_op[],type){
  //IC_input -> array of IC's i/p pins
  //n -> size of the array

  //gateStatus -> 1: good, 0-> faulty
  int gateStatus[m] = {};

  if(type == "logicGate"){
        //send o/p on i/p pins
        for(int i = 0; i < (n-1); i++){
          for(int j = k; j < m; j++){  //m-> o/p = conditions of truth table!
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
  }
  
  else if(type == "d_ff"){
       //send o/p on i/p pins
       char *Din = ["LOW","HIGH"];
        for(int i = 0; i < n ; i++){
          for(int j = 0; j < 2; j++){  //m-> o/p = conditions of truth table!
            digitalWrite(IC_input[i],Din[j]);
            
            delay(300);
            if( digitalRead(IC_output[i]) == expected_op[i] && digitalRead(IC_OP2[i]) != expected_op[i] ){
              //continue
              gateStatus[i] = 1;
             }
            else{
              //Gate is faulty...move to the next gate
              gateStatus[i] = 0;
              break;
             }
          }
        }
  }
  displayStatus(gateStatus[]);
}

void displayStatus(int gateStatus[]){
  //print the status of each gate on LCD
      len = length(gateStatus);
      for(int i = 0 , i < len , i++ ){
        if(gateStatus[i] == 1){
          lcd.print("GATE ",i+1," OK");
        }
        else{
          lcd.print("GATE ",i+1," FAULTY");
        }
      }
}
