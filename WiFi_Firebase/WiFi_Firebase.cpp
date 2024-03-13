// /*---Includes---*/
// #include <WiFi.h>
// #include <FirebaseESP32.h>

// /*---Constants---*/
// const char* WIFI_SSID = "Euzinha";
// const char* WIFI_PW = "senha123";

// const char* FB_HOST = "https://teste-6ae3f-default-rtdb.firebaseio.com/";
// const char* FB_KEY = "EVp4xtJQ2ZRmfWrkkk4BsLO4tBJpG4kSqH24JIGu";

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
//   WiFi.begin(ssid, pw);

//   Serial.print("Conectando");
//   int tentativa = 0;

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
//   float value = 3.14;
//   FirebaseJson json;

//   json.set("/maquina1/variavel", value);

//   bool status = Firebase.updateNode(fbdo, "teste-6ae3f", json); 
  
//   if(!status)
//   {
//     Serial.println(fbdo.errorReason().c_str());
//   }
//   delay(7000);

//   // float value = 3.14;
//   // bool status = Firebase.setFloat(fbdo, "/iot-yas-bb21c/variavel", value); // 'valor' é o nome da variavel no banco de dados
  
//   // if(!status)
//   // {
//   //   Serial.println(fbdo.errorReason().c_str());
//   // }
//   // delay(7000);
// }