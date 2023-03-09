// vars for hardware
const int LED_blue = 4;
const int LED_red = 5;
const int LED_green = 6;
const int BUTTON = 7;

// timer freqs in micro seconds
const long BLUE_freq = 1000000;     // 1hz
const long RED_freq = 2000000;    // 0.5 hz
const long GREEN_freq = 4000000;  // 0.25hz

// Button vars
bool buttonInput;
bool buttonState;
int buttonCount = 0;

class tmrMicros {
  private: 
  unsigned long nextChangeTime; 
  unsigned long timeOn_; 
  boolean overFlow;
  public: 
  void tmrSet(unsigned long timeOn) { 
    timeOn_ = timeOn; 
    unsigned long currentTime = micros(); 
    nextChangeTime = currentTime + timeOn; 
  }
  boolean tmrActive() { 
    unsigned long currentTime = micros(); 
    boolean val = false; 
    if (! overFlow) { 
      if (currentTime < nextChangeTime) { 
        val = true; 
      } 
    } 
    else if ((currentTime + timeOn_) < (nextChangeTime + timeOn_)){ 
      val = true; 
    } 
  return val; 
  }
};

// create timer objects
tmrMicros tmr1; 
tmrMicros tmr2;
tmrMicros tmr3;

void setup() {
  pinMode(LED_blue, OUTPUT);
  pinMode(LED_red, OUTPUT);
  pinMode(LED_green, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);

  digitalWrite(LED_blue, LOW);
  digitalWrite(LED_red, LOW);
  digitalWrite(LED_green, LOW);

  Serial.begin(9600);
}
void loop() {
  buttonInput = !digitalRead(BUTTON);
  if(buttonInput){
    if(buttonState){
      buttonState = false;
      buttonCount += 1;
    }
  }else if(!buttonState){
    buttonState = true;
  }
  
  Serial.println(buttonCount);
  if(buttonCount == 1){   // All LEDS
    if (! tmr1.tmrActive()){    //BLUE
      digitalWrite(LED_blue, ! digitalRead(LED_blue)); 
      tmr1.tmrSet(BLUE_freq); 
    }
    if (! tmr2.tmrActive()){    // RED
      digitalWrite(LED_red, ! digitalRead(LED_red)); 
      tmr2.tmrSet(RED_freq); 
    }
    if (! tmr3.tmrActive()){ // GREEN
      digitalWrite(LED_green, ! digitalRead(LED_green)); 
      tmr3.tmrSet(GREEN_freq); 
    }
  }
  if(buttonCount == 2){   // LED 1 only (blue)
    if (! tmr1.tmrActive()){    //BLUE
      digitalWrite(LED_blue, ! digitalRead(LED_blue)); 
      tmr1.tmrSet(BLUE_freq); 
    }
    digitalWrite(LED_red, LOW);
    digitalWrite(LED_green, LOW);
  }
  if(buttonCount == 3){   // LED 2 only (red)
    if (! tmr2.tmrActive()){    // RED
      digitalWrite(LED_red, ! digitalRead(LED_red)); 
      tmr2.tmrSet(RED_freq); 
    }
    digitalWrite(LED_blue, LOW);
    digitalWrite(LED_green, LOW);
  }
  if(buttonCount == 4){   // LED 3 only (green)
    if (! tmr3.tmrActive()){ // GREEN
      digitalWrite(LED_green, ! digitalRead(LED_green)); 
      tmr3.tmrSet(GREEN_freq); 
    }
    digitalWrite(LED_blue, LOW);
    digitalWrite(LED_red, LOW);
  }
  if(buttonCount == 5){   // LEDS OFF reset counter
    digitalWrite(LED_blue, LOW);
    digitalWrite(LED_red, LOW);
    digitalWrite(LED_green, LOW);
    buttonCount = 0;
  }
}
