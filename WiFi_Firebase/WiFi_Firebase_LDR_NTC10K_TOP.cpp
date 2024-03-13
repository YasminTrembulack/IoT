// /*---Includes---*/
// #include <WiFi.h>
// #include <FirebaseESP32.h>
// #include <cmath>
//#include<Arduino.h>

// /*---Constants---*/
// const char* WIFI_SSID = "belisarius";
// const char* WIFI_PW = "senhaaaa";

// const char* FB_HOST = "https://iiot-dta-default-rtdb.firebaseio.com";
// const char* FB_KEY = "Ag5gJMhAnTWQgDVhegkDRF1uTjJfpMUDkXB8WBEa";

// /*------------*/
// const uint16_t ADC_MAX = 4095; // valor maximo do conversor analogico digital
// const float VREF = 3.3f; // tensao de referencia dos esp32

// /*---NTC10K---*/

// const uint8_t PIN_NTC_00 = 33;
// const uint8_t PIN_NTC_01 = 35;
// const float R1 = 10000.0f;

// /*---LDR---*/
// const uint8_t PIN_INPUT = 32;

// /*---Variables---*/
// FirebaseData fbdo; //informações do banco de dados
// FirebaseAuth fbauth; //metodo de autenticação
// FirebaseConfig fbconfig; 

// /*---Function---*/
// bool connectWiFi(const char* ssid, const char* pw)
// {
//   WiFi.mode(WIFI_STA);
//   WiFi.disconnect();

//   //Conectar a uma rede
//   Serial.print("Conectando");
//   int tentativa = 0;
//   WiFi.begin(ssid, pw);
//   while (WiFi.status() != WL_CONNECTED)
//   {
//     tentativa++;

//     if(tentativa > 300)
//     {
//       return false;
//     }

//     Serial.print(".");
//     delay(200);
    
//   }
//   Serial.print("\nConectado com o IP: ");
//   Serial.println(WiFi.localIP());

//   return true;
// }

// /*---Hardware mapping---*/

// /*---Setup---*/
// void setup()
// {
//   pinMode(PIN_NTC_00, INPUT);
//   pinMode(PIN_INPUT, INPUT);

//   Serial.begin(115200);

//   connectWiFi(WIFI_SSID, WIFI_PW);

//   fbconfig.database_url = FB_HOST;
//   fbconfig.signer.tokens.legacy_token = FB_KEY;

//   fbdo.setBSSLBufferSize(4096, 1024);
//   Firebase.reconnectWiFi(true); // quando tentar acessar o banco e não tiver conectado na net ele conecta

//   Firebase.begin(&fbconfig, &fbauth);
// }

// /*---Loop---*/
// void loop()
// {
//   FirebaseJson json;

//   float a = 12.9611833;
//   float b = -0.0761498101;
//   float c = 3.40889111;
//   float d = -64.5957953;
//   float e = 390.218793;


//   /*---NTC10K_00---*/
//   uint16_t input_valueNTC_00 = analogRead(PIN_NTC_00);
//   float voltageNTC_00 =  static_cast<float>(input_valueNTC_00) * VREF / static_cast<float>(ADC_MAX);

//       //Resistencia a partir da temperatura
//   float resistence_00 = R1 * voltageNTC_00 / (VREF - voltageNTC_00);

//   float temperature_00 = b * pow((log(resistence_00 - a)), 3) + c * pow((log(resistence_00 - a)), 2) + d *(log(resistence_00 - a)) + e;

//   json.set("/subsys_04/temperature/temp_sensor_00", temperature_00);
  
//   Serial.printf("ADC %8i Voltage: %8.2f Resistence: %8.2f Temperature: %8.2f\n", input_valueNTC_00, voltageNTC_00, resistence_00, temperature_00);


//   /*---NTC10K_01---*/
//   uint16_t input_valueNTC_01 = analogRead(PIN_NTC_01);
//   float voltageNTC_01 =  static_cast<float>(input_valueNTC_01) * VREF / static_cast<float>(ADC_MAX);

//       //Resistencia a partir da temperatura
//   float resistence_01 = R1 * voltageNTC_01 / (VREF - voltageNTC_01);

//   float temperature_01 = b * pow((log(resistence_01 - a)), 3) + c * pow((log(resistence_01 - a)), 2) + d *(log(resistence_01 - a)) + e;
  
//   json.set("/subsys_04/temperature/temp_sensor_01", temperature_01);
  
//   Serial.printf("ADC %8i Voltage: %8.2f Resistence: %8.2f Temperature: %8.2f\n", input_valueNTC_01, voltageNTC_01, resistence_01, temperature_01);


//   /*---LDR---*/
//   uint16_t input_valueLDR = analogRead(PIN_INPUT);

//   float voltageLDR =  static_cast<float>(input_valueLDR) * VREF / static_cast<float>(ADC_MAX);

//   Serial.println();
//   Serial.println(voltageLDR);

//   json.set("/subsys_04/luminosity", voltageLDR);


//   /*---Enviar dados para o Firebase---*/
//   bool status = Firebase.updateNode(fbdo, "/iiot-dta", json); 
  
//   if(!status) 
//   {
//     //Caso de algum erro para enviar o o json para o banco de dados, retorna o erro que aconteceu
//     Serial.println(fbdo.errorReason().c_str());
//   }
//   delay(15000);
// }