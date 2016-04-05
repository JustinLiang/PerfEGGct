#define PIN_BTN_LEFT  12
#define PIN_BTN_MID  11
#define PIN_BTN_RIGHT  10

#define PIN_ACCEL_Y A3

unsigned long buttonL;
unsigned long buttonM;
unsigned long buttonR;
unsigned long yAccel;

// Define the number of samples to keep track of.  The higher the number,
// the more the readings will be smoothed, but the slower the output will
// respond to the input.  Using a constant rather than a normal variable lets
// use this value to determine the size of the readings array.
const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

void setup() {
  Serial.begin(9600);
  pinMode(PIN_BTN_LEFT, INPUT);
  pinMode(PIN_BTN_MID, INPUT);
  pinMode(PIN_BTN_RIGHT, INPUT);
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop() {
//  yAccel = analogRead(PIN_ACCEL_Y);
  buttonL = digitalRead(PIN_BTN_LEFT);
  buttonM = digitalRead(PIN_BTN_MID);
  buttonR = digitalRead(PIN_BTN_RIGHT);

//  Serial.print("y: ");
//  Serial.println(yAccel);
//  Serial.print(" btnL: ");
//  Serial.print(buttonL);
//  Serial.print(" btnM: ");
//  Serial.print(buttonM);
//  Serial.print(" btnR: ");
//  Serial.print(buttonR);
//  Serial.println();

  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(PIN_ACCEL_Y);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  Serial.println(average);
//  Serial.write(0); // Start byte
//  Serial.write(lowByte(average));
//  Serial.write(highByte(average));
//  Serial.write(lowByte(average)==255 + highByte(average)==255); // Escape byte
  
//  Serial.print(1); // Start byte
//  Serial.print(" ");
//  Serial.print(lowByte(average));
//  Serial.print(" ");
//  Serial.print(highByte(average));
//  Serial.println(" ");

//  Serial.write(average>>8);
  delay(1);        // delay in between reads for stability
}

//#define PIN_BTN_LEFT  12
//#define PIN_BTN_MID  11
//#define PIN_BTN_RIGHT  10
//
//#define PIN_ACCEL_Y A3
//
//#define FILTER_SIZE 5
//#define SIGMA 1.4
//double gaussFilter[FILTER_SIZE];
//
//unsigned long buttonL;
//unsigned long buttonM;
//unsigned long buttonR;
//unsigned long yAccel;
//
//// Define the number of samples to keep track of.  The higher the number,
//// the more the readings will be smoothed, but the slower the output will
//// respond to the input.  Using a constant rather than a normal variable lets
//// use this value to determine the size of the readings array.
//const int numReadings = FILTER_SIZE;
//
//int readings[numReadings];      // the readings from the analog input
//int readIndex = 0;              // the index of the current reading
//double total = 0;                  // the running total
//
//void CalculateGaussianFilter(void) {
//  for(int index = 0; index < numReadings; index++) {
//    gaussFilter[index] = (1/(sqrt(2*PI)*SIGMA))*exp(-pow((index-2),2)/(2*pow(SIGMA,2)));
//  }
//}
//
//void setup() {
//  Serial.begin(9600);
//  pinMode(PIN_BTN_LEFT, INPUT);
//  pinMode(PIN_BTN_MID, INPUT);
//  pinMode(PIN_BTN_RIGHT, INPUT);
//  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
//    readings[thisReading] = 0;
//  }
//  CalculateGaussianFilter();
//}
//
//void loop() {
////  yAccel = analogRead(PIN_ACCEL_Y);
//  buttonL = digitalRead(PIN_BTN_LEFT);
//  buttonM = digitalRead(PIN_BTN_MID);
//  buttonR = digitalRead(PIN_BTN_RIGHT);
//
////  Serial.print("y: ");
////  Serial.println(yAccel);
////  Serial.print(" btnL: ");
////  Serial.print(buttonL);
////  Serial.print(" btnM: ");
////  Serial.print(buttonM);
////  Serial.print(" btnR: ");
////  Serial.print(buttonR);
////  Serial.println();
//
//  readings[readIndex] = analogRead(PIN_ACCEL_Y);
//
//  for(int index = 0; index < numReadings; index++) {
//    int newIndex = (readIndex-numReadings/2+index>=0)?((readIndex-numReadings/2+index))%5:
//                      (numReadings-1+newIndex+index)%5;
//    total += gaussFilter[index]*readings[newIndex];
////    Serial.print("index: ");
////    Serial.print(index);
////    Serial.println();
////    Serial.print("readIndex: ");
////    Serial.print(readIndex);
////    Serial.println();
////    Serial.print("newIndex: ");
////    Serial.print(newIndex);
////    Serial.println();
////    Serial.print("gaussFilter: ");
////    Serial.print(gaussFilter[index]);
////    Serial.println();
////    Serial.print("readings: ");
////    Serial.print(readings[newIndex]);
////    Serial.println();
////    Serial.print("Total: ");
////    Serial.print(total);
////    Serial.println();
//  }
//  // advance to the next position in the array:
//  readIndex = readIndex + 1;
//
//  // if we're at the end of the array...
//  if (readIndex >= numReadings) {
//    // ...wrap around to the beginning:
//    readIndex = 0;
//  }
//  
//  // send it to the computer as ASCII digits
//  Serial.println(total);
////  for(int index = 0; index < numReadings; index++) {
////    Serial.println(gaussFilter[index]);
////  }
//  total = 0;
////  Serial.write(0); // Start byte
////  Serial.write(lowByte(average));
////  Serial.write(highByte(average));
////  Serial.write(lowByte(average)==255 + highByte(average)==255); // Escape byte
//  
////  Serial.print(1); // Start byte
////  Serial.print(" ");
////  Serial.print(lowByte(average));
////  Serial.print(" ");
////  Serial.print(highByte(average));
////  Serial.println(" ");
//  delay(1);        // delay in between reads for stability
//}
