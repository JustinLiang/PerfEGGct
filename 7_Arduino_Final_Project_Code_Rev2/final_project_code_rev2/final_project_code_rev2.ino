#define PIN_RESET 2
#define PIN_CE   3
#define PIN_DC   4
#define PIN_DIN  5
#define PIN_CLK  6
#define PIN_LED  7
#define PIN_BTN_RIGHT  10
#define PIN_BTN_MID  11
#define PIN_BTN_LEFT  12

#define PIN_LOAD A2
#define PIN_ACCEL A3

#define LCD_C     LOW
#define LCD_D     HIGH

#define LCD_X     84
#define LCD_Y     48
#define LED_BRIGHTNESS  50

#define ON 1
#define OFF 0

#define TRUE 1
#define FALSE 0

#define MODE_1 1  // Display chart
#define MODE_2 2  // Clear chart
#define MODE_3 3  // Display points on C#

// Previous values array size
#define PREV_ARRAY_SIZE 3

unsigned int accelOutput = 0;
double pi = 3.14159;
double mass = 0;
unsigned long startFlag = 0;
unsigned long prevTime = 0;
unsigned long timeDif = 0;
unsigned long dampedPeriod = 0;
unsigned long avgDampedPeriod = 0;
unsigned long avgDampedFrequency = 0;
unsigned long buttonPressedFlag = 0;

unsigned long dataPointsCount = 0;

const bool arduinoTestFlag = false;

// Define the number of samples to keep track of.  The higher the number,
// the more the readings will be smoothed, but the slower the output will
// respond to the input.  Using a constant rather than a normal variable lets
// use this value to determine the size of the readings array.
const int numReadings = 3;  // For averaging/smoothing

int accelReadings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int totalAccel = 0;                  // the running total
int averageAccel = 0;                // the average

// Array that stores the previous average values
unsigned long prevAverageArray[PREV_ARRAY_SIZE];

int dataPoints = 0;

int displayCounter = 0;

