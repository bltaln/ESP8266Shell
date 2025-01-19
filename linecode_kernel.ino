// www.linecode.ro
// linecode_kernel.ino
// LineCode WebShell System 
// Coded by B. Alin Gabriel 2024

#include <ESP8266WiFi.h>
#include "shell_wbserver.h"
#include "kernel_cmd.h"
#include "html_core.h"
#include "sys_script.h"

const char* ssid = "WirLab Gabriel";          // Numele rețelei Wi-Fi
const char* password = "29101986";            // Parola Wi-Fi

unsigned long previousMillis = 0;             // Timpul pentru clipire LED
const long interval = 200;                    // Intervalul pentru clipirea LED-ului (în milisecunde)
bool activityFlag = false;                    // Flag pentru activitate

// Definirea funcțiilor de activitate
void onActivityDetected() {
  activityFlag = true;  // Marchează activitatea
}

void onNoActivity() {
  activityFlag = false;  // Oprește activitatea
}

void setup() {
  Serial.begin(115200);
  
  // Conectare la rețeaua Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.println("IP address: " + WiFi.localIP().toString());

  // Configurare server web
  setupWebServer();
  
  // Setare pin LED_BUILTIN ca ieșire
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  handleWebRequests(); // Gestionează cererile web
  
  // Dacă există activitate (cerere web primită), aprinde LED-ul
  if (activityFlag) {
    unsigned long currentMillis = millis();

    // Clipire LED în intervalul definit
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));  // Inversează starea LED-ului
    }
  } else {
    // LED-ul este stins atunci când nu există activitate
    digitalWrite(LED_BUILTIN, LOW);
  }
}
