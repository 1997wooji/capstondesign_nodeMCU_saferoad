
//받는쪽 코드 ~자동차~

#include "ThingSpeak.h"  
#include <ESP8266WiFi.h>

char ssid[] = "capstone" ; // your network SSID (name) 
char pass[] = "87654321" ; // your network password

WiFiClient client;
unsigned long myChannelNumber = 822783;   // CH ID
const char *myreadAPIKey = "P7PBXKK0V3TNXHHY" ; //read API Key

void setup() {
  WiFi.begin (ssid, pass) ;
  Serial.begin(115200);      // Initialize serial
  ThingSpeak.begin(client);  // Initialize ThingSpeak
 }

void loop() {
  
  int x = ThingSpeak.readIntField(myChannelNumber, 1) ; 
  Serial.print("신호등 : ");
  if(x==0) { Serial.println("자동차, 건너시오") ;}
  else { Serial.println("자동차, 건너지 마시오") ;}
  delay (10) ; 
  
  int y = ThingSpeak.readIntField(myChannelNumber, 2) ;
  Serial.print("초음파 센서 1 : ");
  Serial.print(y);
  Serial.print("cm");
  delay (1000) ; 
 }