static const byte ASCII[][5] =
{
  {0x00, 0x00, 0x00, 0x00, 0x00} // 20
  , {0x00, 0x00, 0x5f, 0x00, 0x00} // 21 !
  , {0x00, 0x07, 0x00, 0x07, 0x00} // 22 "
  , {0x14, 0x7f, 0x14, 0x7f, 0x14} // 23 #
  , {0x24, 0x2a, 0x7f, 0x2a, 0x12} // 24 $
  , {0x23, 0x13, 0x08, 0x64, 0x62} // 25 %
  , {0x36, 0x49, 0x55, 0x22, 0x50} // 26 &
  , {0x00, 0x05, 0x03, 0x00, 0x00} // 27 '
  , {0x00, 0x1c, 0x22, 0x41, 0x00} // 28 (
  , {0x00, 0x41, 0x22, 0x1c, 0x00} // 29 )
  , {0x14, 0x08, 0x3e, 0x08, 0x14} // 2a *
  , {0x08, 0x08, 0x3e, 0x08, 0x08} // 2b +
  , {0x00, 0x50, 0x30, 0x00, 0x00} // 2c ,
  , {0x08, 0x08, 0x08, 0x08, 0x08} // 2d -
  , {0x00, 0x60, 0x60, 0x00, 0x00} // 2e .
  , {0x20, 0x10, 0x08, 0x04, 0x02} // 2f /
  , {0x3e, 0x51, 0x49, 0x45, 0x3e} // 30 0
  , {0x00, 0x42, 0x7f, 0x40, 0x00} // 31 1
  , {0x42, 0x61, 0x51, 0x49, 0x46} // 32 2
  , {0x21, 0x41, 0x45, 0x4b, 0x31} // 33 3
  , {0x18, 0x14, 0x12, 0x7f, 0x10} // 34 4
  , {0x27, 0x45, 0x45, 0x45, 0x39} // 35 5
  , {0x3c, 0x4a, 0x49, 0x49, 0x30} // 36 6
  , {0x01, 0x71, 0x09, 0x05, 0x03} // 37 7
  , {0x36, 0x49, 0x49, 0x49, 0x36} // 38 8
  , {0x06, 0x49, 0x49, 0x29, 0x1e} // 39 9
  , {0x00, 0x36, 0x36, 0x00, 0x00} // 3a :
  , {0x00, 0x56, 0x36, 0x00, 0x00} // 3b ;
  , {0x08, 0x14, 0x22, 0x41, 0x00} // 3c <
  , {0x14, 0x14, 0x14, 0x14, 0x14} // 3d =
  , {0x00, 0x41, 0x22, 0x14, 0x08} // 3e >
  , {0x02, 0x01, 0x51, 0x09, 0x06} // 3f ?
  , {0x32, 0x49, 0x79, 0x41, 0x3e} // 40 @
  , {0x7e, 0x11, 0x11, 0x11, 0x7e} // 41 A
  , {0x7f, 0x49, 0x49, 0x49, 0x36} // 42 B
  , {0x3e, 0x41, 0x41, 0x41, 0x22} // 43 C
  , {0x7f, 0x41, 0x41, 0x22, 0x1c} // 44 D
  , {0x7f, 0x49, 0x49, 0x49, 0x41} // 45 E
  , {0x7f, 0x09, 0x09, 0x09, 0x01} // 46 F
  , {0x3e, 0x41, 0x49, 0x49, 0x7a} // 47 G
  , {0x7f, 0x08, 0x08, 0x08, 0x7f} // 48 H
  , {0x00, 0x41, 0x7f, 0x41, 0x00} // 49 I
  , {0x20, 0x40, 0x41, 0x3f, 0x01} // 4a J
  , {0x7f, 0x08, 0x14, 0x22, 0x41} // 4b K
  , {0x7f, 0x40, 0x40, 0x40, 0x40} // 4c L
  , {0x7f, 0x02, 0x0c, 0x02, 0x7f} // 4d M
  , {0x7f, 0x04, 0x08, 0x10, 0x7f} // 4e N
  , {0x3e, 0x41, 0x41, 0x41, 0x3e} // 4f O
  , {0x7f, 0x09, 0x09, 0x09, 0x06} // 50 P
  , {0x3e, 0x41, 0x51, 0x21, 0x5e} // 51 Q
  , {0x7f, 0x09, 0x19, 0x29, 0x46} // 52 R
  , {0x46, 0x49, 0x49, 0x49, 0x31} // 53 S
  , {0x01, 0x01, 0x7f, 0x01, 0x01} // 54 T
  , {0x3f, 0x40, 0x40, 0x40, 0x3f} // 55 U
  , {0x1f, 0x20, 0x40, 0x20, 0x1f} // 56 V
  , {0x3f, 0x40, 0x38, 0x40, 0x3f} // 57 W
  , {0x63, 0x14, 0x08, 0x14, 0x63} // 58 X
  , {0x07, 0x08, 0x70, 0x08, 0x07} // 59 Y
  , {0x61, 0x51, 0x49, 0x45, 0x43} // 5a Z
  , {0x00, 0x7f, 0x41, 0x41, 0x00} // 5b [
  , {0x02, 0x04, 0x08, 0x10, 0x20} // 5c ¥
  , {0x00, 0x41, 0x41, 0x7f, 0x00} // 5d ]
  , {0x04, 0x02, 0x01, 0x02, 0x04} // 5e ^
  , {0x40, 0x40, 0x40, 0x40, 0x40} // 5f _
  , {0x00, 0x01, 0x02, 0x04, 0x00} // 60 `
  , {0x20, 0x54, 0x54, 0x54, 0x78} // 61 a
  , {0x7f, 0x48, 0x44, 0x44, 0x38} // 62 b
  , {0x38, 0x44, 0x44, 0x44, 0x20} // 63 c
  , {0x38, 0x44, 0x44, 0x48, 0x7f} // 64 d
  , {0x38, 0x54, 0x54, 0x54, 0x18} // 65 e
  , {0x08, 0x7e, 0x09, 0x01, 0x02} // 66 f
  , {0x0c, 0x52, 0x52, 0x52, 0x3e} // 67 g
  , {0x7f, 0x08, 0x04, 0x04, 0x78} // 68 h
  , {0x00, 0x44, 0x7d, 0x40, 0x00} // 69 i
  , {0x20, 0x40, 0x44, 0x3d, 0x00} // 6a j
  , {0x7f, 0x10, 0x28, 0x44, 0x00} // 6b k
  , {0x00, 0x41, 0x7f, 0x40, 0x00} // 6c l
  , {0x7c, 0x04, 0x18, 0x04, 0x78} // 6d m
  , {0x7c, 0x08, 0x04, 0x04, 0x78} // 6e n
  , {0x38, 0x44, 0x44, 0x44, 0x38} // 6f o
  , {0x7c, 0x14, 0x14, 0x14, 0x08} // 70 p
  , {0x08, 0x14, 0x14, 0x18, 0x7c} // 71 q
  , {0x7c, 0x08, 0x04, 0x04, 0x08} // 72 r
  , {0x48, 0x54, 0x54, 0x54, 0x20} // 73 s
  , {0x04, 0x3f, 0x44, 0x40, 0x20} // 74 t
  , {0x3c, 0x40, 0x40, 0x20, 0x7c} // 75 u
  , {0x1c, 0x20, 0x40, 0x20, 0x1c} // 76 v
  , {0x3c, 0x40, 0x30, 0x40, 0x3c} // 77 w
  , {0x44, 0x28, 0x10, 0x28, 0x44} // 78 x
  , {0x0c, 0x50, 0x50, 0x50, 0x3c} // 79 y
  , {0x44, 0x64, 0x54, 0x4c, 0x44} // 7a z
  , {0x00, 0x08, 0x36, 0x41, 0x00} // 7b {
  , {0x00, 0x00, 0x7f, 0x00, 0x00} // 7c |
  , {0x00, 0x41, 0x36, 0x08, 0x00} // 7d }
  , {0x10, 0x08, 0x08, 0x10, 0x08} // 7e ←
  , {0x78, 0x46, 0x41, 0x46, 0x78} // 7f →
};

