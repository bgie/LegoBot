/*  LegoBot ESP8266 udp to motor driver
 *  Copyright (C) 2018 Brecht Kuppens
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

// wifi_password should contain these 2 defines:
// #define WIFI_NETWORK "SSID"
// #define WIFI_PASSWORD "secret_password"
#include "wifi_password.h"

#define ROBOT_NAME "Robot 1"

#define MASTER_UDP_PORT  8000
#define SLAVE_UDP_PORT  8001
#define UDP_PACKET_BUFFERSIZE 128

#define STAYING_ALIVE_TIMEOUT_MSEC  5000

WiFiClient client;
WiFiUDP udpListener;
WiFiUDP udpSender;
IPAddress masterIp;
bool isConnected = false;
unsigned long stayingAliveTime = 0;
unsigned long previousMillis = 0;

char packetBuffer[UDP_PACKET_BUFFERSIZE];
String serialInput = "";

void setup() 
{
  Serial.begin(115200);
  Serial.println("Serial com up.");

  WiFi.persistent(false);
  WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);
  Serial.print("Connecting to wifi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  udpListener.begin(SLAVE_UDP_PORT);

  previousMillis = millis();
}

void loop()
{
  int packetSize = udpListener.parsePacket();
  if (packetSize)
  {
    int len = udpListener.read(packetBuffer, UDP_PACKET_BUFFERSIZE-1);
    if (len >= 0) packetBuffer[len] = 0;
    // processCommand(packetBuffer)
    Serial.print("UDP received: ");
    Serial.println(packetBuffer);

    if(!isConnected)
    {
      if(strcmp(packetBuffer, "HI") == 0)
      {
        Serial.print("Replying to ");
        Serial.println(udpListener.remoteIP());
        
        udpSender.beginPacket(udpListener.remoteIP(), MASTER_UDP_PORT);
        udpSender.write(ROBOT_NAME);
        udpSender.endPacket();
      }
      else if(strcmp(packetBuffer, "CONNECT") == 0)
      {
        masterIp = udpListener.remoteIP();
        Serial.print("Connected to ");
        Serial.println(udpListener.remoteIP());
        stayingAliveTime = 0;
        isConnected = true;
      }
    }
    else // is connected
    {
      if(strcmp(packetBuffer, "BYE") == 0)
      {
        masterIp = IPAddress();
        isConnected = false;
        Serial.println("Disconnected by master");
      }
      else if(strcmp(packetBuffer, "HAH") == 0)
      {
        stayingAliveTime = 0;      
      }
    }
  }

  unsigned long currentMillis = millis();
  unsigned long elapsed = currentMillis - previousMillis;
  previousMillis = currentMillis;

  if(isConnected)
  {
    stayingAliveTime += elapsed;
    if(stayingAliveTime > STAYING_ALIVE_TIMEOUT_MSEC)
    {
      masterIp = IPAddress();
      isConnected = false;
      Serial.println("Disconnected by timeout");
    }
  }
}
