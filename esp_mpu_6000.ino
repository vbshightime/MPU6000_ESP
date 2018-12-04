#include <Wire.h>
#define Addr 0x68

void setup() {
 
Wire.begin(2,14);
Serial.begin(115200);

Serial.println("Transmision started to address 0x68");

//Gyro configuration 2000dps
writeTo(Addr,0x1B,0x18);
//Accel Configuration
//8g  resolution
writeTo(Addr,0x1C,0x10);
//Power management
//Temp sensor disable
//device reset
writeTo(Addr,0x6B,0x89);
delay(300);
}

void loop() {
  

  writeTo(Addr,0x6B,0x29);
  writeTo(Addr,0x6C,0xC0);
  
  unsigned int accl_data[6];
  unsigned int gyro_data[6];
  
  Wire .beginTransmission(Addr);
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(Addr,6);

  if(Wire.available() == 6){
      accl_data[0] = Wire.read();
      accl_data[1] = Wire.read();
      accl_data[2] = Wire.read();
      accl_data[3] = Wire.read();
      accl_data[4] = Wire.read();
      accl_data[5] = Wire.read();
    }

  int accl1 = accl_data[0] * 256 + accl_data[1];
  int accl2 = accl_data[2] * 256 + accl_data[3];
  int accl3 = accl_data[4] * 256 + accl_data[5];



  Wire .beginTransmission(Addr);
  Wire.write(0x43);
  Wire.endTransmission();
  Wire.requestFrom(Addr,6);

  if(Wire.available() == 6){
      gyro_data[0] = Wire.read();
      gyro_data[1] = Wire.read();
      gyro_data[2] = Wire.read();
      gyro_data[3] = Wire.read();
      gyro_data[4] = Wire.read();
      gyro_data[5] = Wire.read();
    }

  int gyro1 = gyro_data[0] * 256 + gyro_data[1];
  int gyro2 = gyro_data[2] * 256 + gyro_data[3];
  int gyro3 = gyro_data[4] * 256 + gyro_data[5];

  float gyroX = gyro1/32.8;
  float gyroY = gyro2/32.8;
  float gyroZ = gyro3/32.8;
  
  float acclX = accl1/4096;
  float acclY = accl2/4096;
  float acclZ = accl3/4096;
  
  Serial.print("Acceleration in X-Axis : ");
  Serial.println(acclX);
  Serial.print("Acceleration in Y-Axis : ");
  Serial.println(acclY);
  Serial.print("Acceleration in Z-Axis : ");
  Serial.println(acclZ);
 
  Serial.print("X-Axis of Rotation : ");
  Serial.println(gyroX);
  Serial.print("Y-Axis of Rotation : ");
  Serial.println(gyroY);
  Serial.print("Z-Axis of Rotation : ");
  Serial.println(gyroZ);

  delay(100);
}


void writeTo(byte addr, byte reg_addr, byte val){
   Wire.beginTransmission(addr);
   Wire.write(reg_addr);
   Wire.write(val);
   Wire.endTransmission();
  }
