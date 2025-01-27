/*
Keyboard Matrix Controller
Hardware:
- Two 74HC595 shift registers:
  * First shift register controls rows (G: 1-7).
  * Second shift register controls columns (V: 8-14).
- Characters are displayed one at a time with a delay of 1 second.

Input:
- Type a word in Serial Monitor to simulate key presses.

Outputs:
- Outputs are activated for the corresponding rows (G) and columns (V).

*/

// Pin assignments for shift registers
const int latchPin = 8;   // ST_CP
const int clockPin = 12;  // SH_CP
const int dataPin = 11;   // DS

// Map keys to their row (G) and column (V) values
struct KeyMapping {
  char character;  // The key
  uint8_t row;     // Row number (G: 1-7)
  uint8_t column;  // Column number (V: 8-14)
};

// Define the key matrix mapping
KeyMapping keyMap[] = {
  {'k', 1, 8}, {'l', 1, 9}, {'ö', 1, 10}, {'ä', 1, 11}, {'m', 1, 12}, {',', 1, 13}, {'.', 1, 14},
  {'u', 2, 8}, {'i', 2, 9}, {'o', 2, 10}, {'p', 2, 11}, {'ü', 2, 12}, {'\n', 2, 13}, {'j', 2, 14},
  {'7', 3, 8}, {'8', 3, 9}, {'9', 3, 10}, {'0', 3, 11}, {'ß', 3, 12}, {'`', 3, 13}, {'\b', 3, 14},
  {'1', 4, 8}, {'2', 4, 9}, {'3', 4, 10}, {'4', 4, 11}, {'5', 4, 12}, {'6', 4, 13}, {'\t', 4, 14},
  {'q', 5, 9}, {'w', 5, 10}, {'e', 5, 11}, {'r', 5, 12}, {'t', 5, 13}, {'z', 5, 14},
  {'a', 6, 9}, {'s', 6, 10}, {'d', 6, 11}, {'f', 6, 12}, {'g', 6, 13}, {'h', 6, 14},
  {'y', 7, 8}, {'x', 7, 9}, {'c', 7, 10}, {'v', 7, 11}, {'b', 7, 12}, {'n', 7, 13}, {'U', 7, 14}  // U: Umsch
};

// Function prototypes
void shiftOutData(uint16_t rowData, uint16_t columnData);
KeyMapping* findKeyMapping(char key);

void setup() {
  // Set pins to OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  // Begin Serial communication
  Serial.begin(9600);
  Serial.println("Type a word in the Serial Monitor and press Enter:");
}

void loop() {
  // Check if user input is available
  if (Serial.available() > 0) {
    String word = Serial.readStringUntil('\n');  // Read the word
    word.trim();                                // Remove any trailing spaces or newlines

    for (int i = 0; i < word.length(); i++) {
      char currentChar = word[i];

      // Find the row and column for the character
      KeyMapping* key = findKeyMapping(currentChar);
      if (key != nullptr) {
        // Output the row and column signals
        uint16_t rowData = ~(1 << (key->row - 1));    // Set the corresponding row LOW
        uint16_t columnData = (1 << (key->column - 8));  // Set the corresponding column HIGH
        shiftOutData(rowData, columnData);
      } else {
        Serial.print("Character '");
        Serial.print(currentChar);
        Serial.println("' not found in key map!");
      }

      delay(1000);  // 1-second delay before processing the next character
    }

    // Clear all signals after finishing the word
    shiftOutData(0xFFFF, 0x00);
  }
}

// Shift out data to the shift registers
void shiftOutData(uint16_t rowData, uint16_t columnData) {
  digitalWrite(latchPin, LOW);  // Begin shifting

  // Shift out data for rows (first shift register)
  shiftOut(dataPin, clockPin, MSBFIRST, rowData >> 8);  // High byte
  shiftOut(dataPin, clockPin, MSBFIRST, rowData & 0xFF); // Low byte

  // Shift out data for columns (second shift register)
  shiftOut(dataPin, clockPin, MSBFIRST, columnData >> 8);  // High byte
  shiftOut(dataPin, clockPin, MSBFIRST, columnData & 0xFF); // Low byte

  digitalWrite(latchPin, HIGH);  // Latch the data
}

// Find the row and column for a given key
KeyMapping* findKeyMapping(char key) {
  for (int i = 0; i < sizeof(keyMap) / sizeof(KeyMapping); i++) {
    if (keyMap[i].character == key) {
      return &keyMap[i];
    }
  }
  return nullptr;
}
