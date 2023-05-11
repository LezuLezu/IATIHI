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

tmrMicros tmr1; 
tmrMicros tmr2;
tmrMicros tmr3;
void setup() { 
  pinMode(4, OUTPUT); 
  digitalWrite(4, LOW); 
  pinMode(5, OUTPUT); 
  digitalWrite(5, LOW);
  pinMode(6, OUTPUT); 
  digitalWrite(6, LOW);
} 
  
void loop() { 
  if (! tmr1.tmrActive()){ 
    digitalWrite(4, ! digitalRead(4)); 
    //Interne LED knippert om de 0,5 seconde 
    tmr1.tmrSet(500000); 
  }
  if (! tmr2.tmrActive()){ 
    digitalWrite(5, ! digitalRead(5)); 
    //Interne LED knippert om de 0,5 seconde 
    tmr2.tmrSet(500000); 
  }
  if (! tmr3.tmrActive()){ 
    digitalWrite(6, ! digitalRead(6)); 
    //Interne LED knippert om de 0,5 seconde 
    tmr3.tmrSet(500000); 
  }
}
 
