// /*---Includes---*/
// #include <Arduino.h>
// #include <cmath>

// /*---Variables---*/
 
// /*---Hardware mapping---*/
// const uint8_t PIN_NTC = 26;

// /*---Constants---*/
// const uint32_t ADC_MAX = (1 << 12) - 1;
// const float VREF = 3.3f;
// const float R1 = 10000.0f;
 

// /*---Setup---*/
// void setup()
// {
//   pinMode(PIN_NTC, INPUT);

//   Serial.begin(115200);
// }

// /*---Loop---*/
// void loop()
// {
//   uint16_t input_value = analogRead(PIN_NTC);
//   float voltage =  static_cast<float>(input_value) * VREF / static_cast<float>(ADC_MAX);

//   //Resistencia a partir da temperatura
//   float resistence = R1 * voltage / (VREF - voltage);

//   float a = 12.9611833;
//   float b = -0.0761498101;
//   float c = 3.40889111;
//   float d = -64.5957953;
//   float e = 390.218793;

//   float temperature = b * pow((log(resistence - a)), 3) + c * pow((log(resistence - a)), 2) + d *(log(resistence - a)) + e;

//   Serial.printf("ADC %8i Voltage: %8.2f Resistence: %8.2f Temperature: %8.2f\n", input_value, voltage, resistence, temperature);
//   delay(1000);
// }