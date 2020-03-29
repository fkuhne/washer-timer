#include "util.h"

void printBanner()
{
  Serial.println();
  Serial.println("Platform: " + String(PLATFORM));
  Serial.println("Application name: " + String(appName));
  Serial.println("Version " + String(version) + ", compiled at " + String(compileDate));
  Serial.println();
}

void blink_led(int led_pin, int repeat)
{
  int i = 0;
  while(++i <= repeat)
  {
    digitalWrite(led_pin, LOW);
    delay(50);
    digitalWrite(led_pin, HIGH);
    delay(50);
  }
}
