//https://randomnerdtutorials.com/esp32-mpu-6050-accelerometer-gyroscope-arduino/

// #include <Adafruit_MPU6050.h>
// #include <Adafruit_Sensor.h>
// #include <Wire.h>

// Adafruit_MPU6050 mpu;

// void setup(void) {
//   Serial.begin(115200);
//   while (!Serial)
//     delay(10); // will pause Zero, Leonardo, etc until serial console opens

//   Serial.println("Adafruit MPU6050 test!");

//   // Try to initialize!
//   if (!mpu.begin()) {
//     Serial.println("Failed to find MPU6050 chip");
//     while (1) {
//       delay(10);
//     }
//   }
//   Serial.println("MPU6050 Found!");
//   mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
//   Serial.println("");
//   delay(100);
// }

// void loop() {
//   /* Get new sensor events with the readings */
//   sensors_event_t a, g, temp;
//   mpu.getEvent(&a, &g, &temp);

//   Serial.print(" Z: ");
//   Serial.printf("%2.20f" , g.gyro.z);
//   Serial.println(" rad/s");
//   Serial.println("");
//   delay(2000);
// }