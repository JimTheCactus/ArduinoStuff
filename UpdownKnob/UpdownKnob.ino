#define APIN 2
#define BPIN 3
#define CHATTERTIMEOUT 1000 // Chatter timeout in microseconds (datasheet suggests 1000)

void setup() {
  // Setup our two pins
  pinMode(APIN,INPUT);
  pinMode(BPIN,INPUT);
  // And tell the keyboard driver to get ready
  Keyboard.begin();
}

unsigned long hightime=0; // Keeps track of how long we've been active (used for debounce) 
unsigned char latched=0; // Keeps track of whether we've already acted on the rising edge.
void loop() {
  unsigned char state; // holds the current state of the main pin on the quadrature encoder
  unsigned char dir; // Holds the current state of the quadrature pin on the encoder

  // Get the current state of the main pin
  state = digitalRead(APIN);
  // If it's high
  if (state != LOW) {
    // And we haven't seen a rising edge yet
    if (hightime == LOW) {
      // Mark when we saw it
      hightime=micros();
    }
    // If we have seen one
    else {
      // check to make sure it's been there long enough to not be chatter
      // and make sure we haven't already tols the PC about it
      if (micros()-hightime > CHATTERTIMEOUT && !latched) {
        // If we haven't start by getting the quadrature output (which should be stable now)
        dir=digitalRead(BPIN);
        // If we're going forward
        if (dir == LOW) {
          // Push up
          Keyboard.write(KEY_UP_ARROW);
        }
        else {
          // Otherwise push down
          Keyboard.write(KEY_DOWN_ARROW);
        }
        // And mark that we've taken action on this edge
        latched=1;
      } 
    }
  }
  else{
    // If the main signal is low, then reset our two signals.
    hightime=0;
    latched=0;
  }
}


