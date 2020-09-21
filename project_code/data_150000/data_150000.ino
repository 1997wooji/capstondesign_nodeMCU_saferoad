//보내는쪽 코드

#include <DHT.h>  //온습도 센서
#include <ESP8266WiFi.h> //distance 24~26=사람 없음, 그 이하=사람 있음 멈춰!

#include <Wire.h> //OLED
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Adafruit_NeoPixel.h> //릴레이LED (네오픽셀)

 String apiKey = "P4GTBD9A0LD15HK0";   // Write API key from ThingSpeak  
 //const char *ssid =  "capstone";       // wifi ssid and wpa2 key 
 //const char *pass =  "87654321";
 const char *ssid =  "AndroidHotspot3615";       // wifi ssid and wpa2 key 
 const char *pass =  "12345678";
 const char* server = "api.thingspeak.com"; 

 #define DHTPIN 2  //온습도센서 D4
 
 #define LIGHT_P 14 //보행자 신호등
 #define LIGHT_C 12//차 도로 신호등 
 
 #define TRIG 16 //초음파센서 trigger pin D0
 #define ECHO 0 //초음파센서 echo pin D3

 #define SCREEN_WIDTH 128 // OLED display width, in pixels
 #define SCREEN_HEIGHT 64 // OLED display height, in pixels

 #define NEOPIN 15 //relay neo pixel pin
 #define NUM_LEDS 10
 
 #define OLED_RESET LED_BUILTIN //4
 // SCL GPIO4, SDA GPIO5
 
 DHT dht(DHTPIN, DHT11); 
 WiFiClient client;      // WiFiClient Declaration

 Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); 
 Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, NEOPIN, NEO_GRB + NEO_KHZ800);

 void setup()  
 { 

  //초음파
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  
  //TRAFFIC LIGHT
  pinMode(LIGHT_C,OUTPUT);
  pinMode(LIGHT_P,OUTPUT);
 
  Serial.begin(115200); 

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C ) ;
  display.clearDisplay( ) ; 
  display.setTextColor(WHITE) ; 
  
  dht.begin();

  strip.begin();
  strip.show();

  /*WiFi 연결 코드*/
  Serial.println("Connecting to "); 
  Serial.println(ssid); 
  WiFi.begin(ssid, pass);    // WiFi Start 
  while (WiFi.status() != WL_CONNECTED )  { 
    delay(500); 
    Serial.print("."); 
   } 
  Serial.println(""); 
  Serial.println("WiFi connected"); 
 } 
   
 void loop()  { 

    /*온습도 읽어오기*/
  float h = dht.readHumidity(); 
  float t = dht.readTemperature(); 
  Serial.print("온도 : ");
  Serial.print(t);
  Serial.print(", 습도 : ");
  Serial.println(h);
  
  oled_display(h,t); 
  
  long distance = distance_cal();
  int x=0; //자동차 STOP 보행자 GREEN
  data_to_cloud(x, distance);
  
  digitalWrite(LIGHT_C,HIGH); //자동차 RED LIGHT ON
  digitalWrite(LIGHT_P,LOW);
  setStripGreen(10); //NEOSTRIP GREEN LIGHT ON
  print_x_distance(distance, x);
  delay(3000);

  setStripGreen(8);
  delay(3000);
  setStripGreen(6);
  delay(3000);
  setStripGreen(4);
  delay(3000);
  setStripGreen(2);
  delay(3000);
  
  x=1; //자동차 GO 보행자 RED
  distance = distance_cal();
  data_to_cloud(x, distance);
  digitalWrite(LIGHT_C,LOW); //자동차 GREEN LIGHT ON
  digitalWrite(LIGHT_P,HIGH);
  setStripRed(); //보행자 RED RIGHT ON
  print_x_distance(distance, x);
  delay(15000);

 }  

 void oled_display(int h, int t){

     display.clearDisplay( ) ; 
     display.setTextSize(2) ;
     
     display.setCursor(2,2) ;
     display.print("Temp") ;
     display.setCursor(60,2) ;
     display.print(t); 
     
     display.setCursor(2,30) ;
     display.print("Hum") ;
     display.setCursor(60,30) ;
     display.print(h); 
     
     display.display( ) ;
     
   return;
 }

 long distance_cal() {

  long duration, distance;  
  digitalWrite(TRIG, LOW);        
  delayMicroseconds(2);        
  digitalWrite(TRIG, HIGH);        
  delayMicroseconds(10);        
  digitalWrite(TRIG, LOW);      
  duration = pulseIn(ECHO, HIGH);   // echoPin핀에서 펄스값을 받아옵니다.
  distance = (duration/2)/29.1;

  return distance;

 }

 void data_to_cloud(int x, int distance){

    if (client.connect(server,80))  {   // connect to server (api.thingspeak.com) port 80 
        String postStr = apiKey;   // apiKey += field1 += field2 ....  
        postStr +="&field1=";      // &field1 --> Address of field1
        postStr += String(x);      // traffic 정보 
        postStr +="&field2=";
        postStr += String(distance); //distance 정보
        postStr += "\r\n\r\n"; 

      // Sending Data to server 
       client.print("POST /update HTTP/1.1\n");      
       client.print("Host: api.thingspeak.com\n"); 
       client.print("Connection: close\n"); 
       client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n"); 
       client.print("Content-Type: application/x-www-form-urlencoded\n"); 
       client.print("Content-Length: "); 
       client.print(postStr.length()); 
       client.print("\n\n"); 
       client.print(postStr); 
  
       Serial.println("go to cloud");        
      } 

      client.stop(); 
      Serial.println("Waiting..."); 
        // thingspeak needs minimum 15 sec delay between updates 
        
    return;
 }

 void print_x_distance(int distance, int x){
  
  Serial.print("x : ");
  Serial.print(x);
  Serial.print(", distance : ");
  Serial.println(distance);
 
  
  return;
 }

 /*
 strip.setPixelColor(0, 255, 0, 0); 는
 첫번째 파라메터는 LED 의 번호이고, 
 2,3,4번째 파라메터는 RGB 값이다. 0~255까지 지정할수 있다.
 setPixelColor로 설정한 값은. strip.show(); 를 실행할때, 네오픽셀에 실제로 나타난다.
 */

 void setStripRed() {
    int i;
    for(i=0; i<NEOPIN; i++){
     strip.setPixelColor(i, 255, 0, 0);
    }
    
    strip.show();

  return;
  
 }

 void setStripGreen(int num){

    int i;
    
    for(i=0; i<num; i++){
      strip.setPixelColor(i, 92, 209, 229); //GREEN LIGHT
    }
    
    for(i=num; i<NEOPIN; i++){
      strip.setPixelColor(i, 0, 0, 0); //OFF
    }
    
    strip.show();
    
    return;
    
 }

 
