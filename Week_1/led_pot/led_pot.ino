#define LED 3
#define POTPIN A7
int inputVal = 0;
int outputVal = 0;
void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(POTPIN, INPUT);
}

void loop() {
  inputVal = analogRead(POTPIN);
  Serial.print("Input from potmeter: ");
  Serial.println(inputVal);

  outputVal = map(inputVal, 0, 1023, 0, 255);
  Serial.print("Output calculated: ");
  Serial.println(outputVal);

  analogWrite(LED, outputVal);

  delay(100);
  
}
