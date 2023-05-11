// Constants for hardware
#define POTPIN A0
const int LED_B1 = 5;
const int LED_R1 = 6;
const int LED_W1 = 7;
const int LED_B2 = 4;
const int LED_R2 = 3;
const int LED_W2 = 2; 

int inputVal = 0;
int outputVal = 0;

void setup() {
// pinmodes
  pinMode(LED_B1, OUTPUT);
  pinMode(LED_R1, OUTPUT);
  pinMode(LED_W1, OUTPUT);
  pinMode(LED_B2, OUTPUT);
  pinMode(LED_R2, OUTPUT);
  pinMode(LED_W2, OUTPUT);
  pinMode(POTPIN, INPUT);

// set LEDS to low
  digitalWrite(LED_B1, LOW);
  digitalWrite(LED_R1, LOW);
  digitalWrite(LED_W1, LOW);
  digitalWrite(LED_B2, LOW);
  digitalWrite(LED_R2, LOW);
  digitalWrite(LED_W2, LOW);

// Serial
  Serial.begin(9600);
}

void loop() {
  inputVal = analogRead(POTPIN);
  Serial.print("Input from potmeter: ");
  Serial.println(inputVal);

  outputVal = map(inputVal, 0, 1023, 0, 6);
  Serial.print("Output calculated: ");
  Serial.println(outputVal);
  delay(100);

  if(outputVal == 0){       // All leds off
    digitalWrite(LED_B1, LOW);
    digitalWrite(LED_R1, LOW);
    digitalWrite(LED_W1, LOW);
    digitalWrite(LED_B2, LOW);
    digitalWrite(LED_R2, LOW);
    digitalWrite(LED_W2, LOW);
  }
  if(outputVal == 1){       // 1 led on, others off
    digitalWrite(LED_B1, HIGH);
    digitalWrite(LED_R1, LOW);
    digitalWrite(LED_W1, LOW);
    digitalWrite(LED_B2, LOW);
    digitalWrite(LED_R2, LOW);
    digitalWrite(LED_W2, LOW);
  }
  if(outputVal == 2){       // 2 leds on, others off
    digitalWrite(LED_B1, HIGH);
    digitalWrite(LED_R1, HIGH);
    digitalWrite(LED_W1, LOW);
    digitalWrite(LED_B2, LOW);
    digitalWrite(LED_R2, LOW);
    digitalWrite(LED_W2, LOW);
  }
  if(outputVal == 3){       // 3 leds on, others off
    digitalWrite(LED_B1, HIGH);
    digitalWrite(LED_R1, HIGH);
    digitalWrite(LED_W1, HIGH);
    digitalWrite(LED_B2, LOW);
    digitalWrite(LED_R2, LOW);
    digitalWrite(LED_W2, LOW);
  }
  if(outputVal == 4){       // 4 leds on, others off
    digitalWrite(LED_B1, HIGH);
    digitalWrite(LED_R1, HIGH);
    digitalWrite(LED_W1, HIGH);
    digitalWrite(LED_B2, HIGH);
    digitalWrite(LED_R2, LOW);
    digitalWrite(LED_W2, LOW);
  }
  if(outputVal == 5){       // 5 leds on, 1 off
    digitalWrite(LED_B1, HIGH);
    digitalWrite(LED_R1, HIGH);
    digitalWrite(LED_W1, HIGH);
    digitalWrite(LED_B2, HIGH);
    digitalWrite(LED_R2, HIGH);
    digitalWrite(LED_W2, LOW);
  }
  if(outputVal == 6){       // All leds on
    digitalWrite(LED_B1, HIGH);
    digitalWrite(LED_R1, HIGH);
    digitalWrite(LED_W1, HIGH);
    digitalWrite(LED_B2, HIGH);
    digitalWrite(LED_R2, HIGH);
    digitalWrite(LED_W2, HIGH);
  }  
  
}
