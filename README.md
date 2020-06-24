# KaffeeKochenJunge
<<<<<<< HEAD
ESP webserver that controls a coffee grinder with a timer.

Just set the correct pin and WIFI SSID and passwort.

Copy the libraries folder in the Arduino folder to install the ESPasyncwebserver and AsnycTCP libraries.

For the file system on the ESP you will need the Sketch data uploader:

1) Go to the releases page and click the ESP32FS-1.0.zip file to download: [Here]](https://github.com/me-no-dev/arduino-esp32fs-plugin/releases/)

2) Go to the Arduino IDE directory, and open the Tools folder.

=======
ESP webserver that controls a coffee grinder

Musst nur die Pins entsprechend setzen und ssid+pw dann sollte es gehen. 

Da jetzt ein Asynchroner Webserver drin ist, musst du noch die libs installieren. EInfach den inhalte des libraries ordner in den von der Adruino IDE kopieren. 

Dazu brauchst du noch den Sketch uploader:

1) Go to the releases page and click the ESP32FS-1.0.zip file to download.
[Drückst du hier](https://github.com/me-no-dev/arduino-esp32fs-plugin/releases/https://github.com/me-no-dev/arduino-esp32fs-plugin/releases/)

2) Go to the Arduino IDE directory, and open the Tools folder.


>>>>>>> 963e8dc42713f4b89d613013f6c53492d6fea1e3
3) Unzip the downloaded .zip folder to the Tools folder. You should have a similar folder structure:

<home_dir>/Arduino-<version>/tools/ESP32FS/tool/esp32fs.jar

<<<<<<< HEAD
(If youre using a MAC go to the application and right klick to "Show package content" -> Contents/Java/tools/)
=======
(wenn du auf mac bist, musst du auf die arduino app gehen und inhalt anzeigen. Dann unter Contents/Java/tools/)
>>>>>>> 963e8dc42713f4b89d613013f6c53492d6fea1e3

4) Finally, restart your Arduino IDE.

To check if the plugin was successfully installed, open your Arduino IDE. Select your ESP32 board, go to Tools and check that you have the option “ESP32 Sketch Data Upload“.
