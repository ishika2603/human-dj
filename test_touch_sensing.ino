const int touchPin1 = A5; // Define the analog pin connected to the touch sensor
const int touchPin2 = A3;
const int threshold = 750; // Set a threshold for detecting touch (adjust based on testing)

void setup() {
  Serial.begin(9600); // Begin serial communication to monitor the touch input
}

void loop() {
  int touchValue1 = analogRead(touchPin1); // Read the analog value from the touch sensor
  int touchValue2 = analogRead(touchPin2); 

  // Serial.print("Person 1 ");
  // Serial.println(touchValue1);

  // Serial.print("Person 2 ");
  // Serial.println(touchValue2);

  if (touchValue1 < threshold) {
    Serial.println("Person 1 detected!"); // Print a message if a touch is detected
  } 
  if (touchValue2 < threshold) {
    Serial.println("Person 2 detected!"); // Print a message if a touch is detected
  } // else {
  //   Serial.println("No touch."); // Print a message if no touch is detected
  // }

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

