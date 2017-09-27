/*
 * MQTT OTA HALLWAY LIGHT v4
 * Maxime MOREILLON
 * Changelog
 * v4
 * - Now using Async MQTT library
 */

// Libraries
#include <ESP8266WiFi.h> // Main ESP8266 library
#include <ArduinoOTA.h> // OTA update library
#include <WiFiUdp.h> // Required for OTA
#include <AsyncMqttClient.h> // MQTT library
#include <Ticker.h> // Used when reconecting MQTT upon wifi drop

#include "credentials.h";

// Wifi
WiFiEventHandler wifi_connect_handler;
WiFiEventHandler wifi_disconnect_handler;
Ticker wifi_reconnect_timer;

// OTA settings
#define HOSTNAME "entranceLight"

// MQTT
AsyncMqttClient MQTT_client;
Ticker MQTT_reconnect_timer;
#define MQTT_BROKER_ADDRESS IPAddress(192, 168, 1, 2)
#define MQTT_PORT 1883
#define  MQTT_LIGHT_COMMAND_TOPIC "light/entrance/command"
#define  MQTT_LIGHT_STATUS_TOPIC "light/entrance/status"
#define  MQTT_MOTION_STATUS_TOPIC "motion/entrance/status"
#define  MQTT_LAST_WILL "OFF"
#define  MQTT_QOS 1
#define  MQTT_RETAIN true

// Pin mapping
#define  LIGHT_PIN D6
#define  PIR_PIN D2

// Misc variables
char* light_status;
int last_PIR_reading;

void setup()
{
  // Mandatory initial delay
  delay(10);

  // Serial init
  Serial.begin(115200);
  Serial.println();
  Serial.println(); // Separate serial stream from initial gibberish

  // IO init
  pinMode(PIR_PIN, INPUT);
  pinMode(LIGHT_PIN, OUTPUT);

  // Light initial state
  digitalWrite(LIGHT_PIN, LOW);
  light_status = "OFF";

  wifi_setup();
  MQTT_setup();
  OTA_setup();

  wifi_connect();
}


void loop()
{
  ArduinoOTA.handle();
  read_PIR();
}
