const int inputPin = 3;

void setup() {
  Serial.begin(9600);
  pinMode(inputPin, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!digitalRead(inputPin)){
    Serial.println("Hall switch");
  }
  delay(100);
}
