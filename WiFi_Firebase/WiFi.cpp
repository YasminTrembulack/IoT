// /*---Includes---*/
// #include <WiFi.h>
// #include <FirebaseESP32.h>

// /*---Function---*/

// bool connectWiFi(const char* ssid, const char* pw)
// {
//   WiFi.mode(WIFI_STA);
//   WiFi.disconnect();

//   //WiFi.begin("ssid","senha");

//   //WiFi.begin(WiFi.SSID(0),"senha"); //pegar o wifi com melhor sinal

//   //Conectar a uma rede
//   Serial.print("Conectando");
//   int tentativa = 0;
//   WiFi.begin(WIFI_SSID, WIFI_PW);
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

// /*---Constants---*/
// const char* WIFI_SSID = "Euzinha";
// const char* WIFI_PW = "senha123";

// const char* FB_HOST = "https://iot-yas-bb21c-default-rtdb.firebaseio.com/";
// const char* FB_KEY = "aMKULGoGY7I6dEQBCBwzPDDOZKDqSs2ZGpLBwnYg";

// /*---Variables---*/
// FirebaseData fbdo; //informações do banco de dados
// FirebaseAuth fbauth; //metodo de autenticação
// FirebaseConfig fbconfig; 

// /*---Setup---*/
// void setup()
// {
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
//   /*-------- VER TODAS AS REDES --------*/

//   // int qtde_wifi = WiFi.scanNetworks();

//   // if(qtde_wifi == 0)
//   // {
//   //   return;
//   // }

//   // for(int i = 0; i < qtde_wifi; i++)
//   // {
//   //   Serial.printf("\nQuantidade de redes disponiveis %i ", qtde_wifi);
//   //   Serial.print("\nIndice: ");
//   //   Serial.print(i+1);
//   //   Serial.print("\nSSID: ");
//   //   Serial.print(WiFi.SSID(i)); //nome
//   //   Serial.print("\nRSSI: ");
//   //   Serial.print(WiFi.RSSI(i)); //intensidade do sinal
//   //   Serial.print("\nAuth: ");
//   //   Serial.print(WiFi.encryptionType(i)); //tipo de autenticação(aberta, senha,...)
//   //   Serial.println(); // Serial.print("\n")
//   // }
//   // Serial.println();
//   // Serial.println();
//   // delay(5000);

//   float value = 3.14;
//   bool status = Firebase.setFloat(fbdo, "/iot-yas/valor", value); // 'valor' é o nome da variavel no banco de dados
  
//   if(!status)
//   {
//     Serial.println(fbdo.errorReason().c_str());
//   }
//   delay(7000);
// }