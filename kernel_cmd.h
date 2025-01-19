// www.linecode.ro
// www.linecode.ro
// kernel_cmd.h

#ifndef KERNEL_CMD_H
#define KERNEL_CMD_H

#include <ESP8266WiFi.h>
#include "sys_script.h"

String processCommand(String command) {
  if (command == "cpu") {
    return "CPU Frequency: " + String(ESP.getCpuFreqMHz()) + " MHz";
  } else if (command == "mem") {
    return getMemoryInfo();
  } else if (command == "sys") {
    return getSystemInfo();
  } else if (command == "ip") {
    return "IP Address: " + WiFi.localIP().toString();
  } else if (command == "reset") {
    // Aș dori să adaug un mesaj de confirmare înainte de a restarta dispozitivul
    return "Are you sure you want to restart? Type 'yes' to confirm.";
  } else if (command == "scan") {
    // Înlocuim scanarea WiFi cu un buffer de rețele scanate pentru a evita scanările repetate
    static String scanResult = "";
    static unsigned long lastScanTime = 0;
    
    unsigned long currentMillis = millis();
    if (currentMillis - lastScanTime > 60000) {  // Dacă a trecut mai mult de 1 minut de la ultima scanare
      int n = WiFi.scanNetworks(); // Scanează rețelele WiFi
      if (n == 0) {
        scanResult = "No WiFi networks found.";
      } else {
        scanResult = "Found " + String(n) + " WiFi network(s):\n";
        for (int i = 0; i < n; ++i) {
          scanResult += String(i + 1) + ". " + WiFi.SSID(i) + " (Signal: " + String(WiFi.RSSI(i)) + " dBm)\n";
        }
      }
      lastScanTime = currentMillis; // Actualizează timpul ultimei scanări
    }
    return scanResult;
  } else if (command == "help") {
    return "Available commands:\n"
           " - cpu: Show CPU frequency\n"
           " - mem: Show free heap memory\n"
           " - sys: Show system info\n"
           " - ip: Show the device IP address\n"
           " - reset: Restart the device\n"
           " - scan: Scan for WiFi networks\n"
           " - help: Show this help message";
  } else {
    return "Error: Unknown command. Type 'help' to see the list of available commands.";
  }
}

#endif
