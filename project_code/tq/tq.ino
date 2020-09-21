#include <Adafruit_NeoPixel.h> //릴레이LED (네오픽셀)
Adafruit_NeoPixel stopline = Adafruit_NeoPixel(4, 7, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
   stopline.begin();
  stopline.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  setStopLine();

}

 void setStopLine(){
  
     int k;
   for(k=0; k<4; k++){
    stopline.setPixelColor(k, 92, 209, 229);
  }
  stopline.show();
 }
