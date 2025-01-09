#include <Arduino.h>
#include <U8x8lib.h>
U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

// U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // OLEDs without Reset of the Display

#include "LIS3DHTR.h"
#ifdef SOFTWAREWIRE
    #include <SoftwareWire.h>
    SoftwareWire myWire(3, 2);
    LIS3DHTR<SoftwareWire> LIS;       //Software I2C
    #define WIRE myWire
#else
    #include <Wire.h>
    LIS3DHTR<TwoWire> LIS;           //Hardware I2C
    #define WIRE Wire
#endif

float dist = 0;   // distance
float veloc = 0;  // velocity
float accel = 0;  // acceleration
float timer = 1;  // delay between polls
int numOfVal = 10;// number of values for the moving average
float values[10]; // values of the moving average
int index = 0;
float movAvg = 0; // moving average
int counter = 0;  // counting the accel 0 values
int threshold = 30;

void setup(void) {
  Serial.begin(115200); // Initialize serial
  while (!Serial) {};
  //u8x8.setBusClock(100000);  // If you breakout other modules, please enable this line
  u8x8.begin(); // to start using the screen
  u8x8.setFlipMode(0);  // flip the display orientation

  LIS.begin(WIRE, 0x19); //IIC init
  delay(100);
  LIS.setFullScaleRange(LIS3DHTR_RANGE_2G); // +-2G range
  LIS.setOutputDataRate(LIS3DHTR_DATARATE_400HZ); // 400Hz polling rate for accelerometer
  LIS.setHighSolution(true);            //High solution enable
  LIS.setPowerMode(POWER_MODE_NORMAL);  //Normal power mode
}

void loop(void) {
  u8x8.setFont(u8x8_font_profont29_2x3_f); //u8x8_font_chroma48medium8_r
//  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.setCursor(0, 0); //defining the starting point for the cursor
  
  accel = getCorrectedValue(LIS.getAccelerationY(), 'y');

  // If the raw accelerometer value is small enough, consider it to be 0
  if(accel <= 0.015 && accel >= -0.015)
    accel = 0;

  // Store the accelerometer value in an array for a moving average, and increment the index
  values[index] = accel;
  if(index < numOfVal-1)
    index++;
  else
    index = 0;
  movAvg = 0;
  for(int i = 0; i < numOfVal; i++){
    movAvg += values[i];
  }
  movAvg = movAvg/float(numOfVal);

  // If the moving average is small enough, increment a counter
  if(movAvg <= 0.01 && movAvg >= -0.01)
    counter++;
  else
    counter = 0;

  // If the counter is high enough, it means the board is at rest, so correct the velociy to be 0
  if (counter >= threshold){
    Serial.println("---THRESHOLD---");
    counter = threshold + 1;
    veloc = 0;
  }
  
  // Print the moving average value
  Serial.print("yF: ");
  Serial.println(movAvg*10.0);
  veloc = veloc + movAvg*0.001*9.8*100.0*timer; //(cm/s)
//  u8x8.print("ay: ");
//  u8x8.println(accel);
//  u8x8.print("vy: ");
//  u8x8.println(veloc);
  dist = dist + veloc*timer; //(cm)

  // Print the position on the display
  u8x8.print("y: ");
  u8x8.print(dist);
  delay(timer);
  
}

// Correct the accelerometer values
float getCorrectedValue(float val, char axis){
  float correctedValue = 0;
  if(axis == 'x'){
    correctedValue = (((val - (-1.03)) * 2.0) / 1.97) - 1.0;
  }else if(axis == 'y'){
    correctedValue = (((val - (-1.00)) * 2.0) / 1.96) - 1.0;
  } else if(axis == 'z'){
    correctedValue = (((val - (-0.96)) * 2.0) / 1.93) - 2.0;
  }
  return correctedValue;
}
