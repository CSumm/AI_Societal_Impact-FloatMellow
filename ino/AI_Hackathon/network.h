
void setupWiFi(WiFiServer &server, String ssid, String pw){
  WiFi.begin(ssid, pw);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

// HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
// and a content-type so the client knows what's coming, then a blank line:
// Since we're developping an API, the content-type is application/json
void sendHeader(WiFiClient &client){
	client.println("HTTP/1.1 200 OK");
	client.println("Content-type:application/json");
	client.println("Connection: close");
	client.println();
}


String toJson(String distance){
  String JSONdata = "{ \"level\": \""+distance+"\"}";
  return JSONdata;
}


