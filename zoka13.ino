/*
  Serial Event example
 
 When new serial data arrives, this sketch adds it to a String.
 When a newline is received, the loop prints the string and 
 clears it.
 
 A good test for this is to try it with a GPS receiver 
 that sends out NMEA 0183 sentences. 
 
 Created 9 May 2011
 by Tom Igoe
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/SerialEvent
 
 */

#include <Servo.h> 
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 

int pos = 0;    // variable to store the servo position 
int servopin = 9;
const int buttonPinRight = 2;     // the number of the pushbutton pin
const int buttonPinLeft = 3;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

const int MIN = 0;
const int MAX = 90;
const int servoStart = MAX;

// variables will change:
int rightSensor = 0;         // variable for reading the pushbutton status
int leftSensor = 0;         // variable for reading the pushbutton status

int _direction = 0; //Can also be -1, to close, +1 to open.

char* buffer;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  
  myservo.attach(servopin);  // attaches the servo on pin 9 to the servo object 
  myservo.write(servoStart);
  pos = servoStart;
  
  pinMode(ledPin, OUTPUT);      
  pinMode(buttonPinRight, INPUT);     
  pinMode(buttonPinLeft, INPUT);
}

void loop() 
{
  rightSensor = digitalRead(buttonPinRight);
  leftSensor = digitalRead(buttonPinLeft);
  
  if (rightSensor == HIGH && leftSensor == HIGH) 
  {
    _direction = 0; //Stop when both bottons pushed
    Serial.println("BOTH_TOUCH");
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  
  Serial.println(pos);
  
  if(pos <= MIN)
  {
     _direction = 1;
  }
  
  if(pos > MAX)
  {
    _direction = 0; 
  }
  
  if(stringComplete)
  {
    if(pos >= MAX)
    {
      _direction = -1;
    }
    stringComplete = false;
  }
  
  pos += _direction;
  myservo.write(pos);
  delay(20);
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}
