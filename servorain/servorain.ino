#include <Servo.h>
#define ledPin 6
#define sensorPin A0

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0; //angle
boolean open=true; //is window open


void setup() {

  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, HIGH);

}


void loop() {

  Serial.print("Analog output: ");
  myservo.attach(9); //attaching the servo with arduino (pin no=9)

  Serial.println(readSensor());

  delay(1000);

}


//  This function returns the analog data to calling function

int readSensor() {

  int sensorValue = analogRead(sensorPin);  // Read the analog value from sensor

  int outputValue = map(sensorValue, 0, 1023, 255, 0); // map the 10-bit data to 8-bit data
  // Serial.println("\noutside loop");
   Serial.println(sensorValue);
  analogWrite(ledPin, outputValue); // generate PWM signal
  if(outputValue>0)
  {
    if(open) //if window open, then close it
    {
      for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
      myservo.write(pos);
      delay(2);
      
    }
     Serial.print("\nAnalog output inside loop1: ");
    Serial.print(pos);
    open=false; // window is close now
  }
  }
 
  else
  {
    if(!open) //window closed, then open
    {
      for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
      myservo.write(pos);
      delay(2);
      
    }
     Serial.print("\nAnalog output inside loop2: ");
     Serial.print(pos);
    open=true;
  }
  }
  return outputValue;             // Return analog rain value

}