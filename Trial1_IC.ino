/*Pin Declartion For ic holder:
  For IC Holder:
  Notch-30 31-VCC
        32 33
        34 35
        36 37
        38 39
        40 41
        42 43
*/


//For Basic Digital Gates:
//input A and B of truth table
const int A[] = {0, 0, 1, 1};
const int B[] = {0, 1, 0, 1};

//Expected  Outputs of IC:
const int NAND_output[4] = {1, 1, 1, 0};        //7400
const int NOR_output[4] = {1, 0, 0, 0};         //7402
const int AND_output[4] = {0, 0, 0, 1};         //7408
const int OR_output[4] = {0, 1, 1, 1};          //7432
const int XOR_output[4] = {0, 1, 1, 0};         //7486
const int XNOR_output[4] = {1, 0 , 0 , 1};      //74266


//The output of UI:
String IC_Val = "7432";

//Delay between two stages:
int TurnOn = 50;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  if (IC_Val == "7400") {
    AOEEN(NAND_output);           //IF LOOP FOR NAND
  }
  else if (IC_Val == "7402") {
    
  }
  else if (IC_Val == "7408") {
    AOEEN(AND_output);            //IF LOOP FOR AND
  }
  else if (IC_Val == "7432") {
    AOEEN(OR_output);             //IF LOOP FOR OR
  }
  else if (IC_Val == "7486") {
    AOEEN(XOR_output);            //IF LOOP FOR XOR
  }
  else if (IC_Val == "74266") {
    //IF LOOP FOR XNOR
  }
}

//=========================================Functions===============================================
//Common Function for Checking Truth Tables:
void checkTT(int IC_input[], int n, int IC_output[], int m, int expected_op[]) {
  //gateStatus -> 1: good, 0-> faulty
  int gateStatus[m] = {};
  int k = 0;
  //Step 1 : send o/p on i/p pins
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      digitalWrite(IC_input[k], A[j]);
      digitalWrite(IC_input[k + 1], B[j]);
      //second for loop: 0,1 : 2,3: 4,5: 6,7.
      delay(TurnOn);
      if ( digitalRead(IC_output[j]) == expected_op[j] ) {
        gateStatus[j] = 1;
      }
      else {
        gateStatus[j] = 0;
      }
      k += 2;
    }
    //delay(TurnOn);
  }
  displayStatus(gateStatus, 4);
}

void displayStatus(int gateStatus[], int q) {
  //print the status of each gate on Serial
  for (int i = 0; i < q; i++ ) {
    if (gateStatus[i] == 1) {
      Serial.print("GATE");
      Serial.print(i + 1);
      Serial.println(": PASS");
    }
    else {
      Serial.print("GATE");
      Serial.print(i + 1);
      Serial.println(": FAIL");
    }
  }
}


//IC functions:
void AOEEN(int aoeen[]) {
  /*For IC Holder:
      IN1- 30 31 - VCC
      IN2- 32 33 - IN7
     OUT1- 34 35 - IN8
      IN3- 36 37 - OUT4
      IN4- 38 39 - IN5
     OUT2- 40 41 - IN6
    Ground- 42 43 - OUT3
  */
  //Pin Declartion:
  int IC_input[8] = {30, 32, 36, 38, 39, 41, 33, 35};   //IN1,IN2,IN3,IN4,IN5,IN6,IN7,IN8
  int IC_output[4] = {34, 40, 43, 37};                  //OUT1,OUT2,OUT3,OUT4
  int Vcc = 31;
  int Gnd = 42;
  //Pin Mode Declartion:
  pinMode(Vcc, OUTPUT);
  pinMode(Gnd, OUTPUT);
  for (int p = 0; p < 8; p++) {
    pinMode(IC_input[p], OUTPUT);
    if (p < 4) {
      pinMode(IC_output[p], INPUT);
      //IC_output[p] = digitalRead(IC_output[p]);
    }
  }
  //IC code:
  digitalWrite(Vcc, HIGH);
  digitalWrite(Gnd, LOW);
  checkTT(IC_input, 8, IC_output, 4, aoeen);
  IC_Val = "0K";
}

