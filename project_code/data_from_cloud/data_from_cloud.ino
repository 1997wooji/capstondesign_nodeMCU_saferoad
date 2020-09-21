
//받는쪽 코드 ~자동차~

#include "ThingSpeak.h"  
#include <ESP8266WiFi.h>

char ssid[] = "kcw" ; // your network SSID (name) 
char pass[] = "87654321" ; // your network password

WiFiClient client;
unsigned long myChannelNumber = 935565;   // CH ID
const char *myreadAPIKey = "P7PBXKK0V3TNXHHY" ; //read API Key

void setup() {
  WiFi.begin (ssid, pass) ;
  Serial.begin(115200);      // Initialize serial
  ThingSpeak.begin(client);  // Initialize ThingSpeak
 }

void loop() {
  
  int x = ThingSpeak.readIntField(myChannelNumber, 1) ; 
  int y = ThingSpeak.readIntField(myChannelNumber, 2) ;
  
  Serial.print("신호등 : ");
  Serial.print(x);
  Serial.print(", 초음파 : ");
  Serial.println(y);
  delay (1000) ; 
 }
