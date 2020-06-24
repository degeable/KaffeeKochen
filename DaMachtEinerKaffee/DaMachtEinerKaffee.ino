#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

// Replace with your network credentials
const char* ssid = "SSID";
const char* password = "PW";

// Set LED GPIO
const int ledPin = 25;
// Stores LED state
String motorRunning = "false";
String timeValue = "40";
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Replaces placeholder with LED state value
String processor(const String& var){
  Serial.println(var);
  if(var == "RUNNING"){
    Serial.print(motorRunning);
    return motorRunning;
  }
    if(var == "TIMEVAL"){
    Serial.print(timeValue);
    return timeValue;
  }
    if(var == "IMG"){
      if(motorRunning  == "true"){
        return "https://i.giphy.com/media/3ohc0RX6czoFUc64tq/giphy.webp";
      }
    return "https://i.imgur.com/2xUgLE0.png";
    }
  return String();
}

 
void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });

  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/script.js", "text/javascript");
  });

  // Route to set GPIO to HIGH
  server.on("/start", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("got the request:" + request->url());
    Serial.println("Timer ON");
    if (request->hasParam("start")){
    timeValue=request->getParam("start")->value();
    }
    motorRunning = "true";
    digitalWrite(ledPin, HIGH);  
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
    server.on("/stop", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("got the request:" + request->url());
    Serial.println("Timer Off");
    if (request->hasParam("stopVal")){
      if (request->getParam("stopVal")->value() == "0"){
        timeValue = "40";
      }else{
      timeValue=request->getParam("stopVal")->value();
      }
    }
    motorRunning = "false";
    digitalWrite(ledPin, LOW);
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Start server
  server.begin();
}
 
void loop(){
  
}
