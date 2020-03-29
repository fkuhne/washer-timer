/*
  CORONAVIRUS OUTBREAK: Auto-triggered hand sanitizer.

  Dependencies:
  - PubSubClient (instalar pela IDE)
  - Bifrost library for HC-SR04 (instalar pela IDE)

  03/2020
  Felipe Kühne - fkuhne@gmail.com
*/

#include "util.h"
#include "wifi.h"
#include "mqtt.h"

#include <hcsr04.h>
#include <Servo.h>

#define LED_PIN LED_BUILTIN
#define BUTTON_PIN D3 // 'Flash' button
#define SERVO_PIN D8
#define TRIG_PIN D5
#define ECHO_PIN D6

#define MIN_DISTANCE 200 // Minumium distance in millimeters
#define SERVO_MIN 20
#define SERVO_MAX (SERVO_MIN + 162)

int washerCounter = 0;
unsigned lastTimeMsg = 0;

WFclass wifi;

const String publishTopic("fkuhne/mqtt/washertimer/output");
const String subscribeTopic("fkuhne/mqtt/washertimer/input");
const String mqttServer("iot.eclipse.org");
const int mqttServerPort = 1883;
MqttClient mqttClient(mqttServer, mqttServerPort);

HCSR04 hcsr04(TRIG_PIN, ECHO_PIN, 20, 4000);

Servo servo;

void connect_wifi_and_mqtt()
{
  wifi.connectFromList();
  mqttClient.connect();
  mqttClient.subscribe(subscribeTopic);
  mqttClient.setCallback(callback);
  blink_led(LED_PIN, 5);
}

void callback(char *topic, byte *payload, unsigned int length)
{
  char message[length + 1];
  memcpy(message, payload, length);
  message[length] = 0;

  Serial.println("Mensagem \"" + String(message) + "\" recebida no tópico \"" + String(topic) + "\"");

  if (strncmp(topic, subscribeTopic.c_str(), subscribeTopic.length()))
    return;

  if (!strncmp(message, "on", 2))
    servoControl();
}

void servoControl()
{
  servo.attach(SERVO_PIN);  
  delay(100);
  
  for(int pos = SERVO_MIN; pos <= SERVO_MAX; pos++)
  {
    servo.write(pos);
    delay(23);
    blink_led(LED_PIN, 5);
  }

  blink_led(LED_PIN, 5);
  delay(500);

  for(int pos = SERVO_MAX; pos >= SERVO_MIN; pos--)
  {
    servo.write(pos);
    delay(10);
  }

  washerCounter++;
  delay(200);
  servo.detach();
}

void setup()
{
  delay(100);
  Serial.begin(9600);
  printBanner();

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  servo.attach(SERVO_PIN);
  servo.write(SERVO_MIN);
  delay(500);
  servo.detach();
}

void loop()
{
//  if (!mqttClient.connected())
//    connect_wifi_and_mqtt();
//
//  mqttClient.loop();

  long now = millis();
  if (now - lastTimeMsg > 500)
  {
    lastTimeMsg = now;

    int distance = hcsr04.distanceInMillimeters();
    if(distance == -1)
      return;

    Serial.printf("Distance = %d mm\n", distance);

    if (distance < MIN_DISTANCE)
      servoControl();
  }
}
