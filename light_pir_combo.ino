/*
 * Light and PIR combo
 * Maxime MOREILLON
 * Board type: Wemos D1 Mini
 */

// Libraries
#include <ESP8266WiFi.h> // Main ESP8266 library
#include <ArduinoOTA.h> // OTA update library
#include <WiFiUdp.h> // Required for OTA
#include <AsyncMqttClient.h> // MQTT library
#include <Ticker.h> // Used when reconecting MQTT upon wifi drop

// Credentials and device specific configuration
#include "credentials.h";
//#include "entrance_light_config.h";
#include "bathroom_light_config.h";

// Wifi
WiFiEventHandler wifi_connect_handler;
WiFiEventHandler wifi_disconnect_handler;
Ticker wifi_reconnect_timer;

// MQTT
AsyncMqttClient MQTT_client;
Ticker MQTT_reconnect_timer;
#define MQTT_BROKER_ADDRESS IPAddress(192, 168, 1, 2)
#define MQTT_PORT 1883
#define  MQTT_LAST_WILL "OFF"
#define  MQTT_QOS 1
#define  MQTT_RETAIN true

// Pin mapping
#define  LIGHT_PIN D6
#define  PIR_PIN D2

// Misc variables
char* light_status = INITIAL_STATE;
int last_PIR_reading;

void setup()
{
  // Mandatory initial delay
  delay(10);

  // Serial init
  Serial.begin(115200);
  Serial.println();
  Serial.println(); // Separate serial stream from initial gibberish

  IO_setup();
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
