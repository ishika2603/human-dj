const int touchPins[] = {A3, A5};
const int numPeople = sizeof(touchPins) / sizeof(touchPins[0]);
int touchThresholds[numPeople]; // store dynamic thresholds for each pin
int touchStatus[numPeople]; // store current touch status (0 or 1)

void setup() {
  Serial.begin(9600); // Begin serial communication to monitor the touch input
  Serial.println("Starting calibration...");
  calibrateThresholds(); // Set initial thresholds based on environment
  Serial.println("Ending calibration...");
}

void calibrateThresholds() {
  for (int i = 0; i < numPeople; i++) {
    int initialValue = analogRead(touchPins[i]);
    touchThresholds[i] = initialValue - 100; // Set threshold slightly below initial value
    Serial.print("Calibrated threshold for Person ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(touchThresholds[i]);
  }
}

void loop() {

  for (int i = 0; i < numPeople; i++) {
    int touchValue = analogRead(touchPins[i]); // Read value from each sensor

    if (touchValue < touchThresholds[i]) {
      touchStatus[i] = 1;

      Serial.print("Person ");
      Serial.print(i + 1);
      Serial.println(" detected!"); // Print message if touch is detected
    }
    else{
      touchStatus[i] = 0;
    } 
  }

  // Print touch status array
  Serial.print("Touch Status: [");
  for (int i = 0; i < numPeople; i++) {
    Serial.print(touchStatus[i]);
    if (i < numPeople - 1) {
      Serial.print(", ");
    }
  }
  Serial.println("]");

  delay(100); // Small delay for stability
}

// const int touchPin = A5; // Analog pin connected to the touch sensor
// const int numReadings = 10; // Number of readings to calculate the moving average
// const int threshold = 50; // Change in voltage threshold for touch detection

// int readings[numReadings]; // Array to store readings for moving average
// int readIndex = 0; // Index of the current reading
// int total = 0; // Total of all readings in the array
// int average = 0; // Moving average of the readings

// void setup() {
//   Serial.begin(9600); // Begin serial communication
//   for (int i = 0; i < numReadings; i++) {
//     readings[i] = 0; // Initialize all readings to 0
//   }
// }

// void loop() {
//   // Subtract the oldest reading from the total
//   total -= readings[readIndex];
  
//   // Read the new touch value
//   int touchValue = analogRead(touchPin);
  
//   // Add the new reading to the array and the total
//   readings[readIndex] = touchValue;
//   total += touchValue;
  
//   // Advance to the next position in the array
//   readIndex = (readIndex + 1) % numReadings;

//   // Calculate the moving average
//   average = total / numReadings;
  
//   // Print the moving average and current touch value
//   Serial.print("Current Value: ");
//   Serial.print(touchValue);
//   Serial.print(" - Moving Average: ");
//   Serial.println(average);

//   // Check if the change exceeds the threshold for touch detection
//   if (abs(touchValue - average) > threshold) {
//     Serial.println("Touch detected!");
//   } else {
//     Serial.println("No touch.");
//   }
// }

