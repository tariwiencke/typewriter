/*
Shift Register Example
for 74HC595 shift register
This sketch turns reads serial input and uses it to set the pins
of two 74HC595 shift registers.
Hardware:
* Two 74HC595 shift registers connected in series.
* 74HC595 shift register latch pin (ST_CP) connected to pin 8 of Arduino.
* Clock pin (SH_CP) connected to pin 12 of Arduino.
* Data pin (DS) connected to pin 11 of Arduino.
* LEDs attached to the outputs of the shift registers.
Created 22 May 2009
Modified for two shift registers 26 Jan 2025
by User
*/

// Pins connected to the shift registers
const int latchPin = 8;   // ST_CP
const int clockPin = 12;  // SH_CP
const int dataPin = 11;   // DS

void setup() {
  // Set all pins to OUTPUT mode
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  // Begin serial communication (for debugging, if needed)
  Serial.begin(9600);
}

void loop() {
  // Use a 16-bit variable to store the data for two shift registers
  uint16_t ledData = 1; // Start with the first LED ON

  for (int i = 0; i < 16; i++) { // Loop through all 16 LEDs
    shiftOutData(ledData);      // Shift out data to the registers
    ledData <<= 1;              // Move to the next LED
    delay(1000);                 // Delay to create the running effect
  }
}

// Function to shift out data to two shift registers
void shiftOutData(uint16_t data) {
  // Begin shifting
  digitalWrite(latchPin, LOW);

  // Shift out the 16-bit data (high byte first, then low byte)
  shiftOut(dataPin, clockPin, MSBFIRST, highByte(data)); // High byte (8 bits)
  shiftOut(dataPin, clockPin, MSBFIRST, lowByte(data));  // Low byte (8 bits)

  // Latch the data to the output pins
  digitalWrite(latchPin, HIGH);
}
