#include "wifi.h"

/* Contrutor da classe. Não faz nada, só instancia o objeto */
WFclass::WFclass() {}

/* Inicia a conexão do cliente Wi-Fi com a rede disponível no local. */
void WFclass::connect()
{
  Serial.print("Conectando na rede: ");
  Serial.print(c_ssid);

  /* Inicia o cliente Wi-Fi, conectando à rede especificada, de acordo com
       as credenciais de acessi (SSID e senha). */
  status = WiFi.begin(c_ssid, c_pass);

  /* O ESP tende a demorar para conectar em redes instáveis. Quando isto
       ocorre, a melhor alternativa é causar um reset na placa e tentar
       novamente. Isto é o que o código abaixo faz. */
  for (int count = 0; count <= 30; count++)
  {
    if (WiFi.status() == WL_CONNECTED)
      break;

    delay(1000);
    Serial.print(".");

    if (count == 30)
    {
      Serial.println(" desisto :(");
      ESP.restart();
    }
  }

  Serial.println(" conectado!");
  Serial.print(" MAC: ");
  Serial.println(WiFi.macAddress());
  Serial.print(" IP: ");
  Serial.println(WiFi.localIP());
  Serial.print(" Subrede: ");
  Serial.println(WiFi.subnetMask());
  Serial.print(" Gateway: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print(" DNS: ");
  Serial.println(WiFi.dnsIP());
  Serial.print(" Canal: ");
  Serial.println(WiFi.channel());
  Serial.print(" Status: ");
  Serial.println(WiFi.status());
  Serial.println();
}

struct wifinetworks {
  String ssid;
  String pass;
} wifiNetworks[] = {
  {"YOUR-SSID", "YOUR-PASSWORD"}
};

/* Tenta conectar com alguma rede no local, a partir de uma lista pré-definida. */
void WFclass::connectFromList()
{
  int wifiListSize = sizeof(wifiNetworks) / sizeof(wifiNetworks[0]);

  for (int i = 0; i < wifiListSize; i++)
  {
    Serial.print("Tentando conectar na rede " + wifiNetworks[i].ssid);

    status = WiFi.begin(wifiNetworks[i].ssid.c_str(), wifiNetworks[i].pass.c_str());
    for (int count = 0; count <= 240; count++)
    {
      if (WiFi.status() == WL_CONNECTED)
      {
        Serial.println(" conectado!");
        Serial.print(" MAC: ");
        Serial.println(WiFi.macAddress());
        Serial.print(" IP: ");
        Serial.println(WiFi.localIP());
        Serial.print(" Subrede: ");
        Serial.println(WiFi.subnetMask());
        Serial.print(" Gateway: ");
        Serial.println(WiFi.gatewayIP());
        Serial.print(" DNS: ");
        Serial.println(WiFi.dnsIP());
        Serial.print(" Canal: ");
        Serial.println(WiFi.channel());
        Serial.print(" Status: ");
        Serial.println(WiFi.status());
        Serial.println();

        digitalWrite(LED_BUILTIN, HIGH);

        return;
      }

      delay(250);
      digitalWrite(LED_BUILTIN, HIGH - digitalRead(LED_BUILTIN));
      Serial.print(".");
    }
    Serial.println();
  }

  Serial.println(" desisto :(");
  ESP.restart();
}
