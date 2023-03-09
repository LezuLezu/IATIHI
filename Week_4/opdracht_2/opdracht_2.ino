const int LED = 5;
#define POTPIN A0

int POT_input;
int brightness;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(POTPIN, INPUT);

  digitalWrite(LED, LOW);

  Serial.begin(9600);
}

void loop() {
  POT_input = analogRead(POTPIN);
  brightness = POT_input / 4;
  analogWrite(LED, brightness);

  Serial.print("Pot reading: ");
  Serial.println(POT_input);
  Serial.print("Calculated brightness: ");
  Serial.println(brightness);

}
