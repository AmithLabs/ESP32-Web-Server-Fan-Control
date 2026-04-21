/*
  ---------------------------------------------------------
  Project         : ESP32 Web Server Fan Control
  Youtube Channel : @AmithLabs
  Author          : Amith Wijekoon
  ---------------------------------------------------------

  This ESP32 project demonstrates a simple wireless
  fan ON / OFF control system using a web server.

  The ESP32 creates its own WiFi Access Point (AP Mode),
  so no external WiFi router is needed.

  When a mobile phone connects to the ESP32 WiFi and opens
  the IP address in a browser, a control webpage appears.

  Pressing:
    TURN ON  -> Fan turns ON
    TURN OFF -> Fan turns OFF

  A relay module is used to control the fan safely.

  The onboard RGB LED (NeoPixel) is also used as a
  status indicator:

    RED   -> Fan OFF
    GREEN -> Fan ON

  This project is ideal for learning:

  - ESP32 Web Server (ESP32-S3-DevKitC-1)
  - Access Point (AP Mode)
  - Relay Control
  - Mobile Browser Control
  - RGB LED Status Indication
  - Smart Home Basics

  ---------------------------------------------------------
  Hardware Connections (ESP32-S3-DevKitC-1)
  ---------------------------------------------------------

  Relay Module
    Relay IN   -> GPIO 4
    Relay VCC  -> 5V
    Relay GND  -> GND

  Fan Connection (Example using Relay)
    Power (+)  -> Relay COM
    Relay NO   -> Fan Positive
    Fan (-)    -> Power Supply Negative

  Onboard RGB LED
    Built-in NeoPixel LED
    Controlled by GPIO 48

  ---------------------------------------------------------
*/

#include <WiFi.h>
#include <Adafruit_NeoPixel.h>

//
// =====================================================
// WiFi Access Point Settings
// =====================================================
//
// This is the WiFi name and password created by ESP32.
// Your mobile phone should connect to this WiFi.
//

const char* ap_ssid = "ESP32_FAN_CONTROL";
const char* ap_password = "12345678";

//
// =====================================================
// Relay Pin
// =====================================================
//
// Relay input pin connected to ESP32 GPIO 4
//

const int relayPin = 4;

//
// =====================================================
// Onboard RGB LED (NeoPixel)
// =====================================================
//
// This ESP32-S3 board has an onboard addressable RGB LED
// driven by GPIO 48.
//
// LED_COUNT = only 1 LED on board
//

#define LED_PIN   48
#define LED_COUNT 1

//
// Create NeoPixel object
//

Adafruit_NeoPixel rgbLed(
  LED_COUNT,
  LED_PIN,
  NEO_GRB + NEO_KHZ800
);

//
// =====================================================
// Web Server Port
// =====================================================
//
// Port 80 = default HTTP web server port
//

WiFiServer server(80);

//
// =====================================================
// setup()
// =====================================================
//
// This runs only once when ESP32 starts
//

void setup() {

  //
  // Start Serial Monitor
  //

  Serial.begin(115200);
  delay(1000);

  //
  // =================================================
  // Relay Setup
  // =================================================
  //

  pinMode(relayPin, OUTPUT);

  //
  // Most relay modules are ACTIVE LOW
  //
  // HIGH = Relay OFF = Fan OFF
  // LOW  = Relay ON  = Fan ON
  //

  digitalWrite(relayPin, HIGH);

  //
  // =================================================
  // RGB LED Setup
  // =================================================
  //

  rgbLed.begin();

  //
  // Apply current LED state
  //

  rgbLed.show();

  //
  // Default startup condition:
  //
  // Fan OFF -> RED LED
  //

  rgbLed.setPixelColor(
    0,
    rgbLed.Color(255, 0, 0)
  );

  rgbLed.show();

  //
  // =================================================
  // Serial Monitor Startup Message
  // =================================================
  //

  Serial.println();
  Serial.println("====================================");
  Serial.println("ESP32 Fan Control Starting...");
  Serial.println("====================================");

  //
  // =================================================
  // Start ESP32 WiFi Access Point
  // =================================================
  //
  // ESP32 creates its own WiFi network
  //

  WiFi.softAP(ap_ssid, ap_password);

  //
  // Get ESP32 default AP IP address
  // Usually: 192.168.4.1
  //

  IPAddress IP = WiFi.softAPIP();

  Serial.println("WiFi Access Point Started!");

  Serial.print("WiFi Name (SSID): ");
  Serial.println(ap_ssid);

  Serial.print("Password: ");
  Serial.println(ap_password);

  Serial.print("ESP32 IP Address: ");
  Serial.println(IP);

  Serial.println("====================================");
  Serial.println("Connect your phone to ESP32 WiFi");
  Serial.println("Then open browser and type:");
  Serial.println(IP);
  Serial.println("====================================");

  //
  // =================================================
  // Start Web Server
  // =================================================
  //

  server.begin();

  Serial.println("Web Server Started");
}

//
// =====================================================
// loop()
// =====================================================
//
// This runs continuously forever
//

