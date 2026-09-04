#include <WiFi.h>
#include <HTTPClient.h>


const char* ssid = "name of Wi-Fi";
const char* password = "Password of Wi-fi";


const char* apiKey = "API key";

unsigned long counter = 0;

unsigned long previousMillis = 0;
const unsigned long counterInterval = 1000;   // 1 second

unsigned long previousUploadMillis = 0;
const unsigned long uploadInterval = 5000;   // 5 seconds


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  counter = 0;
}


void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= counterInterval) {
    previousMillis = currentMillis;
    counter++;
    Serial.print("Counter = ");
    Serial.println(counter);
  }



  if (currentMillis - previousUploadMillis >= uploadInterval) {
    previousUploadMillis = currentMillis;
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      String url = "https://api.thingspeak.com/update?api_key=";
      url += apiKey;
      url += "&field1=";
      url += String(counter);
      Serial.println("Sending data to ThingSpeak...");
      Serial.println(url);

      http.begin(url);
      int httpResponseCode = http.GET();
      if (httpResponseCode > 0) {
        Serial.print("HTTP Response Code: ");
        Serial.println(httpResponseCode);
        String response = http.getString();
        Serial.print("ThingSpeak Response: ");
        Serial.println(response);
      } else {
        Serial.print("Error sending GET request: ");
        Serial.println(httpResponseCode);
      }
      http.end();
    } else {
      Serial.println("WiFi disconnected!");
    }
  }
}
