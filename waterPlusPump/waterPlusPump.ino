#include <Servo.h>
#define ledPin 6
#define ledPin2 7
#define WsensorPin1 A0
#define WsensorPin2 A2
const int RELAY_PIN = A5;
#define soilSensorPin A1
#define soilPin 8
#define rainPin A3

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0; //servo angle
boolean open=true;  //is window open


void setup() {
  Serial.begin(9600);
  //water
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin2, HIGH);
  pinMode(RELAY_PIN, OUTPUT);
  // soil
  pinMode(soilPin, OUTPUT);
  digitalWrite(soilPin,LOW);

//rain sensor + window	
   myservo.attach(9);

}

void loop() {
  int sensorValue1 = analogRead(WsensorPin1);
  int sensorValue2 = analogRead(WsensorPin2);
   myservo.attach(9);
  Serial.println(sensorValue1);

  Serial.print("Analog output: ");


  readRain();
 // Serial.println(readSensor());
  delay(500);
  if (sensorValue1 > 100)  {
   // int outputValue = HIGH;
  //  Serial.println(outputValue);
    digitalWrite(ledPin, HIGH); // water level crossed the upper level
    digitalWrite(ledPin2, LOW);
    digitalWrite(RELAY_PIN, HIGH);  //turn off pump
  }
  if (sensorValue2< 300) {
   // int outputValue =LOW;
    Serial.println("con2");
   // Serial.println(outputValue);
    digitalWrite(ledPin2, HIGH); // water level is below lower level
    digitalWrite(ledPin, LOW); 
    digitalWrite(RELAY_PIN, LOW); //turn on pump
  }
  else  {
   // int outputValue =LOW;
    
   // Serial.println(outputValue);
    digitalWrite(ledPin2, LOW); // in between turn off both lights 
    digitalWrite(ledPin, LOW); 
  }

  //soil part 
  Serial.print("Analog output: ");
  Serial.println(readSensor());


    //rain
    // myservo.attach(9);
    // Serial.println(readRain());
    delay(500);
}


int readSensor() {

  int sensorValue = analogRead(soilSensorPin);  // Read the analog value from sensor
  int outputValue = map(sensorValue, 0, 1023, 255, 0); // map the 10-bit data to 8-bit data
 // analogWrite(soilPin, outputValue); // generate PWM signal
  if(outputValue<50)
  {
      digitalWrite(soilPin,HIGH);
      digitalWrite(RELAY_PIN, LOW); //turn oFF pump

  }
  else
  {
     digitalWrite(soilPin,LOW);
    digitalWrite(RELAY_PIN, HIGH); //turn on pump
  }
  return outputValue;             // Return analog moisture value
}


int readRain() {

  int sensorValue = analogRead(rainPin);  // Read the analog value from sensor

  int outputValue = map(sensorValue, 0, 1023, 255, 0); // map the 10-bit data to 8-bit data
  // Serial.println("\noutside loop");
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);
  Serial.print("Output Value: ");
  Serial.println("Output Value: ");

  analogWrite(ledPin, outputValue); // generate PWM signal
  if(outputValue>0)
  {
    if(open) //if window open, then close
    {
      for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
      myservo.write(pos);
      delay(2);
      
    }
     Serial.print("\nAnalog output inside loop1: ");
    Serial.print(pos);
    open=false;
    }
  }
 
  else
  { 
    if(!open)//if window closed, then open
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