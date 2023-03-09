const int LED = 5;
#define LDR A0

int LDR_input;
int brightness;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(LDR, INPUT);

  digitalWrite(LED, LOW);

  Serial.begin(9600);
}

void loop() {
  LDR_input = analogRead(LDR);
  brightness = LDR_input / -4;
  analogWrite(LED, brightness);

  Serial.print("Pot reading: ");
  Serial.println(LDR_input);
  Serial.print("Calculated brightness: ");
  Serial.println(brightness);

}
