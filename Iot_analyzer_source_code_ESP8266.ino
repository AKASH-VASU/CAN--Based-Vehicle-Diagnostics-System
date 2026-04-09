#include <SPI.h>
#include <mcp_can.h>
#include <ESP8266WiFi.h>

#define CS_PIN D8

MCP_CAN CAN(CS_PIN);

// 🔧 WiFi Credentials
const char* ssid = "project202502";
const char* password = "123456789";

// 🔒 Static IP (Adjusted to your network)
IPAddress local_IP(10, 142, 18, 200);
IPAddress gateway(10, 142, 18, 1);
IPAddress subnet(255, 255, 255, 0);

WiFiServer server(80);

// Parameters
int rpm = 0, speed = 0, temp = 0, load = 0, fuel = 0, throttle = 0;
float batt = 0;
int fuelcons = 0, distance = 0, airtemp = 0, o2 = 0, dtc = 0;

void setup() {
  Serial.begin(9600);

  // 🔹 CAN Initialization
  if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("CAN Ready");
  } else {
    Serial.println("CAN Failed");
    while (1);
  }
  CAN.setMode(MCP_NORMAL);

  // 🔹 Static IP Setup
  WiFi.config(local_IP, gateway, subnet);

  // 🔹 WiFi Connect
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("Open this in browser: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {

  // 🔹 Receive CAN Data
  unsigned long rxId;
  unsigned char len = 0;
  unsigned char buf[8];

  if (CAN.checkReceive() == CAN_MSGAVAIL) {

    CAN.readMsgBuf(&rxId, &len, buf);

    if (rxId == 0x100) {
      rpm = (buf[0] << 8) | buf[1];
      speed = buf[2];
      temp = buf[3];
      load = buf[4];
      fuel = buf[5];
      throttle = buf[6];
      batt = buf[7] / 10.0;
    }

    if (rxId == 0x101) {
      fuelcons = buf[0];
      distance = (buf[1] << 8) | buf[2];
      airtemp = buf[3];
      o2 = buf[4];
      dtc = buf[5];
    }
  }

  // 🔹 Web Client Handling
  WiFiClient client = server.available();

  if (client) {

    String html = "<html><head>";
    html += "<script>setTimeout(function(){ location.reload(); }, 2000);</script>";
    html += "<style>body{background:black;color:white;font-family:Arial;} h1{color:lime;}</style>";
    html += "</head><body>";

    html += "<h1>Vehicle Diagnostics Dashboard</h1>";

    html += "<h3>Engine</h3>";
    html += "RPM: " + String(rpm) + "<br>";
    html += "Speed: " + String(speed) + " km/h<br>";
    html += "Temp: " + String(temp) + " C<br>";
    html += "Load: " + String(load) + "%<br>";

    html += "<h3>Fuel & Power</h3>";
    html += "Fuel Level: " + String(fuel) + "%<br>";
    html += "Fuel Consumption: " + String(fuelcons) + " km/l<br>";
    html += "Battery: " + String(batt) + " V<br>";
    html += "Throttle: " + String(throttle) + "%<br>";

    html += "<h3>Sensors</h3>";
    html += "Air Temp: " + String(airtemp) + " C<br>";
    html += "O2 Sensor: " + String(o2) + "<br>";

    html += "<h3>Diagnostics</h3>";
    html += "Distance: " + String(distance) + " km<br>";
    html += "DTC: " + String(dtc) + "<br>";

    // 🚨 Alerts Section
    html += "<h2>Alerts</h2>";

    if (rpm > 4000)
      html += "<p style='color:red;'>CRITICAL RPM!</p>";

    if (load > 85)
      html += "<p style='color:red;'>HIGH ENGINE LOAD!</p>";

    if (temp > 100)
      html += "<p style='color:red;'>ENGINE OVERHEAT!</p>";

    if (fuel < 15)
      html += "<p style='color:red;'>LOW FUEL!</p>";

    if (batt < 11.8)
      html += "<p style='color:red;'>LOW BATTERY!</p>";

    if (dtc != 0)
      html += "<p style='color:red;'>FAULT DETECTED!</p>";

    html += "</body></html>";

    client.print(html);
    client.stop();
  }
}