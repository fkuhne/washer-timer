#include "mqtt.h"

MqttClient::MqttClient(const String &mqttServer, const int mqttPort)
{
  mqttClient = new PubSubClient(wifiClient);
  mqttClient->setServer(mqttServer.c_str(), mqttPort);

  /* O MAC address do módulo ESP será o device ID. */
  byte mac[6];
  WiFi.macAddress(mac);
  String _deviceId = String(mac[0], HEX) + String(mac[1], HEX) + String(mac[2], HEX) +
                     String(mac[3], HEX) + String(mac[4], HEX) + String(mac[5], HEX);

  _mqttServer = mqttServer;
  _mqttPort = mqttPort;
}

// Funcão para efetuar conexão com servidor mqtt.
void MqttClient::connect()
{
  Serial.print("Conectando-se ao broker MQTT " + _mqttServer);
  Serial.print(":"); Serial.print(_mqttPort);

  for (int count = 0; count <= 30; count++)
  {
    Serial.print(".");

    if (mqttClient->connected())
      break;

    if (mqttClient->connect(_deviceId.c_str()))
    {
      Serial.println(" conectado!");
    }
    else if (count == 30)
    {
      Serial.println(" desisto :(");
      ESP.restart();
    }
    else delay(1000);
  }
}

// Função para verificar conexão mqtt.
int MqttClient::connected()
{
  return mqttClient->connected();
}

/* Função de repetição. Ela fica sendo chamada repetidamente durante a execução
     do programa. */
void MqttClient::loop()
{
  mqttClient->loop();
}

// Configura a função callback na biblioteca PubSubClient.
void MqttClient::setCallback(void (*callback)(char*, uint8_t*, unsigned int))
{
  Serial.println("Configurando função de callback para recebimento de mensagens.");
  mqttClient->setCallback(callback);
}

// Inscrição em um tópico
boolean MqttClient::subscribe(const String &topic)
{
  Serial.println("Fazendo inscrição no tópico \"" + topic + "\"");
  return mqttClient->subscribe(topic.c_str());
}

// Desinscrição em um tópico
boolean MqttClient::unsubscribe(const String &topic)
{
  Serial.println("Desinscrevendo do tópico \"" + topic + "\"");
  return mqttClient->unsubscribe(topic.c_str());
}

// Publica mensagens.
boolean MqttClient::publish(const String &topic, const String &payload)
{
  Serial.print("Publicando \"" + payload + "\" no tópico \"" + topic);

  int ret = mqttClient->publish(topic.c_str(), payload.c_str(), payload.length());
  if (!ret)
    Serial.println("\" falhou :(");
  else 
    Serial.println("\" com sucesso.");

  return (boolean)ret;
}
