const int analogPinPullDown = A0; // Analog pin for pull-down resistor buttons
const int analogPinPullUp = A1;   // Analog pin for pull-up resistor buttons
const int numButtons = 3;         // Number of buttons per setup

// Thresholds for each button (adjust experimentally for pull-down)
int thresholdsPullDown[numButtons] = {900, 800, 700};

// Thresholds for each button (adjust experimentally for pull-up)
int thresholdsPullUp[numButtons] = {100, 200, 300};

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Process pull-down button setup
  int analogValuePullDown = analogRead(analogPinPullDown); // Read pull-down pin
  int buttonPressedPullDown = -1;

  for (int i = 0; i < numButtons; i++) {
    if (analogValuePullDown > thresholdsPullDown[i]) {
      buttonPressedPullDown = i + 1;
      break;
    }
  }

  if (buttonPressedPullDown != -1) {
    Serial.print("Pull-Down Button ");
    Serial.print(buttonPressedPullDown);
    Serial.println(" pressed");
    Serial.println(analogValuePullDown);
    delay(200); // Debounce
  }

  // Process pull-up button setup
  int analogValuePullUp = analogRead(analogPinPullUp); // Read pull-up pin
  int buttonPressedPullUp = -1;

  for (int i = 0; i < numButtons; i++) {
    if (analogValuePullUp < thresholdsPullUp[i]) { // Inverted logic for pull-up
      buttonPressedPullUp = i + 1;
      break;
    }
  }

  if (buttonPressedPullUp != -1) {
    Serial.print("Pull-Up Button ");
    Serial.print(buttonPressedPullUp);
    Serial.println(" pressed");
    Serial.println(analogValuePullUp);
    delay(200); // Debounce
  } else {
    Serial.println(analogValuePullUp);
    delay(200);} // Debounce
}
