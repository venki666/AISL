/* library MPU6050 */
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>

/* library blynk */
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

/* config MPU6050 */
Adafruit_MPU6050 mpu;

/* config blink */

#define gyroValueX V0
#define gyroValueY V1
#define gyroValueZ V2
#define accellValueX V3
#define accellValueY V4
#define accellValueZ V5
#define virtualLCD1 V6
#define virtualLCD2 V7
WidgetLCD lcd1(virtualLCD1);
WidgetLCD lcd2(virtualLCD2);

// credential blynk send value for email when created project in mobile app
char auth[] = "";

/* config wifi */
char ssid[] = "";
char pass[] = "";

void setup(void)
{
    Serial.begin(115200);

    Blynk.begin(auth, ssid, pass); // Give us access!

    while (Blynk.connect() == false)
    { // Be patient.
        // Wait for Blynk to come online
    }
    // Notify immediately on startup
    Blynk.notify("Device Started");

    while (!Serial)
        delay(10); // will pause Zero, Leonardo, etc until serial console opens

    Serial.println("Adafruit MPU6050 test!");

    // Try to initialize!
    if (!mpu.begin())
    {
        Serial.println("Failed to find MPU6050 chip");
        while (1)
        {
            delay(10);
        }
    }
    Blynk.notify("MPU6050 Found!");
    Serial.println("MPU6050 Found!");

    // change param (enum values) functions if necessary
    setConfigAccelScale(MPU6050_RANGE_2_G, true);
    setConfigGyroScale(MPU6050_RANGE_250_DEG, true);
    setConfigFilterBandwidth(MPU6050_BAND_260_HZ, true);

    // Print a splash screen:
    lcd1.clear();
    lcd1.print(0, 0, " GY521/MPU SET");
    lcd1.print(0, 1, "Band:");
    lcd1.print(6, 1, getConfigFilterBandwidth());
    lcd2.clear();
    lcd2.print(0, 0, "Gyro:");
    lcd2.print(7, 0, getConfigGyroScale());
    lcd2.print(0, 1, "Accell:");
    lcd2.print(8, 1, getConfigAccelScale());
    delay(100);
}

void loop()
{
    Blynk.run();

    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    Serial.print(g.gyro.x, 6);
    Serial.print(",");
    Serial.print(g.gyro.y, 6);
    Serial.print(",");
    Serial.print(g.gyro.z, 6);
    Serial.print(",");
    Serial.print(a.acceleration.x, 6);
    Serial.print(",");
    Serial.print(a.acceleration.y, 6);
    Serial.print(",");
    Serial.print(a.acceleration.z, 6);
    Serial.println("");

    // Write the values to Blynk:
    Blynk.virtualWrite(gyroValueX, a.gyro.x);
    Blynk.virtualWrite(gyroValueY, a.gyro.y);
    Blynk.virtualWrite(gyroValueZ, a.gyro.z);
    Blynk.virtualWrite(accellValueX, g.acceleration.x);
    Blynk.virtualWrite(accellValueY, g.acceleration.y);
    Blynk.virtualWrite(accellValueZ, g.acceleration.z);
}

void setConfigAccelScale(mpu6050_accel_range_t range_accel, bool print)
{
    mpu.setAccelerometerRange(range_accel);
    if (print)
        getConfigAccelScale();
}

void setConfigGyroScale(mpu6050_gyro_range_t range_gyro, bool print)
{
    mpu.setGyroRange(range_gyro);
    if (print)
        getConfigGyroScale();
}

void setConfigFilterBandwidth(mpu6050_bandwidth_t range_bandwidth, bool print)
{
    mpu.setFilterBandwidth(range_bandwidth);

    if (print)
        getConfigFilterBandwidth();
}

String getConfigAccelScale()
{
    Serial.print("Accelerometer range set to: ");
    switch (mpu.getAccelerometerRange())
    {
    case MPU6050_RANGE_2_G:
        Serial.println("2G");
        return ("2G");
    case MPU6050_RANGE_4_G:
        Serial.println("4G");
        return ("4G");
    case MPU6050_RANGE_8_G:
        Serial.println("8G");
        return ("8G");
    case MPU6050_RANGE_16_G:
        Serial.println("16G");
        return ("16G");
    }
    return "";
}

String getConfigGyroScale()
{
    Serial.print("Gyro range set to: ");
    switch (mpu.getGyroRange())
    {
    case MPU6050_RANGE_250_DEG:
        Serial.println("250 deg/s");
        return ("250 deg/s");
    case MPU6050_RANGE_500_DEG:
        Serial.println("500 deg/s");
        return ("500 deg/s");
    case MPU6050_RANGE_1000_DEG:
        Serial.println("1000 deg/s");
        return ("1000 deg/s");
    case MPU6050_RANGE_2000_DEG:
        Serial.println("2000 deg/s");
        return ("2000 deg/s");
    }
    return "";
}

String getConfigFilterBandwidth()
{
    Serial.print("Filter bandwidth set to: ");
    switch (mpu.getFilterBandwidth())
    {
    case MPU6050_BAND_260_HZ:
        Serial.println("260 Hz");
        return ("260 Hz");
    case MPU6050_BAND_184_HZ:
        Serial.println("184 Hz");
        return ("184 Hz");
    case MPU6050_BAND_94_HZ:
        Serial.println("94 Hz");
        return ("94 Hz");
    case MPU6050_BAND_44_HZ:
        Serial.println("44 Hz");
        return ("44 Hz");
    case MPU6050_BAND_21_HZ:
        Serial.println("21 Hz");
        return ("21 Hz");
    case MPU6050_BAND_10_HZ:
        Serial.println("10 Hz");
        return ("10 Hz");
    case MPU6050_BAND_5_HZ:
        Serial.println("5 Hz");
        return ("5 Hz");
    }
    return "";
}