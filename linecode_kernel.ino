// www.linecode.ro
// linecode_kernel.ino
// LineCode WebShell System 
// Coded by B. Alin Gabriel 2024

#include <ESP8266WiFi.h>
#include "shell_wbserver.h"
#include "kernel_cmd.h"
#include "html_core.h"
#include "sys_script.h"

const char* ssid = "wifi name here";                       
const char* password = "wifi password";           

unsigned long previousMillis = 0;             
const long interval = 200;                   
bool activityFlag = false;                   
void onActivityDetected() {
  activityFlag = true;  
}
void onNoActivity() {
  activityFlag = false;  
}
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.println("IP address: " + WiFi.localIP().toString());

  setupWebServer();
  
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  handleWebRequests(); 
  if (activityFlag) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));  
    }
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
