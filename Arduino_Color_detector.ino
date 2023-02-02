/*
 * Set Arduino Serial Monitor Baud Rate to 57600.
 * 
 * IF-ELSE RANGE:
 * if(((R >= MINIMUM RED RANGE VALUE) && (R <= MAXIMUM RED RANGE VALUE))&&((G >= MINIMUM GREEN RANGE VALUE) && (G <= MAXIMUM GREEN RANGE VALUE))
 *      &&((B >= MINIMUM BLUE RANGE VALUE) && (R <= MAXIMUM BLUE RANGE VALUE)))
 *      {
 *      Display/Serial.print
 *      }
 * You will get it by using arduino color detector calibration code.
 */
#include <LiquidCrystal_I2C.h>
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
LiquidCrystal_I2C lcd(0x27,16,2);


void setup() {
  
  Serial.begin(115200);
  Serial.println(" ");
  Serial.println("#########################################################");
  Serial.println("Arduino Color Detector with TCS-230 sensor              #");
  Serial.println("Note:                                                   #");
  Serial.println(" IF ""No Color Detected "" message pop up               #");
  Serial.println(" then move your sensor  or                              #");
  Serial.println("Please Modify the range of if-else condition RGB range  #");
  Serial.println("to detect your desired color.                           #");
  Serial.println("#########################################################");
  Serial.println(" ");
  
  lcd.init();         // Initialize the lcd
  //lcd.backlight();    // Initialize the backlight, Use the potentiometer is I2C module to change the contrast and brightness
  lcd.setCursor(0,0);
  lcd.print("Arduino Color ");
  lcd.setCursor(0,1);
  lcd.print("Detector");
    
  delay(1000);
  CS.begin();        // Color Sensor Begin
  CS.read();         // Color Sensor start reading value
  lcd.clear();       //Clearing the lcd
}



void loop() {

  lcd.setCursor(0,0);//lcd.setCursor(coloumn Number,row Number)
  lcd.print("Color Detected: ");
  lcd.setCursor(0,1);
  readSensor();
    // For RED Color
      if ( (( R >= 30) && ( R <= 42)) && (( G >= 0) && ( G <= 2)) && (( B >= 13) && ( B <= 20)) )
      {
      //  Serial.println("RED");
        lcd.print("RED");
      }
    
    // For Green Color
    else  if ( (( R >= 0) && ( R <= 5)) && (( G >= 4) && ( G <= 15)) && (( B >= 7) && ( B <= 15)) )
      {
    //   Serial.println("GREEN");
        lcd.print("GREEN");
    
      }
    // For BLUE Color
    else  if ( (( R >= 0) && ( R <= 2)) && (( G >= 2) && ( G <= 7)) && (( B >= 32) && ( B <= 45)) )
      {
     //   Serial.println("BLUE");
        lcd.print("BLUE");
    
      }
    // For YELLOW Color
    else  if ( (( R >= 40) && ( R <= 55)) && (( G >= 25) && ( G <= 35)) && (( B >= 14) && ( B <= 25)) )
      {
        //Serial.println("YELLOW");
        lcd.print("YELLOW");
    
      }
    // For PURPLE Color
    else  if ( (( R >= 7) && ( R <= 14)) && (( G >= 0) && ( G <= 1)) && (( B >= 15) && ( B <= 25)) )
      {
       // Serial.println("PURPLE");
        lcd.print("PURPLE");
      }
    // For LIGHT BLUE Color
    else  if ( (( R >= 0) && ( R <= 2)) && (( G >= 5) && ( G <= 12)) && (( B >= 40) && ( B <= 50)) )
      {
       // Serial.println("LIGHT BLUE");
         lcd.print("LIGHT BLUE");
    
      }
    // For NAVY BLUE Color
    else  if ( (( R >= 0) && ( R <= 2)) && (( G >= 0) && ( G <= 2)) && (( B >= 23) && ( B <= 30)) )
      {
      //Serial.println("NAVY BLUE");
        lcd.print("NAVY BLUE");
    
      }
    // For PINK Color
    else  if ( (( R >= 30) && ( R <= 40)) && (( G >= 0) && ( G <= 2)) && (( B >= 22) && ( B <= 32)) )
      {
       // Serial.println("PINK");
        lcd.print("PINK");
      }
    // For Black Color
    else   if ( (( R >= 0) && ( R <= 2)) && (( G >= 0) && ( G <= 2)) && (( B >= 0) && ( B <= 10)) )
      {
        //clear display
      //Serial.println("BLACK");
      lcd.print("BLACK");
    
      }
      // For White Color
    else   if ( (( R >= 48) && ( R <= 58)) && (( G >= 45) && ( G <= 55)) && (( B >= 70) && ( B <= 90)) )
      {
        //clear display
        //Serial.println("WHITE");
        lcd.print("WHITE");
      } 
      else
      {
      
     // Serial.println("No Color Detected");
      lcd.print("No Color");
      }
 delay(100);
 lcd.clear();
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
/* Comment Or Uncomment all this lines to write the value in serial monitor 
      Serial.print("RGB [");
      Serial.print(rgb.value[TCS230_RGB_R]);
      Serial.print(",");
      Serial.print(rgb.value[TCS230_RGB_G]);
      Serial.print(",");
      Serial.print(rgb.value[TCS230_RGB_B]);
      Serial.println("]");
*/
      
      R = rgb.value[TCS230_RGB_R];
      G = rgb.value[TCS230_RGB_G];
      B = rgb.value[TCS230_RGB_B];

      waiting = false;
    }
  }
}
