The folder "StiftReader" contains the Arduino project when using an Arduino MEGA in combination with a RasperryPi as Wifi Proxy.
The RFID Reader is attateched to the Arduino which ist attatech to the RaspberryPi.
The RapsberryPi recieves over Serial-Port alle Tag-IDs and calls the API from the server to update the location of the tool.
On the RaspberryPi must run the Pyhton script read.py.

The folder "StiftReaderWiFi" contains the Arduino project when using an "Arduino Uno WiFi Rev2" wich allready has a WiFi onboard an therefore does not need a RasperryPi. The Arduino calls for every Tag encountered the API from the Webserver to update the location of the tool.


On both usecases the WiFi SSID and the Server-URL must be cheange for pruduction.
