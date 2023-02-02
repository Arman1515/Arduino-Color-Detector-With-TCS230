#include <Wire.h>
#include <MD_TCS230.h>
#include <FreqCount.h>


// Pin definitions
#define  S2_OUT  6
#define  S3_OUT  7
#define  OE_OUT  8    // LOW = ENABLED 

int R = 0;
int G = 0;
int B = 0;

MD_TCS230 CS(S2_OUT, S3_OUT, OE_OUT);
  


void setup() {

  Serial.begin(115200);
 
   CS.begin();
   CS.read();
}

void loop() {


  readSensor();

}



void readSensor()
{
  static  bool  waiting = false;
  
  if (!waiting)
  {
    CS.read();
    waiting = true;
  }
  else
  {
    if (CS.available()) 
    {
      colorData  rgb;
      
      CS.getRGB(&rgb);
      Serial.print("RGB [");
      Serial.print(rgb.value[TCS230_RGB_R]);
      Serial.print(",");
      Serial.print(rgb.value[TCS230_RGB_G]);
      Serial.print(",");
      Serial.print(rgb.value[TCS230_RGB_B]);
      Serial.println("]");
      
      R = rgb.value[TCS230_RGB_R];
      G = rgb.value[TCS230_RGB_G];
      B = rgb.value[TCS230_RGB_B];

      waiting = false;
    }
  }
}
