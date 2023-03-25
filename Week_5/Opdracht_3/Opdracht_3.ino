#define POTPIN A0
const int LED_cor = 3;
const int LED_notCor = 5;
int POT_read;
int POT_percentage;
int LED_out_notCor;
int LED_out_cor; 

void setup(){
  Serial.begin(9600);
  
  pinMode(POTPIN,INPUT);
  
  pinMode(LED_notCor,OUTPUT);
  digitalWrite(LED_notCor, LOW);
  
  pinMode(LED_cor,OUTPUT);
  digitalWrite(LED_cor, LOW);
}

void loop(){
// read and calculate
  POT_read = analogRead(POTPIN);
  LED_out_notCor = map(POT_read, 0, 1023, 0, 255);
  POT_percentage = (POT_read / 1023.0) * 100;
  LED_out_cor = (255 / 100.0) * POT_percentage;

// Print values
  Serial.print("Readed value from potmeter: ");
  Serial.println(POT_read);
  
  Serial.print("Percentage of potmeter: ");
  Serial.println(POT_percentage);
  
  Serial.print("LED brightness without correction: ");
  Serial.println(LED_out_notCor);

  Serial.print("LED brightness with correction: ");
  Serial.println(LED_out_cor);

// Set leds on 
  analogWrite(LED_notCor, LED_out_notCor);
  analogWrite(LED_cor, LED_out_cor);

  delay(50);
  
}
