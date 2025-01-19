// www.linecode.ro
// sys_script.h

#ifndef SYS_SCRIPT_H
#define SYS_SCRIPT_H

#include <ESP8266WiFi.h>

String getMemoryInfo() {
  return "Free Heap: " + String(ESP.getFreeHeap()) + " bytes";
}

String getSystemInfo() {
  return "Chip ID: " + String(ESP.getChipId()) + "\n" +
         "SDK Version: " + String(ESP.getSdkVersion());
}

#endif
