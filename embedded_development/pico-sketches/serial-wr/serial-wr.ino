String input = "";
bool isComplete = false;

// this example has potential application in developing macros for keyboard
// when the serial reader picks a combination of key pressed, launch a specific command
void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("Please input a string and press enter when finished...");
}

void loop() {
  if (Serial.available()) {
    char charInputted = Serial.read();
    input += charInputted;
    if (charInputted == '\n') {
      isComplete = true;
    }
  }

  if (isComplete) {
    Serial.print("Text inputted: ");
    Serial.print(input);
    resetComponents();
  }
}

void resetComponents() {
  input = "";
  isComplete = false;
}
