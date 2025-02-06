// www.linecode.ro
// shell_wbserver.h
#ifndef SHELL_WBSERVER_H
#define SHELL_WBSERVER_H

#include <ESP8266WebServer.h>
#include "kernel_cmd.h"
#include "html_core.h"  

ESP8266WebServer server(80);

void setupWebServer() {
    server.on("/", HTTP_GET, []() {
        server.send(200, "text/html", getHTML());  
    });

    server.on("/cmd", HTTP_GET, []() {
        String command = server.arg("command");
        String response = processCommand(command);
        server.send(200, "text/plain", response);
    });

    server.begin();
}

void handleWebRequests() {
    server.handleClient();
}

#endif
