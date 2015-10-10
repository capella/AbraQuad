#define MPU6050 0x69
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
static void mpu(void) {
  uint8_t buff[14];
  hal.i2c->readRegisters(MPU6050, 0x3B, 14, buff);
  AcX=buff[0]<<8|buff[1];  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=buff[2]<<8|buff[3];  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=buff[4]<<8|buff[5];  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=buff[6]<<8|buff[7];  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=buff[8]<<8|buff[9];  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=buff[10]<<8|buff[11];  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=buff[12]<<8|buff[13];  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  
  cliSerial->printf_P(PSTR("AcX = %d"), AcX);
  cliSerial->printf_P(PSTR(" | AcY = %d"), AcY);
  cliSerial->printf_P(PSTR(" | AcZ = %d"), AcZ);
  cliSerial->printf_P(PSTR(" | Tmp = %d"), Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
  cliSerial->printf_P(PSTR(" | GyX = %d"), GyX);
  cliSerial->printf_P(PSTR(" | GyY = %d"), GyY);
  cliSerial->printf_P(PSTR(" | GyZ = %d\n"), GyZ);
}

static void init_mpu(void) {
  uint8_t value;
  hal.i2c->writeRegister((uint8_t)MPU6050, 0x6B, 0);
  hal.i2c->readRegister((uint8_t)MPU6050, 0x03, &value);
  cliSerial->printf_P(PSTR("PERF: %u\n"), value);
}
