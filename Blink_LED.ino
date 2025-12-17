void setup() {
  Serial.begin(115200);
  Serial.println("Initializing...");
  pinMode(2, OUTPUT);
}

void loop() {
  digitalWrite(2, HIGH);  
  Serial.println("LED is ON");
  delay(1000);   

  Serial.println("LED is OFF");                     
  digitalWrite(LED_BUILTIN, LOW);   
  delay(1000);                      
}
