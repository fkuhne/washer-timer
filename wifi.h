#ifndef __WIFI_H__
#define __WIFI_H__

#if defined(ESP8266)
# include <ESP8266WiFi.h>
#elif defined(ESP32)
# include <WiFi.h>
#endif
#include <WiFiClient.h>

class WFclass
{
  public:
    WFclass();
    /* Inicia a conexão do cliente Wi-Fi com a rede disponível no local. */
    void connect();
    void connectFromList();
    /* Atenção: este método returna sempre true, então não pode ser usado
     *  pra identificar uma desconexão do wifi. */
    bool isConnected() { return WiFi.isConnected(); }
    
  private:
    const char* c_ssid = "";
    const char* c_pass = "";


    int status;
};

#endif /* __WIFI_H__ */
