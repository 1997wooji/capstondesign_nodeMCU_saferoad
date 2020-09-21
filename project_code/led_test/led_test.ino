
int trig = 16; //초음파 1trigger
int echo = 3; //초음파 1echo
int trig2 = 1; //초음파 2 trigger
int echo2 = 0; // 초음파 2 echo

void setup( ) {
  
 Serial.begin (115200) ;   
 pinMode(trig, OUTPUT);
 pinMode(echo, INPUT);
 pinMode(trig2,OUTPUT);
 pinMode(echo2, INPUT);
 
 //display.begin(SSD1306_SWITCHCAPVCC, 0x3C ) ;
 //display.clearDisplay( ) ; 
 //display.setTextColor(WHITE) ; 
 
 }
 
 void loop( ) {
  
  KKC_wave_display();
 
 } 
 
void KKC_wave_display() {
 
  digitalWrite(trig, HIGH);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  digitalWrite(trig2, LOW);
 
  unsigned long distance = pulseIn(echo, HIGH);
  unsigned long distance2=pulseIn(echo2, HIGH);
  
  Serial.print(distance);
  Serial.println("cm 첫번째");
  Serial.print(distance2);
  Serial.println("cm 두번째");
  delay(1000);
  /*
  if (distance < 10) {
    i=(i+1);
    if(i>8) i=8;
  }
  else{
    i=(i-1);
    if(i<-2) i=-2;
  }
  
  display.clearDisplay( ) ; 
  display.fillCircle(90-(10*i), 20, 10, WHITE);   // body
  display.fillCircle(88-(10*i),15,1,BLACK); //eye
  display.drawLine(80-(10*i),20,90-(10*i),20,BLACK); //mouth
  display.display();
  */
}

/*
#define LIGHT_P 14 //보행자 신호등
#define LIGHT_C 12//차 도로 신호등 


void setup() {

//traffic light output pin으로 설정
 pinMode(LIGHT_C,OUTPUT);
 pinMode(LIGHT_P,OUTPUT);

}

void loop() {

  //traffic light 작동 하는지만 test
    digitalWrite(LIGHT_C,HIGH);
    digitalWrite(LIGHT_P,LOW);
    delay(1000);
    digitalWrite(LIGHT_C,LOW);
    digitalWrite(LIGHT_P,HIGH);
    delay(1000);
}
*/
