#include <ESP8266WiFi.h>
#include "network.h"
#include "mellow.h"
#include "const.h"



const char* ssid = "******";
const char* password = "******";

WiFiServer server(port);

String header;                  // Variable to store the HTTP request
const long timeoutTime = 2000;  // Define timeout time in milliseconds (example: 2000ms = 2s)



void setup() {

  //Sets the serial interface to 9600, used for debug
  Serial.begin(9600);

  //Sets
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  setupWiFi(server, ssid, password);

}

void loop() {

  WiFiClient client = server.available();

  // wait for a client (web browser) to connect

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    unsigned long currentTime = millis();
    unsigned long previousTime = currentTime;

    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected

      currentTime = millis();

      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;

        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
	  	      sendHeader(client);
            String JSONdata = toJson(String(getWaterLevel(trigPin, echoPin)));


            // Display the JSON data
            client.println(JSONdata);

            break;

          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
