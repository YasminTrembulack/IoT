// /*---Includes---*/
// #include <Arduino.h>
// #include <cmath>
// #include <vector>
 
// /*---Variables---*/


// //T = tipo genérico
// template<class T>
// using Vector = std::vector<T>;
 
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

//   float a = -19.49123972;
//   float b = 204.88328885;
//   float c = 208.78577114;

//   float temperature = a * log(resistence - b) +  c;

//   Serial.printf("ADC %8i Voltage: %8.2f Resistence: %8.2f Temperature: %8.2f\n", input_value, voltage, resistence, temperature);
//   delay(1000);

// }