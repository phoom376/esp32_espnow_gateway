#include <Arduino.h>
#include <global.h>
#include <espnow.h>
#include <vTask.h>
#include <WiFi.h>

EspNow en;

void setup()
{
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  // espnow_init();

  en.init();


  sent_recv_init();

  vTask_init();
  // put your setup code here, to run once:
}

void loop()
{
  // put your main code here, to run repeatedly:
}