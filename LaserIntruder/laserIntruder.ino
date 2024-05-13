int sensorPin = A0; //ldr sensor pin
int buttonPin = 12; //push button for resetting the alarm
int buzzerPin = 11;

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f,16,2);  //0x27 is the i2c address, while 16 = colu
 
int laserThreshold = 500;
 
void setup() {
  lcd.init();        //Initialize the LCD
  lcd.backlight();   
  pinMode(buttonPin, INPUT_PULLUP); //connect push button to gnd
  Serial.begin(9600);
}
 
boolean alarmState = false;
 
void loop() {

  int sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  if (sensorValue > laserThreshold) {
    alarmState = true;
  }

  if (! alarmState) {
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("All fine");
    delay(10);
    
    
  }else{
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("Intruder Alert!");
    tone(buzzerPin, 440);
    if (! digitalRead(buttonPin)) { //button pushed...so reset alarmState
      alarmState = false;
      noTone(buzzerPin);
    }
    delay(10);
  }

  delay(1000);
}