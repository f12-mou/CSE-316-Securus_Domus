
//author : Rizvan Jawad Ruhan
#include <SoftwareSerial.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f,16,2);  //0x3f is the i2c address, while 16 = columns, and 2 = rows. 

#define DHTPIN 10 // digital pin connected to sensor
#define DHTTYPE    DHT11     // DHT 11

DHT dht(DHTPIN, DHTTYPE); 

SoftwareSerial espSerial(5, 6); //rx,tx

int flame_sensor = 2; // digital pin connected to sensor

int flame_detected; // flame detection value

int redLed = 3;
int greenLed = 8;
int buzzer = 9;
int smokeA0 = A0;

// Your threshold value
int smokeSensorThres = 300;
bool alarm = false;

void setup(){

  dht.begin();        //Initialize the DHT11 sensor
  lcd.init();        //Initialize the LCD
  lcd.backlight();    //Activate backlight 

  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  
  pinMode(flame_sensor, INPUT);

  Serial.begin(9600);
  espSerial.begin(9600);

}

void printDHTtoLCD(float t,float h){
  Serial.print("temp : ");
  Serial.println(t);
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print("%");
}

void loop(){

  float t = dht.readTemperature();
  float h = dht.readHumidity();
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
  } 
  
  if(!alarm)
    printDHTtoLCD(t,h);
  
  flame_detected = digitalRead(flame_sensor); //sensor gives 0 when flame is detected and vice-versa
  
  if(flame_detected == 0) 
    flame_detected = 1;
  else
    flame_detected = 0;

  float analogSensor = analogRead(smokeA0);
  int Smoke_detected = 0;

  Serial.print("Pin A0: ");
  Serial.println(analogSensor);

  if( analogSensor > smokeSensorThres )
    Smoke_detected = 1;

  //send different message depending upon current situation
  if (flame_detected == 1 && Smoke_detected == 1  ){

    Serial.println("Flame detected...! take action immediately.");
    Serial.println("Smoke detected...! take action immediately.");
    espSerial.print("fire");  //send "fire" msg to ESP
    
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("fire");
    alarm = true;

    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    tone(buzzer, 1000, 200);

  }else if( flame_detected == 1 && Smoke_detected == 0 ) {

    Serial.println("Flame detected...! take action immediately.");
    Serial.println("No smoke detected.");
    
    espSerial.print("fire");
    
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("fire");
    alarm = true;

    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    tone(buzzer, 1000, 200);

  }else if( flame_detected == 0 && Smoke_detected == 1 ) {

    Serial.println("No flame detected.");
    Serial.println("Smoke detected...! take action immediately.");
    espSerial.print("smoke");
    
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("smoke");

    alarm = true;

    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    tone(buzzer, 1000, 200);

  }
  else if( flame_detected == 0 && Smoke_detected == 0 ){
    Serial.println("No flame detected.");
    Serial.println("No smoke detected.");
    alarm = false;

    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    noTone(buzzer);
  }

  delay(2000);
}