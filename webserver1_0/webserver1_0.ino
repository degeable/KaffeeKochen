/*
 WiFi Web Server LED Blink

 A simple web server that lets you blink an LED via the web.
 This sketch will print the IP address of your WiFi Shield (once connected)
 to the Serial monitor. From there, you can open that address in a web browser
 to turn on and off the LED on pin 5.

 If the IP address of your shield is yourAddress:
 http://yourAddress/H turns the LED on
 http://yourAddress/L turns it off

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 Circuit:
 * WiFi shield attached
 * LED attached to pin 5

 created for arduino 25 Nov 2012
 by Tom Igoe

ported for sparkfun esp32 
31.01.2017 by Jan Hendrik Berlin
 
 */

#include <WiFi.h>

const char* ssid     = "";
const char* password = "";

WiFiServer server(80);
int pin = 25;     // tust du pin hier
void setup()
{
    Serial.begin(115200);
    pinMode(pin, OUTPUT); 

    delay(10);

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();

}
 int t = 0;
 bool running = false;

void loop(){
 WiFiClient client = server.available();   // listen for incoming clients

 String tmp = "";
  if (client) {                             
    Serial.println("New Client.");          
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
      //  Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            Serial.println("Running: "+running);
            client.print(prepareHtmlPage(t,running));
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
        if (currentLine.endsWith("HTTP")){ 
          if (isDigit(currentLine.charAt(11))){
            tmp += currentLine.charAt(11);
          if (isDigit(currentLine.charAt(12))){
            tmp += currentLine.charAt(12);
          }
           t = tmp.toInt();
           Serial.println(t);
           running  = true;
           digitalWrite(pin, HIGH); 
          }
        }
      }
    }
 
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
    sleep(t);
    digitalWrite(pin, LOW); 
    running = false;
  }
}

String prepareHtmlPage(int duration, bool timerRunning)
{
  String htmlPage =
     String("HTTP/1.1 200 OK\r\n") +
            "Content-Type: text/html\r\n" +
            "Connection: close\r\n" +  
            "\r\n" +
            "<script>"+
            "function startTimer(duration, display) {"+
            "  var timer = duration, minutes, seconds;"+
            " setInterval(function () {"+
            "        minutes = parseInt(timer / 60, 10);"+
            "        seconds = parseInt(timer % 60, 10);"+
            "        minutes = minutes < 10 ? '0' + minutes : minutes;"+
            "        seconds = seconds < 10 ? '0' + seconds : seconds;"+
            "        display.textContent = minutes + ':' + seconds;"+
            "        if (--timer < 0) {"+
            "           timer = duration;"+
            "window.history.go(-1); return false;"+
            "        }"+
            "    }, 1000);"+
            "}"+
            "window.onload = function () {"+
            "    var time = "+duration+","+
            "        display = document.querySelector('#timer');"+
            "             if("+timerRunning+" != 0 && time != 0 )"+
            "            startTimer(time, display);"+
            "};"+
            "</script>"+
            "<div>Timer <span id='timer'>00:00</span></div>"+
            "<form id='timerForm'>"+
            "<label for='Zeit'>Zeit</label>"+
            "<input type='number' name='time' id='time' minlength='1' maxlength='60'>"+
            "<button type='submit'>Eingaben absenden</button>"+
            "</form>"+
            "\r\n";
  return htmlPage;
}
