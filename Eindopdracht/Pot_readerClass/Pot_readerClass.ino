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
        int newValue = map(potValues[i], 0, 1023, 0, 9);
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

int numPots = 5;
int potPins[] = {A0, A1, A2, A3, A4};
PotentiometerMapper mapper(numPots);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}
  

void loop() {
  mapper.setPins(potPins);
  int* prevMappedValues = new int[numPots];     // var to store mapped values to compare in class
  while (true) {
    mapper.readValues();                        // read potpins
    bool changed = mapper.mapCompareValues();   // check for changes
    if (changed) {
      int* mappedValues = mapper.getMappedValues(); // get curren readings 
      for (int i = 0; i < numPots; i++) {
        Serial.print(mappedValues[i]);
        Serial.print(" ");
        prevMappedValues[i] = mappedValues[i];      // set new readings to old for new loop
      }
      Serial.println();
    }
    delay(1000);
  }
  delete[] prevMappedValues;

}
