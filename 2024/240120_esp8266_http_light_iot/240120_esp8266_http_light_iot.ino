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
    float progress = ((brightness - currentBrightness)>0) ? ((float)brightness - (float)currentBrightness)/(float)brightness) : ((float)brightness - (float)currentBrightness)/(float)brightness);
    float plus = ((float)brightness - (float)currentBrightness)/(float)(50*(1-progress));
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
  client.println("input[type=range] {");
  client.println("  -webkit-appearance: none;");
  client.println("  width: 80%;");
  client.println("  height: 10px;");
  client.println("  border-radius: 5px;");
  client.println("  background: #d3d3d3;");
  client.println("  outline: none;");
  client.println("  opacity: 0.7;");
  client.println("  -webkit-transition: 0.2s;");
  client.println("  transition: opacity 0.2s;");
  client.println("}");

  client.println("input[type=range]:hover {");
  client.println("  opacity: 1;");
  client.println("}");

  client.println("input[type=range]::-webkit-slider-thumb {");
  client.println("  -webkit-appearance: none;");
  client.println("  appearance: none;");
  client.println("  width: 20px;");
  client.println("  height: 20px;");
  client.println("  border-radius: 50%;");
  client.println("  background: #4CAF50;");
  client.println("  cursor: pointer;");
  client.println("}");

  client.println("input[type=range]::-moz-range-thumb {");
  client.println("  width: 20px;");
  client.println("  height: 20px;");
  client.println("  border-radius: 50%;");
  client.println("  background: #4CAF50;");
  client.println("  cursor: pointer;");
  client.println("}");
  
  client.println(".toggle-switch {");
  client.println("  position: relative;");
  client.println("  display: inline-block;");
  client.println("  width: 60px;");
  client.println("  height: 34px;");
  client.println("}");

  client.println(".toggle-switch input {");
  client.println("  opacity: 0;");
  client.println("  width: 0;");
  client.println("  height: 0;");
  client.println("}");

  client.println(".slider {");
  client.println("  position: absolute;");
  client.println("  cursor: pointer;");
  client.println("  top: 0;");
  client.println("  left: 0;");
  client.println("  right: 0;");
  client.println("  bottom: 0;");
  client.println("  background-color: #ccc;");
  client.println("  border-radius: 34px;");
  client.println("  transition: .4s;");
  client.println("}");

  client.println(".slider:before {");
  client.println("  position: absolute;");
  client.println("  content: '';");
  client.println("  height: 26px;");
  client.println("  width: 26px;");
  client.println("  left: 4px;");
  client.println("  bottom: 4px;");
  client.println("  background-color: white;");
  client.println("  border-radius: 50%;");
  client.println("  transition: .4s;");
  client.println("}");

  client.println("input:checked + .slider {");
  client.println("  background-color: #2196F3;");
  client.println("}");

  client.println("input:focus + .slider {");
  client.println("  box-shadow: 0 0 1px #2196F3;");
  client.println("}");

  client.println("input:checked + .slider:before {");
  client.println("  transform: translateX(26px);");
  client.println("}");
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