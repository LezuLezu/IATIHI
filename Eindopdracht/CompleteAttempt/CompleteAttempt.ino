//  --------------------------------------------------------------------  IATIHI FINAL ASSIGNMENT  --------------------------------------------------------------------
//  --------------------------------------------------------------------  AUTHOR: ZOË VAN DIJK  --------------------------------------------------------------------
//  ----------------------------------  Include library for displays  ----------------------------------
#include <TM1637Display.h>

//  ----------------------------------  Define the connections pins  ----------------------------------
// display 1
#define CLK_1 12
#define DIO_1 11
// display 2
#define CLK_2 10
#define DIO_2 9
// display 3
#define CLK_3 8
#define DIO_3 7

// potmeters
int potPins[] = {A0, A1, A2, A3, A6};

// Button for pit connection
const int BUTTON = 5;
// LEDS
const int LED_top_left = A5;
const int LED_bottom_left = A4;
const int LED_middle = 4;
const int LED_top_right = 3;
const int LED_bottom_right = 2;
const int LED_connection = 6;

//  ----------------------------------  Create objects   ---------------------------------- 
// Create a display object of type TM1637Display
TM1637Display display1 = TM1637Display(CLK_1, DIO_1); 
TM1637Display display2 = TM1637Display(CLK_2, DIO_2); 
TM1637Display display3 = TM1637Display(CLK_3, DIO_3); 

// Create an array that turns all segments ON
const uint8_t allON[] = {0xff, 0xff, 0xff, 0xff};

// Create an array that turns all segments OFF
const uint8_t allOFF[] = {0x00, 0x00, 0x00, 0x00};

// Create A symboll for pit connection
const uint8_t symbol_A[] = {SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G};

// other vars and objects
int numPots = 5;          // Amount of potmeters
int* mappedValues;        // global accesible mapped values
bool buttonInput;       
bool buttonState;       
int buttonCount = 0;    
bool connection = false;

//  ----------------------------------  Potentiometer class  ---------------------------------- 
class PotentiometerMapper {
  private:              // create variables for class
    int numPots;        // amount of potmeters
    int* potPins;       // set potpins
    int* potValues;     // readings of potmeaters
    int* mappedValues;  // mapped reading of potmeters 0 to 9
  public:
    PotentiometerMapper(int num) {
      numPots = num;
      potPins = new int[numPots];
      potValues = new int[numPots];
      mappedValues = new int[numPots];
      for (int i = 0; i < numPots; i++) {   // set all items to 0 to iniate
        potPins[i] = 0;
        potValues[i] = 0;
        mappedValues[i] = 0;
      }
    }
    ~PotentiometerMapper() {        // delete old values to safe storage
      delete[] potPins;
      delete[] potValues;
      delete[] mappedValues;
    }
    void setPins(int* pins) {       // set pins for reading
      for (int i = 0; i < numPots; i++) {
        potPins[i] = pins[i];
      }
    }
    void readValues() {             // read potmeters and store values
      for (int i = 0; i < numPots; i++) {
        potValues[i] = analogRead(potPins[i]);
      }
    }
    bool mapCompareValues() {              // map readings and store
      bool changed = false;
      for (int i = 0; i < numPots; i++) {
        int newValue = map(potValues[i], 0, 1023, 0, 10);
        if (newValue != mappedValues[i]) {    // check if new mapped vallue differs from previous
          changed = true;
          mappedValues[i] = newValue;
        }
      }
      return changed;
    }
    int* getMappedValues() {      // return mapped values 
      return mappedValues;
    }
};

// class object
PotentiometerMapper mapper(numPots);

//  ----------------------------------  SETUP   ----------------------------------
void setup() {
// Serial
  Serial.begin(9600);
  
// Set brightness for displays
  display1.setBrightness(5);
  display2.setBrightness(5);
  display3.setBrightness(5);

// Button
  pinMode(BUTTON, INPUT_PULLUP);

// LEDS
  pinMode(LED_top_left, OUTPUT);
  pinMode(LED_bottom_left, OUTPUT);  
  pinMode(LED_middle, OUTPUT);  
  pinMode(LED_top_right, OUTPUT);
  pinMode(LED_bottom_right, OUTPUT);
  pinMode(LED_connection, OUTPUT);

  digitalWrite(LED_top_left, LOW);
  digitalWrite(LED_bottom_left, LOW);  
  digitalWrite(LED_middle, LOW);  
  digitalWrite(LED_top_right, LOW);
  digitalWrite(LED_bottom_right, LOW);
  digitalWrite(LED_connection, LOW);


}
//  ----------------------------------  LOOP   ----------------------------------
void loop() {
  
//  ----------------------------------  Potmeter   ----------------------------------
  mapper.setPins(potPins);
  int* prevMappedValues = new int[numPots];     // var to store mapped values to compare in class
  while (true) {
    //  ----------------------------------  Button   ----------------------------------
    buttonInput = !digitalRead(BUTTON);
    if(buttonInput){
      if(buttonState){
        buttonState = false;
        buttonCount += 1;
      }
    }else if(!buttonState){
      buttonState = true;
    }
    if(buttonCount%2 == 1){
      Serial.println("LED ON");
      connection = true;
      digitalWrite(LED_connection, HIGH);
    }else{
      Serial.println("LED Off");
      connection = false;
      digitalWrite(LED_connection, LOW);
    }
    mapper.readValues();                        // read potpins
    bool changed = mapper.mapCompareValues();   // check for changes
    if (changed) {
     mappedValues = mapper.getMappedValues(); // get curren readings 
      for (int i = 0; i < numPots; i++) {
        Serial.print(mappedValues[i]);
        Serial.print(" ");
        prevMappedValues[i] = mappedValues[i];      // set new readings to old for new loop
      }
      Serial.println();
    }
  
//  ----------------------------------  Display   ----------------------------------
    // -------------  Display 1 (top pits)  ------------- 
    display1.clear();
    // ------ left  ------
    if(mappedValues[0] != 0){
      display1.showNumberDec(mappedValues[0], false, 1, 0);
      digitalWrite(LED_top_left, HIGH);
    }else{
      digitalWrite(LED_top_left, LOW);
    }
    
    // ------  right  ------
    if(mappedValues[3] != 0 && !connection){
      display1.showNumberDec(mappedValues[3], false, 1, 3);
      digitalWrite(LED_top_right, HIGH);
    }else if(connection){
      display1.setSegments(symbol_A, 1, 3);
      digitalWrite(LED_top_right, HIGH);
    }else{
      digitalWrite(LED_top_right, LOW);
    }
    

    //  -------------   Display 2 (middle pit)  ------------- 
    display2.clear();
    if(mappedValues[2] != 0){
      display2.showNumberDec(mappedValues[2], false, 1, 2);
      digitalWrite(LED_middle, HIGH);
    }else{
      digitalWrite(LED_middle, LOW);
    }

    //  -------------   Display 3 (bottom pits) ------------- 
    display3.clear();
    //  ------  left  ------
    if(mappedValues[1] != 0){
      display3.showNumberDec(mappedValues[1], false, 1, 0);
      digitalWrite(LED_bottom_left, HIGH);
    }else{
      digitalWrite(LED_bottom_left, LOW);
    }
    //  ------  right ------
    if(mappedValues[4] != 0){
      display3.showNumberDec(mappedValues[4], false, 1, 3);
      digitalWrite(LED_bottom_right, HIGH);
    }else{
      digitalWrite(LED_bottom_right, LOW);
    }
          
    delay(1000);
  }
  delete[] prevMappedValues;    // delete to safe storage
}
