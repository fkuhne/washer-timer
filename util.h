#ifndef __UTIL_H__
#define __UTIL_H__

#include "Arduino.h"

const char appName[] = "Hand Sanitizer";
const char compileDate[] = __DATE__ " " __TIME__;
const char version[] = "1.0-0";

#if defined(ESP8266)
# define FLASH_PIN 0
const char PLATFORM[] = "ESP8266";
#elif defined(ESP32)
# define FLASH_PIN 0
# define LED_BUILTIN 2
const char PLATFORM[] = "ESP32";
#endif

void printBanner();
void blink_led(int led_pin, int repeat);

#endif /* __UTIL_H__ */
