#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

bool objectDetected = false; //flag

char ssid[] = "xxx";   // your network SSID (name)
char pass[] = "xxx"; // your network password

WiFiUDP Udp;
const IPAddress outIP(192,168,43,235);  //remote IP of the device you want to send OSC msg to
const unsigned int localPort = 8888;
const unsigned int outPort = 8891; // port of the device you want to send OSC msg to

void setupWifi() {
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(Udp.localPort());
}


void setup() {
  pinMode(D2, INPUT);
  Serial.begin(115200);
  setupWifi();
}

void loop() {
  if (digitalRead(D2) == LOW) {
    if (!objectDetected) {
      Serial.println("Tester detected");
      objectDetected = true;

      OSCMessage msg("/play/1");
      //msg.add("1");
      Udp.beginPacket(outIP, outPort);
      msg.send(Udp);
      Udp.endPacket();
      msg.empty();
    }
    delay(100);  // Adjust the delay as needed
  } else {
    if (objectDetected) {
      OSCMessage msg("/play/0");
      //msg.add("0");
      Udp.beginPacket(outIP, outPort);
      msg.send(Udp);
      Udp.endPacket();
      msg.empty();
      objectDetected = false;
    }
  }
}