void loop() {

  //
  // Check if a new browser client is connected
  //

  WiFiClient client = server.available();

  //
  // If client exists
  //

  if (client) {

    Serial.println("New Client Connected");

    //
    // Read browser request
    //
    // Example:
    // GET /ON HTTP/1.1
    //

    String request = client.readStringUntil('\r');

    Serial.println(request);

    //
    // Clear remaining data
    //

    client.flush();

    //
    // =================================================
    // TURN ON Button Action
    // =================================================
    //

    if (request.indexOf("/ON") != -1) {

      //
      // Relay ON -> Fan ON
      //

      digitalWrite(relayPin, LOW);

      //
      // RGB LED -> GREEN
      //

      rgbLed.setPixelColor(
        0,
        rgbLed.Color(0, 255, 0)
      );

      rgbLed.show();

      Serial.println("Fan ON");
    }

    //
    // =================================================
    // TURN OFF Button Action
    // =================================================
    //

    if (request.indexOf("/OFF") != -1) {

      //
      // Relay OFF -> Fan OFF
      //

      digitalWrite(relayPin, HIGH);

      //
      // RGB LED -> RED
      //

      rgbLed.setPixelColor(
        0,
        rgbLed.Color(255, 0, 0)
      );

      rgbLed.show();

      Serial.println("Fan OFF");
    }

    //
    // =================================================
    // Send HTML Webpage to Browser
    // =================================================
    //

    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html; charset=UTF-8");
    client.println("Connection: close");
    client.println();

    client.println("<!DOCTYPE html>");
    client.println("<html>");

    //
    // =================================================
    // HEAD Section
    // =================================================
    //

    client.println("<head>");

    client.println("<meta charset='UTF-8'>");
    client.println("<meta name='viewport' content='width=device-width, initial-scale=1'>");

    client.println("<title>ESP32 Fan Control</title>");

    //
    // =================================================
    // CSS Styling
    // =================================================
    //

    client.println("<style>");

    //
    // Full page background
    //

    client.println("body {");
    client.println("  margin: 0;");
    client.println("  padding: 0;");
    client.println("  font-family: Arial, sans-serif;");
    client.println("  text-align: center;");
    client.println("  background: linear-gradient(to bottom, #081b5a, #1f4d8f);");
    client.println("  color: white;");
    client.println("}");

    //
    // Main title
    //

    client.println("h1 {");
    client.println("  margin-top: 40px;");
    client.println("  font-size: 42px;");
    client.println("  font-weight: bold;");
    client.println("}");

    //
    // Subtitle
    //

    client.println("h2 {");
    client.println("  font-size: 30px;");
    client.println("  color: #7fdfff;");
    client.println("  margin-bottom: 35px;");
    client.println("}");

    //
    // Fan emoji section
    //

    client.println(".fan {");
    client.println("  font-size: 90px;");
    client.println("  margin-bottom: 40px;");
    client.println("}");

    //
    // Button common style
    //

    client.println(".btn {");
    client.println("  width: 320px;");
    client.println("  padding: 24px;");
    client.println("  font-size: 30px;");
    client.println("  font-weight: bold;");
    client.println("  border: none;");
    client.println("  border-radius: 18px;");
    client.println("  margin: 18px;");
    client.println("  cursor: pointer;");
    client.println("  color: white;");
    client.println("  box-shadow: 0 8px 18px rgba(0,0,0,0.35);");
    client.println("}");

    //
    // Green ON button
    //

    client.println(".on {");
    client.println("  background: linear-gradient(to bottom, #59d92c, #2ecc71);");
    client.println("}");

    //
    // Red OFF button
    //

    client.println(".off {");
    client.println("  background: linear-gradient(to bottom, #ff4d3b, #e53935);");
    client.println("}");

    //
    // Remove underline from links
    //

    client.println("a {");
    client.println("  text-decoration: none;");
    client.println("}");

    //
    // Footer text
    //

    client.println("p {");
    client.println("  margin-top: 40px;");
    client.println("  font-size: 28px;");
    client.println("  color: #d9e6ff;");
    client.println("}");

    client.println("</style>");
    client.println("</head>");

    //
    // =================================================
    // BODY Section
    // =================================================
    //

    client.println("<body>");

    //
    // Page title
    //

    client.println("<h1>ESP32 Web Server</h1>");
    client.println("<h2>Fan ON / OFF Control</h2>");

    //
    // Fan icon section
    //

    client.println("<div class='fan'>🌀⚡</div>");

    //
    // TURN ON button
    //

    client.println("<a href='/ON'>");
    client.println("<button class='btn on'>🟢 TURN ON</button>");
    client.println("</a><br>");

    //
    // TURN OFF button
    //

    client.println("<a href='/OFF'>");
    client.println("<button class='btn off'>🔴 TURN OFF</button>");
    client.println("</a>");

    //
    // Footer text
    //

    client.println("<p>AmithLabs</p>");

    client.println("</body>");
    client.println("</html>");
    client.println();

    //
    // =================================================
    // Close Client Connection
    // =================================================
    //

    client.stop();

    Serial.println("Client Disconnected");
    Serial.println("------------------------------------");
  }
}