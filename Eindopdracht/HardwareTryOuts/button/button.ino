#define BUTTON A6
bool buttonInput;
bool buttonState;
int buttonCount = 0;


void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  buttonInput = !analogRead(BUTTON);
  if(buttonInput){
    if(buttonState){
      buttonState = false;
      buttonCount += 1;
    }
  }else if(!buttonState){
    buttonState = true;
  }

  if(buttonCount%2 == 1){
    Serial.println("LED ON");
  }
 
}
