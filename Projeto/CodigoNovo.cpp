// #include <Adafruit_MPU6050.h>
// #include <Adafruit_Sensor.h>
// #include <Wire.h>
// #include <Arduino.h>
// #include <time.h>

// Adafruit_MPU6050 mpu;

// float times = 0;

// void setup(void) {
//   Serial.begin(115200);
//   mpu.begin();
//   // while (!Serial)
//   //   delay(10); // will pause Zero, Leonardo, etc until serial console opens

//   // Serial.println("Adafruit MPU6050 test!");

//   // // Try to initialize!
//   // if (!mpu.begin()) {
//   //   Serial.println("Failed to find MPU6050 chip");
//   //   while (1) {
//   //     delay(10);
//   //   }
//   // }
//   // Serial.println("MPU6050 Found!");
//   mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
//   // Serial.println("");
//   // delay(100);
// }

// void loop()
// {
//   times = millis();
//   /* Get new sensor events with the readings */
//   sensors_event_t a, g, temp;
//   mpu.getEvent(&a, &g, &temp);

//   float add_rad = 0;

//   /*Used to calibrate the accelerometer*/
//   for (int i = 0; i < 10000; i++) 
//   {
//     add_rad += g.gyro.z; 
//   }
//   /*Mean of the acceleration of rotation*/
//   float mean_rad = add_rad/10000;
 
//   /*Angle of rotation in radians*/
//   float rad = mean_rad * ((millis() - times)/1000);

//   Serial.print(", Z: ");
//   Serial.printf("%2.20f", rad);
//   Serial.println(" rad");
//   delay(500);
// }