#include <ESP8266WiFi.h>

const char* ssid = "galaxy";
const char* password = "asdf1234";
const int ledDesk = 5;
int brightness = 0;
int currentBrightness = 0;
bool isLightOn=false;
// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  // set the digital pin as output:
  pinMode(ledDesk, OUTPUT);
  
  Serial.begin(9600);
  delay(10);
  
  // Connect to WiFi network
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
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  if(brightness != (int)currentBrightness) {
    //int progress = ((brightness - currentBrightness)>0) ? ((brightness - currentBrightness)/brightness) : ((currentBrightness - brightness)/brightness);
    float plus = ((float)brightness - (float)currentBrightness)/(float)50;
    if(plus < 1 && plus > 0) plus = 1;
    else if(plus > -1 && plus < 0) plus = -1;
    currentBrightness += (int)plus;
    analogWrite(ledDesk, (int)(currentBrightness));

    Serial.print("currentBrightness: "); Serial.print(currentBrightness);
    Serial.print("\tplus: "); Serial.print(plus);
    Serial.print("\tbrightness: "); Serial.println(brightness);
    delay(1);
  }
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("new client");

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  // Match the request
/*
  if (req.indexOf("/led.cgi?status=0") > 0) {
    // If the request contains "/led.cgi?status=0", turn off the LED
    brightness = 0;
    analogWrite(ledDesk, brightness);
  }
  else */
  if (req.indexOf("/led.cgi?status=") > 0) {
    brightness = req.substring(req.indexOf('=') + 1).toInt();
  }

  // Prepare the response
  //표준 http 응답 헤더 전송 시작
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println();

  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<style>");
  client.println("input[type=range] { width: 80%; }");
  client.println(".toggle-switch { position: relative; display: inline-block; width: 60px; height: 34px; }");
  client.println(".toggle-switch input { opacity: 0; width: 0; height: 0; }");
  client.println(".slider { position: absolute; cursor: pointer; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 34px; transition: .4s; }");
  client.println(".slider:before { position: absolute; content: ''; height: 26px; width: 26px; left: 4px; bottom: 4px; background-color: white; border-radius: 50%; transition: .4s; }");
  client.println("input:checked + .slider { background-color: #2196F3; }");
  client.println("input:focus + .slider { box-shadow: 0 0 1px #2196F3; }");
  client.println("input:checked + .slider:before { transform: translateX(26px); }");
  client.println("</style>");
  client.println("</head>");
  client.println("<body>");
  client.println("<br />");
  client.println("<form method=\"get\" action=\"/led.cgi\">");
  client.println("<p> Brightness : <input type=\"range\" name=\"status\" min=\"0\" max=\"255\" value=\"" + String(brightness) + "\" onchange=\"updateBrightness(this.value)\">");
  client.println("<p> <label class=\"toggle-switch\"><input type=\"checkbox\" name=\"toggle\" value=\"on\" " + String(isLightOn ? "checked" : "") + " onchange=\"toggleLight(this)\"><span class=\"slider\"></span></label> Light On/Off");
  client.println("</form>");

  client.println("<script>");
  client.println("function updateBrightness(value) {");
  client.println("  var xhttp = new XMLHttpRequest();");
  client.println("  xhttp.open('GET', '/led.cgi?status=' + value, true);");
  client.println("  xhttp.send();");
  client.println("}");

  client.println("function toggleLight(checkbox) {");
  client.println("  var xhttp = new XMLHttpRequest();");
  client.println("  var status = checkbox.checked ? 'on' : 'off';");
  client.println("  xhttp.open('GET', '/led.cgi?toggle=' + status, true);");
  client.println("  xhttp.send();");
  client.println("}");
  client.println("</script>");

  client.println("</body>");
  client.println("</html>");

  delay(1);
  Serial.println("Client disconnected");
}