#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define the dimensions of the display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Create an OLED display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // -1 for no reset pin

const char* linesA[] = {
    "CodeReady..",
    "MainFile..",
    "Input...",
    "File9@0...",
    "Project;J5",
    ".",
    ".",
    ".",
    "ALIVE"
};

const char* linesB[] = {
  "",
  "RnFiles",
  "RnCommands",
  "RnBattery",
  "Complete",
  "ReadyComs."
  "Coms=RnFiles"
  "File$H4R3"
};

const char* linesC[] = {
  "",
  "",
  "Caution!",
  "Battery",
  "LOW"
  };

const int numLinesA = sizeof(linesA) / sizeof(linesA[0]);
const int numLinesB = sizeof(linesB) / sizeof(linesB[0]);
const int numLinesC = sizeof(linesC) / sizeof(linesC[0]);
const int typingDelay = 100; // Milliseconds between each character

const unsigned long countdownDuration = 600000;



void setup() {
    // Initialize the display
    display.begin(SSD1306_PAGEADDR, 0x3C); // Use the correct I2C address
    display.clearDisplay(); // Clear the display buffer
    display.setTextSize(1); // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
     display.setRotation(-1); //Rotate the display 90 degrees
    display.setCursor(0, 0); // Start at top-left corner

    // Type out each line
    for (int i = 0; i < numLinesA; i++) {
        typeOutText(linesA[i]);
        display.println(); // Move to the next line
    }

    // Display the text on the screen
    display.display();
}

void loop() {
  
  displayText();
    
  // Optional: Add a pause before restarting the countdown
  delay(1000);
  
  
}

void typeOutText(const char* text) {
    for (const char* ptr = text; *ptr != '\0'; ptr++) {
        display.print(*ptr); // Print the character
        display.display(); // Refresh the display
        delay(typingDelay); // Wait before the next character
    }
}

void displayText(){
  unsigned long startTime = millis(); // Record start time

  // Countdown from 100% to 0%
  for (int i = 100; i >= 0; i--) {
    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - startTime;

    // Calculate the delay needed for the countdown
    unsigned long timePerPercentage = countdownDuration / 100; // Time per percent

    // Ensure the delay does not exceed the remaining time
    unsigned long delayTime = timePerPercentage - elapsedTime % timePerPercentage;

    display.clearDisplay();

    // Draw the percentage text
    display.setCursor(0, 0);
    display.print(F("Power: "));
    display.print(i);
    display.print(F("%"));

    display.display();

    delay(delayTime); // Delay to make the countdown visible, adjust as needed

    // Check if the countdown is complete
    if (elapsedTime >= countdownDuration) {
      break;
    }

    for (int i = 0; i < numLinesB; i++) {
        typeOutText(linesB[i]);
        display.println(); // Move to the next line  
    }  

    if(i < 20){
      for (int i = 0; i < numLinesC; i++) {
        typeOutText(linesC[i]);
        display.println(); // Move to the next line  
     }  
    }
  }
}