void setup(void)
{
  Serial.begin(9600);
  ButtonInit();
  LcdInit();
  LcdClear();
  ResetAveragingArray(); // Initializes array
  InitPrevAverageArray();

  GotoXY(0,1);
  LcdWriteString("n: ");
}

void ButtonInit(void)
{
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_CE, OUTPUT);
  pinMode(PIN_RESET, OUTPUT);
}

void LcdInit(void)
{
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_CE, OUTPUT);
  pinMode(PIN_RESET, OUTPUT);
  pinMode(PIN_DC, OUTPUT);
  pinMode(PIN_DIN, OUTPUT);
  pinMode(PIN_CLK, OUTPUT);
  analogWrite(PIN_LED, LED_BRIGHTNESS);
  digitalWrite(PIN_RESET, LOW); // Internal registers and RAM are undefined, must RES
  digitalWrite(PIN_RESET, HIGH);
  LcdWrite(LCD_C, 0x21 );  // Set H=1 to get extended instruction set
  LcdWrite(LCD_C, 0xB1 );  // Set LCD Vop (Contrast). //0xB0 for 5V, 0XB1 for 3.3v, 0XBF if screen too dark
  LcdWrite(LCD_C, 0x14 );  // Optimal bias value n = 4 (refer to datasheet)
//  LcdWrite(LCD_C, 0x04 );  // Set Temp coefficent
  LcdWrite(LCD_C, 0x20 );  // H=0, exit extended instruction mode
  LcdWrite(LCD_C, 0x0C );  // Set LCD to be in normal mode
}

void ResetAveragingArray(void) {
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    accelReadings[thisReading] = 0;
  }
  readIndex = 0;              // the index of the current reading
  totalAccel = 0;                  // the running total
  averageAccel = 0;                // the average
}

void InitPrevAverageArray(void) {
  // Reset all elements in the peak times array to 0
  for (int index = 0; index < PREV_ARRAY_SIZE; index++) {
    prevAverageArray[index] = 0;
  }
}

