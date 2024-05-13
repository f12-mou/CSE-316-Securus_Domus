/**
 * BasicHTTPClient.ino
 *
 *  Created on: 24.05.2015
 *
 */

#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#define RX 16
#define TX 17 

WiFiMulti wifiMulti;

const char* ssid = "Totoro";  //Wifi Network Name
const char* password = "totoro123"; //wifi Password

const int callMaxTry = 50;  //maximum number of times program will try to connect to network and execute a get request at callMeBot url
String telegramChatID = "@RizvanRuhan21"; //chatID of telegram to whom you want to send the call


void setup() {

    Serial.begin(115200); //Baud rate of ESP is 115200

    Serial.println();
    Serial.println();
    Serial.println();

    Serial2.begin(9600, SERIAL_8N1, RX, TX);  //setting baud rate of incoming transmission from arduino

    while (!Serial2);
    

    for(uint8_t t = 4; t > 0; t--) {
        Serial.printf("[SETUP] WAIT %d...\n", t);
        Serial.flush();
        delay(1000);
    }

    wifiMulti.addAP(ssid, password);  //connect to Wifi

}

// function for sending call
void sendCall(String msg){   
  for(int i = 0;i < callMaxTry;i++ ){
    if((wifiMulti.run() == WL_CONNECTED)) { //if wifi is connected

          HTTPClient http;

          Serial.print("[HTTP] begin...\n");

          // configure traged server and url
          //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
          // http.begin("http://api.callmebot.com/start.php?user=@RizvanRuhan21&text=আমার+আচার+কই&lang=bn-IN-Standard-B&rpt=4"); //HTTP

          String httpLink = "http://api.callmebot.com/start.php?user=" + telegramChatID + "&text=বাচাও+বাচাও+" + msg + "&lang=bn-IN-Standard-B&rpt=4";  // you can set the text here after &text=...
          
          http.begin(httpLink); //HTTP

          Serial.print("[HTTP] GET...\n");  // start connection and send HTTP header
          int httpCode = http.GET();

          Serial.printf("httpReturnCode = %d",httpCode);

          // httpCode will be negative on error
          if(httpCode > 0) {
              // HTTP header has been send and Server response header has been handled
              Serial.printf("[HTTP] GET... code: %d\n", httpCode);

              // file found at server
              if(httpCode == HTTP_CODE_OK) {
                  String payload = http.getString();
                  //Serial.println(payload);
              }
              http.end();
              break;
          } else {
              Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
          }

          http.end();
      } 
      
      delay(5000);
    }      
}

void loop() {
    // wait for WiFi connection

    String msg = "null";
    if (Serial2.available()) {
        Serial.println("Message Received: ");
        msg = Serial2.readString();
        Serial.println(msg);    
        delay(1000);
    }

    
    //here you can set the condition for sending call with different message depending upon the message you received from arduino
    if(msg.equalsIgnoreCase("fire")){
      sendCall("আগুন");
    }
    else if(msg.equalsIgnoreCase("smoke")){
      sendCall("গ্যাস");
    }
        
    
    Serial.println("looping");
    delay(1000);
}
