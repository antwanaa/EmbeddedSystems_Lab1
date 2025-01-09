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

void setup() {
  Serial.begin(115200); // Initializing serial communication
  while (!Serial) {};
  LIS.begin(WIRE, 0x19); //IIC init
  delay(100);
  LIS.setFullScaleRange(LIS3DHTR_RANGE_2G); // 2G Range
  LIS.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);  // 50Hz polling rate
  LIS.setHighSolution(true); //High solution enable
  LIS.setPowerMode(POWER_MODE_NORMAL);  // normal power mode
}
void loop() {
  float x, y, z;
  //3 axis
  LIS.getAcceleration(&x, &y, &z);  // read from the accelerometer
  x = getCorrectedValue(x, 'x');    // get the corrected value and print it
  Serial.print(x);
  Serial.print(", ");
  y = getCorrectedValue(y, 'y');
  Serial.print(y);
  Serial.print(", ");
  z = getCorrectedValue(z, 'z');
  Serial.println(z);

  delay(50);  // delay of 50ms
}

// function to compute a corrected value for the accelerometer
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
