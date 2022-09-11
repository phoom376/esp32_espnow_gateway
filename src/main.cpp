#include <Arduino.h>
#include <global.h>
#include <espnow.h>
#include <vTask.h>
#include <WiFi.h>

esp_now_peer_info_t peerInfo;

void setup()
{
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  // espnow_init();

  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
  }

  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);

  memcpy(peerInfo.peer_addr, BOARD_CAST_ADDRESS, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
  }

  sent_recv_init();

  vTask_init();
  // put your setup code here, to run once:
}

void loop()
{
  // put your main code here, to run repeatedly:
}