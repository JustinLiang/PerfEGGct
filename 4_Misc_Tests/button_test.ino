#include "fix_fft.h"
char im[512];
char re[512];
#define F_SAMPLE 128
char buffer[5];

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

int count = 0;

bool buttonPressed = false;

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
  if(buttonM == 1 && analogRead(PIN_ACCEL_Y) > 310) {
    buttonPressed = true;
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
  
    Serial.print("#S|LOGDATA|[");
    Serial.print(itoa((average), buffer, 10));
    Serial.println("]#");
    
    im[count] = 0;
    re[count] = (char)(average);
    count++;
    if (count >= 512) { // save 256 samples
      fix_fft(re,im,7,0);
//      print_fft((char *)"2. Two tones of 1040Hz and 1280Hz sampled at 5120Hz");
      count = 0;
      buttonPressed = false;
    }

  //  Serial.write(average>>8);
    delay(1);        // delay in between reads for stability
  }
}

// Generate the magnitude of each bin and print it on the serial monitor
void print_fft(char *title)
{
  int i,j,largest;
  char str[65];
  char linfo[6];

  str[64] = 0;  
  largest = 0;
  // Find the largest entry which will determine how many lines
  // are needed to print the whole histogram
  for (i=0; i< 64;i++){
    re[i] = sqrt(re[i] * re[i] + im[i] * im[i]);
    if(re[i] > largest)largest = re[i];
  }
  // print a blank line just in case there's
  // garbage when the Serial monitor starts up
  Serial.println("");
  // and the title
  Serial.println(title);
  Serial.println("");
  // print the histogram starting with the highest amplitude
  // and working our way back down to zero.
  for(j=largest;j >= 0;j--) {
    for(i=0;i<64;i++) {
      // If the magnitude of this bin is at least as large as
      // the current magnitude we print an asterisk
      if(re[i] >= j)str[i] = '*';
      // otherwise print a space
      else str[i] = ' ';
    }
    sprintf(linfo,"%3d ",j);
    Serial.print(linfo);
    Serial.println(str);
  }
  // print the bin numbers along the bottom
  Serial.print("    ");
  for(i=0;i<64;i++) {
    Serial.print(i%10);
  }
  Serial.println("");
  Serial.print("    ");
  for(i=0;i<64;i++) {
    if(i < 10)Serial.print(" ");
    else Serial.print((i/10)%10);
  }
  Serial.println("");
}




//#define LOG_OUT 1 // use the log output function
//#define FHT_N 256 // set to 256 point fht
//#include <FHT.h> // include the library
//
//
//#define PIN_BTN_LEFT  12
//#define PIN_BTN_MID  11
//#define PIN_BTN_RIGHT  10
//
//#define PIN_ACCEL_Y A3
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
//const int numReadings = 10;
//
//int readings[numReadings];      // the readings from the analog input
//int readIndex = 0;              // the index of the current reading
//int total = 0;                  // the running total
//int average = 0;                // the average
//
//int count = 0;
//
//void setup() {
//  Serial.begin(9600);
//  pinMode(PIN_BTN_LEFT, INPUT);
//  pinMode(PIN_BTN_MID, INPUT);
//  pinMode(PIN_BTN_RIGHT, INPUT);
//  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
//    readings[thisReading] = 0;
//  }
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
//  // subtract the last reading:
//  total = total - readings[readIndex];
//  // read from the sensor:
//  readings[readIndex] = analogRead(PIN_ACCEL_Y);
//  // add the reading to the total:
//  total = total + readings[readIndex];
//  // advance to the next position in the array:
//  readIndex = readIndex + 1;
//
//  // if we're at the end of the array...
//  if (readIndex >= numReadings) {
//    // ...wrap around to the beginning:
//    readIndex = 0;
//  }
//
//  // calculate the average:
//  average = total / numReadings;
//  // send it to the computer as ASCII digits
////  Serial.println(average);
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
//  fht_input[count] = average; // put real data into bins
//  count++;
//  if (count >= FHT_N) { // save 256 samples
//    fht_window(); // window the data for better frequency response
//    fht_reorder(); // reorder the data before doing the fht
//    fht_run(); // process the data in the fht
//    fht_mag_log(); // take the output of the fht
//    sei();
//    Serial.write(255); // send a start byte
//    Serial.write(fht_log_out, FHT_N/2); // send out the data
//    count = 0;
//  }
//
////  Serial.write(average>>8);
//  delay(1);        // delay in between reads for stability
//}






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
