// For displays
// Include the library
#include <TM1637Display.h>

// Define the connections pins
// display 1
#define CLK_1 12
#define DIO_1 11
// display 2
#define CLK_2 10
#define DIO_2 9
// display 3
#define CLK_3 8
#define DIO_3 7
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

// For potreadings
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

// variable declerations for pot readdings
int numPots = 5;
int potPins[] = {A0, A1, A2, A3, A4};
PotentiometerMapper mapper(numPots);
int* mappedValues;
void setup() {
  Serial.begin(9600);
  display1.setBrightness(5);
  display2.setBrightness(5);
  display3.setBrightness(5);


}

void loop() {
  mapper.setPins(potPins);
  int* prevMappedValues = new int[numPots];     // var to store mapped values to compare in class
  while (true) {
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
//------------- Displays ---------------------------------
    // Display 1 (top pits)
    display1.clear();
    if(mappedValues[0] != 0){
      display1.showNumberDec(mappedValues[0], false, 1, 0);
    }
    if(mappedValues[3] != 0){
      display1.showNumberDec(mappedValues[3], false, 1, 3);
    }

    // Display 2 (middle pit)
    display2.clear();
    if(mappedValues[2] != 0){
      display2.showNumberDec(mappedValues[2], false, 1, 2);
    }

    // Display 3 (bottom pits)
    display3.clear();
    if(mappedValues[1] != 0){
      display3.showNumberDec(mappedValues[1], false, 1, 0);
    }
    if(mappedValues[4] != 0){
      display3.showNumberDec(mappedValues[4], false, 1, 3);
    }    

    
    delay(1000);
  }
  delete[] prevMappedValues;    // delete to safe storage
}
