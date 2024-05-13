#include <SoftwareSerial.h>
#include <Servo.h>

String value;

int TxD = 11; //txD pin of bluetooth Module
int RxD = 10; //rxD pin of bluetooth Module

Servo myservo;
int pos;

SoftwareSerial bluetooth(TxD, RxD);

void setup() {

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  myservo.attach(9);
  Serial.begin(9600);       // start serial communication at 9600bps
  bluetooth.begin(9600);    // baud rate of bluetooth module

}


void loop() {

  Serial.println(value);

 if (bluetooth.available()){
  value = bluetooth.readString(); // incoming message from arduino voice app via bluetooth
  
  if (value == "Open the door" || value == "open the door"){

    for (pos = 0; pos <= 120; pos += 1) { // goes from 0 degrees to 120 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15 ms for the servo to reach the position
    }        

  }

  if (value == "Shut the door" || value == "shut the door"){
    for (pos = 120; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15 ms for the servo to reach the position
    }    
  }

  if (value == "all LED turn on" || value == "All LED turn on"){
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);  
  }


  if (value == "all LED turn off" || value == "All LED turn off"){
    digitalWrite(2, LOW); 
    digitalWrite(3, LOW);       
  }


  if (value == "Turn on first LED" || value == "turn on first LED"){ digitalWrite(2, HIGH); }

  if (value == "Turn on second LED" || value == "turn on second LED"){ digitalWrite(3, HIGH); }

  if (value == "Turn off first LED" || value == "turn off first LED"){ digitalWrite(2, LOW); }

  if (value == "Turn off second LED" || value == "turn off second LED"){ digitalWrite(3, LOW); }

 }

}

