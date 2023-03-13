#define POTPIN A0
const int LED = 5;
const int LED_2 = 6;
int POT_read;
int LED_out; 

void setup(){
  Serial.begin(9600);
  pinMode(POTPIN,INPUT);
  pinMode(LED,OUTPUT);
  digitalWrite(LED, LOW);
  pinMode(LED_2,OUTPUT);
  digitalWrite(LED_2, LOW);
}

void loop(){
  POT_read = analogRead(POTPIN);
  LED_out = map(POT_read, 0, 1023, 0, 255);
  analogWrite(LED, LED_out);
  Serial.print("Pot reading: ");
  Serial.println(POT_read);
  Serial.print("Calculated out: ");
  Serial.println(LED_out);  
  delay(50);
}
