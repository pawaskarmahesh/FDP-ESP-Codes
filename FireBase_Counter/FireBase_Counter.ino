#include <WiFi.h>
#include <Firebase_ESP_Client.h>

#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

#define WIFI_SSID "Madhura"
#define WIFI_PASSWORD "87654321"
#define API_KEY "AIzaSyArjly-5lmYfLFCyOiL0M98KsGqmCpwDmo"

#define DATABASE_URL "https://dec15-11284-default-rtdb.firebaseio.com/" 
#define FIREBASE_PROJECT_ID "dec15-11284"


FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
unsigned long sendDataPrevMillis = 0;
bool taskCompleted = false;
int i;
WiFiClient client;

void setup()
{ i = 0;
  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if(Firebase.signUp(&config, &auth, "", "")){
    Serial.println("SignUp Ok");
    taskCompleted = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  config.token_status_callback = tokenStatusCallback; 
  Firebase.begin(&config, &auth);
  Firebase.reconnectNetwork(true);
  i=1;
}

void loop()
{ Serial.print(" It is in loop");
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 5000 || sendDataPrevMillis == 0)){
  sendDataPrevMillis = millis();
  
  if(Firebase.RTDB.setInt(&fbdo, "/test/value_i", i)){
    Serial.println("Data saved Succefully");
  }
  else
  Serial.println("Data not saved.");
}
  Serial.print("value of i=");
  Serial.print(i);
  i++;
  delay(5000);
  
}
