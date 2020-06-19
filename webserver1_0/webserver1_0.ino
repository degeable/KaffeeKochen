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

const char* ssid     = "indanet";
const char* password = "***REMOVED***";

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
 int t = 40;
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
            "<style>"+
             ":root {"+
"  --backgroundColor: rgba(246, 241, 209);"+
"  --colorShadeA: rgb(106, 163, 137);"+
"  --colorShadeB: rgb(121, 186, 156);"+
"  --colorShadeC: rgb(150, 232, 195);"+
"  --colorShadeD: rgb(187, 232, 211);"+
"  --colorShadeE: rgb(205, 255, 232);"+
"}"+

"@import url('https://fonts.googleapis.com/css?family=Open+Sans:400,400i,700');"+
"* {"+
"  box-sizing: border-box;"+
"}"+
"*::before, *::after {"+
"  box-sizing: border-box;"+
"}"+
"body {"+
"  font-family: 'OpenSans', sans-serif;"+
"  font-size: 1rem;"+
"  line-height: 2;"+
"  display: flex;"+
"          align-items: center;"+
"          justify-content: center;"+
"  margin: 0;"+
"  min-height: 100vh;"+
"  background: var(--backgroundColor);"+
"}"+
"button {"+
"  position: relative;"+
"  display: inline-block;"+
"  cursor: pointer;"+
"  outline: none;"+
"  border: 0;"+
"  horizontal-align: middle;"+
"  text-decoration: none;"+
"  font-size: 1.5rem;"+
"    color:var(--colorShadeA);"+
"  font-weight: 700;"+
"  text-transform: uppercase;"+
"  font-family: inherit;"+
"}"+

"button.big-button {"+
"   padding: 1em 2em;"+
"   border: 2px solid var(--colorShadeA);"+
"  border-radius: 1em;"+
"  background: var(--colorShadeE);"+
"transform-style: preserve-3d;"+
"   transition: all 175ms cubic-bezier(0, 0, 1, 1);"+
"}"+
"button.big-button::before {"+
"  position: absolute;"+
"  content: '';"+
"  width: 100%;"+
"  height: 100%;"+
"  top: 0;"+
"  left: 0;"+
"  right: 0;"+
"  bottom: 0;"+
"  background: var(--colorShadeC);"+
"  border-radius: inherit;"+
"    box-shadow: 0 0 0 2px var(--colorShadeB), 0 0.75em 0 0 var(--colorShadeA);"+
" transform: translate3d(0, 0.75em, -1em);"+
"     transition: all 175ms cubic-bezier(0, 0, 1, 1);"+
"}"+


"button.big-button:hover {"+
"  background: var(--colorShadeD);"+
"  transform: translate(0, 0.375em);"+
"}"+

"button.big-button:hover::before {"+
"  transform: translate3d(0, 0.75em, -1em);"+
"}"+

"button.big-button:active {"+
"            transform: translate(0em, 0.75em);"+
"}"+

"button.big-button:active::before {"+
"  transform: translate3d(0, 0, -1em);"+
  
"      box-shadow: 0 0 0 2px var(--colorShadeB), 0 0.25em 0 0 var(--colorShadeB);"+

"}"+
".input {"+
"  width: 20%;"+
"  padding: 12px 20px;"+
"  margin: 8px 0;"+
"  display: inline-block;"+
"  border: 1px solid #ccc;"+
"  border-radius: 4px;"+
"  box-sizing: border-box;"+
"  font-size: 36px; "+
//"  vertical-align: middle;"+
"}"+

            "</style>"+
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
            "<div> <img src='https://cdn.shopify.com/s/files/1/0704/4925/t/12/assets/animated-Grinder.gif' data-gifffer-width='250' data-gifffer-height='237' /> </div>"+ 
            "<span  class='input' id='timer'>00:00</span>"+
            "<form id='timerForm'>"+
            "<input  class='input' type='number' name='time' id='time' minlength='10' step='10' maxlength='60' value='40' >"+
            "<button class='big-button' type='submit'>Eingaben absenden</button>"+
            "</form>"+
            "\r\n";
  return htmlPage;
}