void LcdWriteString(char *characters)
{
  while (*characters)
  {
    LcdWriteChar(*characters++);
  }
}

void LcdWriteChar(char character)
{
  LcdWrite(LCD_D, 0x00);
  for (int index = 0; index < 5; index++)
  {
    LcdWrite(LCD_D, ASCII[character - 0x20][index]);
  }
  LcdWrite(LCD_D, 0x00);
}

void LcdWriteDec(unsigned long n){
  if(n >= 10){
    LcdWriteDec(n/10);
    n = n%10;
  }
  LcdWriteChar(n+'0'); /* n is between 0 and 9 */
}

void LcdWrite(byte dc, byte data)
{
  digitalWrite(PIN_DC, dc);
  digitalWrite(PIN_CE, LOW);
  shiftOut(PIN_DIN, PIN_CLK, MSBFIRST, data);
  digitalWrite(PIN_CE, HIGH);
}

void LcdClear(void)
{
  for (int index = 0; index < LCD_X * LCD_Y; index++)
  {
    LcdWrite(LCD_D, 0x00);
  }
}

void GotoXY(int x, int y)
{
  LcdWrite( 0, 0x80 | x);  // Column.
  LcdWrite( 0, 0x40 | y);  // Row.  
}

void DisplayMass() {
  GotoXY(0,0);
  LcdWriteString("Mass: ");
  mass = analogRead(PIN_LOAD) - 155;
  if(mass < 0) {
    LcdWriteDec(0);
    displayCounter = 0;
  } else {
    LcdWriteDec(int(mass*1.44444));
    displayCounter = 0;
  }
  LcdWriteString("g  ");
  displayCounter++;
}

void GetDampedPeriods() {
  accelOutput = analogRead(PIN_ACCEL);

  // When you flick the controller, the accel exceeds 600
  // This tells us when to begin calculating the periods
  if(accelOutput > 310) { 
    startFlag = TRUE; // Start calculating the periods
  }

  while(startFlag == TRUE) {
    CalculateAndStoreAverage();
  }
}

void CalculateAndStoreAverage() {
  // subtract the last reading:
  totalAccel = totalAccel - accelReadings[readIndex];
  // read from the sensor:
  accelReadings[readIndex] = analogRead(PIN_ACCEL);
  // add the reading to the total:
  totalAccel = totalAccel + accelReadings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  averageAccel = totalAccel / numReadings;
  dataPointsCount++;

  // send it to the computer as ASCII digits
  if(arduinoTestFlag==true) {
    Serial.print(averageAccel);
    Serial.print(",");
  }

  if(digitalRead(PIN_BTN_MID) == 1) {
    WriteDecimalToSerial(averageAccel, MODE_1);
    WriteDecimalToSerial(dataPointsCount, MODE_3);
  }

  // Update array with the previous values
  for(int index = 0; index < PREV_ARRAY_SIZE; index++) {
    // If we are at the last element, then update it with the new averageAccel
    if(index == PREV_ARRAY_SIZE - 1) {  
      prevAverageArray[index] = averageAccel;
    } else {
      prevAverageArray[index] = prevAverageArray[index+1];
    }
  }

  if(dataPointsCount > 500) {
    startFlag = FALSE;
    dataPointsCount = 0;
  }
  
  delay(1);        // delay in between reads for stability
}

void loop(void)
{  
  DisplayMass();

  prevTime = millis();
  while(digitalRead(PIN_BTN_MID) == 1) { // While button is pressed
    GetDampedPeriods();
  }
  ResetAveragingArray();

  if(digitalRead(PIN_BTN_RIGHT) == 1) {
    WriteDecimalToSerial(255,MODE_2); // Command to clear screen
  }
}

// DEBUGGING COMMANDS
void WriteDecimalToSerial(int data, int mode) {
  if(arduinoTestFlag == false) {
    Serial.write(0); // Start byte
    Serial.write(mode);
    Serial.write(lowByte(data));
    Serial.write(highByte(data));
  }
}

