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

// Create A symboll
const uint8_t symbol_A[] = {  
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G
  };

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  display1.setBrightness(5);
  display1.clear();
  display1.showNumberDec(3, false, 1, 0);
  display1.setSegments(symbol_A, 1, 3);

  display2.setBrightness(5);
  display2.clear();
  display2.showNumberDec(8, false, 1, 1);

  display3.setBrightness(5);
  display3.clear();
  display3.showNumberDec(1, false, 1, 0);
  display3.showNumberDec(9, false, 1, 3);
}
