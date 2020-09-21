
#define LIGHT_C 10//차 도로 신호등 

void setup() {
 pinMode(LIGHT_C,OUTPUT);
 Serial.begin(115200); 

}

void loop() {
  // put your main code here, to run repeatedly:
   digitalWrite(LIGHT_C, LOW);
   delay(1000);
   digitalWrite(LIGHT_C, HIGH);
   delay(1000);

}
