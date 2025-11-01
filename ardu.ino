#include <Wire.h>              // Include Wire library for I2C
#include <LiquidCrystal_I2C.h>  // Include LCD library for I2C

// Define the button pin
const int buttonPin = 2;
int buttonState = 0;         // Variable to hold button state
int lastButtonState = 0;     // Last button state for debounce
int messageIndex = 0;        // Index to keep track of the current message

// Initialize the LCD screen (Address 0x27, 16 columns, 2 rows)
LiquidCrystal_I2C lcd(0x27, 16, 2);  

// Define the messages to display
const String messages[] = {
  "And all that I",
  "do is sit",
  "and think about",
  "you if I knew",
  "What you'd do",
  "Collapse",
  "My veins",
  "Wearing",
  "beautiful shoes",
  "It's not living",
  "If it's not with",
  "You <3"  // You can add more messages if needed
};
const int numMessages = sizeof(messages) / sizeof(messages[0]);  // Calculate number of messages

void setup() {
  // Start the serial communication
  Serial.begin(9600);
  
  // Initialize the button pin as an input
  pinMode(buttonPin, INPUT_PULLUP);  // Use internal pull-up resistor
  
  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  
  // Display the initial message
  lcd.setCursor(0, 0);
  lcd.print("INLIINWY");
  lcd.setCursor(0, 1);
  lcd.print("The 1975");
}

void loop() {
  // Read the state of the button
  buttonState = digitalRead(buttonPin);

  // Check for a button press (debounced)
  if (buttonState == LOW && lastButtonState == HIGH) {
    delay(50);  // Debounce delay
    // Switch to the next message
    messageIndex = (messageIndex + 1) % numMessages;
    updateDisplay();  // Update the LCD with new text
  }
  
  // Store the current button state for the next loop iteration
  lastButtonState = buttonState;
}

// Function to update the text on the LCD based on the current message index
void updateDisplay() {
  lcd.clear();  // Clear the previous display
  
  // Display the current message
  lcd.setCursor(0, 0);
  lcd.print(messages[messageIndex]);  // Display message on the first line
}
