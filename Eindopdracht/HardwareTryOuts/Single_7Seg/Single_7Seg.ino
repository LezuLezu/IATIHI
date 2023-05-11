const int data = 4;  // Arduino pin for data pin of the shift register
const int latch = 5;  // Arduino pin for latch pin of the shift register
const int clock = 6;  // Arduino pin for clock pin of the shift register
const char common = 'c'; // 7-segment with common cathode
void setup() {
  // assigning the working modes to the shift register pins
  pinMode(data, OUTPUT);
  pinMode(latch, OUTPUT);
  pinMode(clock, OUTPUT);
}

void loop() {
  for (int i = 0; i <= 9; i++) {// for loop to generate number from 0 to 9
    byte bits = binary(i) ; /* detect the binary given for respective number from the cases given below */
   
    display(bits);    // displaying the numbers on 7-segment
    delay(500);    
  }
}

void display(byte eightBits) {
  if (common == 'c') { // if the configuration is common cathode
    eightBits = eightBits ^ B11111111;  // then change the bits from 0 to 1  
  }
  digitalWrite(latch, LOW);  // preparing shift register for data
  shiftOut(data, clock, LSBFIRST, eightBits); /* sending the data to  7segmnet starting from least significant bit*/
  digitalWrite(latch, HIGH); /* displaying the data on the 7 segment */
}
/*cases for detecting the binary of the numbers generated from 0 to 9 */
byte binary (int Number) {
  switch (Number) {
    case 0:
      return B11111100;// if 0 is generated then binary for zero  
      break;
    case 1:
      return B01100000;// if 1 is generated then giving binary for one
      break;
    case 2:
      return B11011010;// if 2 is generated then giving binary for two
      break;
    case 3:
      return B11110010;// if 3 is generated then giving binary for three  
      break;
    case 4:
      return B01100110;// if 4 is generated then giving binary for four
      break;
    case 5:
      return B10110110;// if 5 is generated then giving binary for five
      break;
    case 6:
      return B10111110;// if 6 is generated then giving binary for six
      break;
    case 7:
      return B11100000;// if 7 is generated then giving binary for seven
      break;
    case 8:
      return B11111110;// if 8 is generated then giving binary for eight
      break;
    case 9:
      return B11110110; // if 9 is generated then giving binary for nine  
  }
}
