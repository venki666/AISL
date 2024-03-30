// Basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#define rad_to_deg 57.2957795
Adafruit_MPU6050 mpu;
float o[3]={0,0,0};
float pitch=0,roll=0;

void cali(){
  int c =0;
  sensors_event_t a, g, temp;
  while (c<1000){
    mpu.getEvent(&a, &g, &temp);
    o[0] = g.gyro.x;
    o[1] = g.gyro.y;
    o[2] = g.gyro.z;
    c++;
    delay(5);
  }
  o[0] = o[0] / 1000;  
  o[1] = o[1] / 1000;
  o[2] = o[2] / 1000;
}

void ComplementaryFilter(float accData[3], float gyrData[3],float dt)
{
    float pitchAcc, rollAcc;               
 
    // Integrate the gyroscope data -> int(angularSpeed) = angle
    pitch += ((float)gyrData[0]) * rad_to_deg * dt; // Angle around the X-axis
    roll -= ((float)gyrData[1]) * rad_to_deg * dt;    // Angle around the Y-axis
 
    // Compensate for drift with accelerometer data if 
    // Sensitivity = -2 to 2 G at 16Bit -> 2G  && 0.5G 
    int forceMagnitudeApprox = abs(accData[0]) + abs(accData[1]) + abs(accData[2]);
    if (forceMagnitudeApprox > SENSORS_GRAVITY_STANDARD *0.5 && forceMagnitudeApprox < 2*SENSORS_GRAVITY_STANDARD)
    {
  // Turning around the X axis results in a vector on the Y-axis
        pitchAcc = atan2f((float)accData[1] / SENSORS_GRAVITY_STANDARD * 16384, (float)accData[2] / SENSORS_GRAVITY_STANDARD * 16384) * 180 / M_PI;
        pitch = pitch * 0.96 + pitchAcc * 0.04;
 
  // Turning around the Y axis results in a vector on the X-axis
        rollAcc = atan2f((float)accData[0] / SENSORS_GRAVITY_STANDARD * 16384, (float)accData[2] / SENSORS_GRAVITY_STANDARD * 16384) * 180 / M_PI;
        roll = roll * 0.98 + rollAcc * 0.02;
    }
}

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_260_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }
  float rate = mpu.getSampleRateDivisor();
  Serial.println(rate);
  cali();
  Serial.println("");
  delay(100);
}

void loop() {

  float acc[3],gyr[3];
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  acc[0]=a.acceleration.x;
  acc[1]=a.acceleration.y;
  acc[2]=a.acceleration.z;

  gyr[0]=g.gyro.x-o[0];
  gyr[1]=g.gyro.y-o[1];
  gyr[2]=g.gyro.z-o[2];

  ComplementaryFilter(acc, gyr, 0.005);

  //Serial.print("roll ");
  Serial.print(roll);
  Serial.print(", ");
  Serial.print(pitch);
  Serial.println("");
  delay(5);
}
