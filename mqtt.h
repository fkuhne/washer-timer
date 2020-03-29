#ifndef __MQTT_H__
#define __MQTT_H__

#if defined(ESP8266)
# include <ESP8266WiFi.h>
#elif defined(ESP32)
# include <WiFi.h>
#endif
#include <PubSubClient.h>

class MqttClient
{
  public:
    MqttClient(const String &mqttServer, const int mqttPort); // Construtor
    void connect(); // Funcão para efetuar conexão com servidor mqtt
    int connected(); // Função para verificar conexão
    void loop(); // Função de repetição

    void setCallback(void (*callback)(char*, uint8_t*, unsigned int)); // Configura callback para tratar mensagens
    boolean subscribe(const String &topic); // Inscrição em um tópico
    boolean unsubscribe(const String &topic); // Desinscrição em um tópico
    boolean publish(const String &topic, const String &payload); // Função para publicar mensagens

  private:
    String _mqttServer;
    int _mqttPort;
    String _deviceId;
    
    WiFiClient wifiClient;
    PubSubClient* mqttClient;
};


#endif /* __MQTT_H__ */
