// /*---Includes---*/
// #include <WiFi.h>
// #include <FirebaseESP32.h>
// #include <vector>

// /*---Constants---*/
// const char* WIFI_SSID = "belisarius";
// const char* WIFI_PW = "senhaaaa";

// const char* FB_HOST = "https://iiot-dta-default-rtdb.firebaseio.com";
// const char* FB_KEY = "Ag5gJMhAnTWQgDVhegkDRF1uTjJfpMUDkXB8WBEa";

// /*------------*/
// const uint16_t ADC_MAX = 4095; // valor maximo do conversor analogico digital
// const float VREF = 3.3f; // tensao de referencia dos esp32

// /*---NTC10K---*/
// template<class T>
// using Vector = std::vector<T>;
// const uint8_t PIN_NTC = 33;
// const float R1 = 10000.0f;

// Vector<float> NTC_10K_temp = { -55, -50, -45, -40, -35,
//                                -30, -25, -20, -15, -10,
//                                -5, 0, 5, 10, 15,
//                                20, 25, 30, 35, 40,
//                                45, 50, 55, 60, 65,
//                                70, 75, 80, 85, 90,
//                                95, 100, 105, 110, 115,
//                                120, 125 };
 
// Vector<float> NTC_10K_res = { 1214600, 844390, 592430, 419380, 299480,
//                               215670, 156410, 114660, 84510, 62927,
//                               47077, 35563, 27119, 20860, 16204,
//                               12683, 10000, 7942, 6327, 5074,
//                               4103, 3336, 2724, 2237, 1846,
//                               1530, 1275, 1068, 899.3, 760.7,
//                               645.2, 549.4, 470.0, 403.6, 347.4,
//                               300.1, 260.1 };


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
//   pinMode(PIN_NTC, INPUT);
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

//   /*---NTC10K---*/
//   uint16_t input_valueNTC = analogRead(PIN_NTC);
//   float voltageNTC =  static_cast<float>(input_valueNTC) * VREF / static_cast<float>(ADC_MAX);

//   //Resistencia a partir da temperatura
//   float resistence = R1 * voltageNTC / (VREF - voltageNTC);

//   int index;
//   for(int i = 0; i < NTC_10K_temp.size(); i++)
//   {
//     if (resistence > NTC_10K_res[i])
//     {
//       index = i;
//       break;
//     }
//   }
//   float temperature = NTC_10K_temp[index] + (resistence - NTC_10K_res[index]) * (NTC_10K_temp[index] - NTC_10K_temp[index - 1]) / (NTC_10K_res[index] - NTC_10K_res[index - 1]);
//   json.set("/subsys_04/temperature/temp_sensor_00", temperature);
  
//   Serial.printf("ADC %8i Voltage: %8.2f Resistence: %8.2f Temperature: %8.2f\n", input_valueNTC, voltageNTC, resistence, temperature);

//   /*---LDR---*/
//   bool luminosity;
//   uint16_t input_valueLDR = analogRead(PIN_INPUT);

//   float voltageLDR =  static_cast<float>(input_valueLDR) * VREF / static_cast<float>(ADC_MAX);
  
//   Serial.println();
//   Serial.println(voltageLDR);

//   if (voltageLDR > 2.5)
//   {
//     luminosity = false;
//   }
//   else
//   {
//     luminosity = true;
//   }
//   json.set("/subsys_04/luminosity", luminosity);

//   /*---Enviar dados para o Firebase---*/


//   bool status = Firebase.updateNode(fbdo, "/iiot-dta-default-rtdb", json); 
  
//   if(!status)
//   {
//     Serial.println(fbdo.errorReason().c_str());
//   }
//   delay(15000);
// }