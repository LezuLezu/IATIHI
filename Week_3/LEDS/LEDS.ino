#define BUTTON 7

// timer freqs in micro seconds
// 1hz -> 1000000
// 0.5hz -> 2000000
// 0.25hz -> 4000000

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
    // if (nextChangeTime > currentTime) 
    // overFlow = false; 
    // else overFlow = true; }
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
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(4, OUTPUT);   
  pinMode(5, OUTPUT); 
  pinMode(6, OUTPUT); 
  digitalWrite(4, LOW); 
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  
  Serial.begin(9600);
}

void loop() {
  if(!digitalRead(BUTTON)){
    delay(100);
    if(!digitalRead(BUTTON)){
      buttonCount += 1;   
    }
  }
  Serial.println(buttonCount);
  if(buttonCount == 1){   // All LEDS
    if (! tmr1.tmrActive()){    //BLUE
      digitalWrite(4, ! digitalRead(4)); 
      tmr1.tmrSet(1000000); 
    }
    if (! tmr2.tmrActive()){    // RED
      digitalWrite(5, ! digitalRead(5)); 
      tmr2.tmrSet(2000000); 
    }
    if (! tmr3.tmrActive()){ // GREEN
      digitalWrite(6, ! digitalRead(6)); 
      tmr3.tmrSet(4000000); 
    }
  }
  if(buttonCount == 2){   // LED 1 only (blue)
    if (! tmr1.tmrActive()){ 
      digitalWrite(4, ! digitalRead(4)); 
      tmr1.tmrSet(1000000); 
    }
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
  }
  if(buttonCount == 3){   // LED 2 only (red)
    if (! tmr2.tmrActive()){ 
      digitalWrite(5, ! digitalRead(5)); 
      tmr2.tmrSet(2000000); 
    }
    digitalWrite(4, LOW);
    digitalWrite(6, LOW);
  }
  if(buttonCount == 4){   // LED 3 only (green)
    if (! tmr3.tmrActive()){ 
      digitalWrite(6, ! digitalRead(6)); 
      tmr3.tmrSet(4000000); 
    }
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }
  if(buttonCount == 5){   // LEDS OFF reset counter
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    buttonCount = 0;
  }
}
