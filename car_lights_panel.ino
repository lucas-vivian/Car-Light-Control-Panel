/*
  CAR LIGHTS PANEL
  
  created 17/04/2022
  by Lucas Vivian
*/

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;    // the number of the pushbutton pin
const int ledPin = 11;      // the number of the LED pin
const int neonPin = 8;      // the number of the transistor pin related to neon light

// Variables will change:
int ledState = LOW;         // the current state of the output pin (IT'S INVERTED, LOW = LED ON)
int buttonState = LOW;             // the current reading from the input pin (ORIGINAL WAS INITIALIZING WITHOUT INITIAL VALUE)
int lastButtonState = HIGH;   // the previous reading from the input pin (ASSUMING SAME INVERSION)
int neonState = HIGH;

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(neonPin, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);
  digitalWrite(neonPin, neonState);
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
        neonState = !neonState;
      }
    }
  }

  // set the LED:
  digitalWrite(ledPin, ledState);
  digitalWrite(neonPin, neonState);

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
