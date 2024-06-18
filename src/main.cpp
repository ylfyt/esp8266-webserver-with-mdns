#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h>

const char *ssid = "URHEART";
const char *password = "12345678yy";

AsyncWebServer server(80);
ESP8266WiFiMulti wifiMulti;

void hello(AsyncWebServerRequest *req)
{
    req->send(200, "text/html", "<h1>Hello, World</h1>");
}

void ping(AsyncWebServerRequest *req)
{
    req->send(200, "text/html", "<h1>PONG</h1>");
}

void setupWebServer()
{
    server.on("/", hello);
    server.on("/ping", ping);
    server.begin();
}

void setup()
{
    Serial.begin(115200);
    delay(10);
    Serial.println('\n');

    wifiMulti.addAP(ssid, password);
    Serial.print("Connecting to wifi ");
    while (wifiMulti.run() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected: ");
    Serial.println(WiFi.localIP());
    if (!MDNS.begin("esp8266"))
    {
        Serial.println("Error setting up MDNS responder!");
    }
    Serial.println("mDNS: esp8266.local");

    setupWebServer();
}

void loop()
{
    MDNS.update();
}