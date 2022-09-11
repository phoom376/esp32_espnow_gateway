#include <Arduino.h>
#include <global.h>
#include <sent_recv.h>
#include <esp_now.h>
#include <esp_wifi.h>

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    Serial.print("\r\nLast Packet Send Status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    memcpy(&PAYLOAD, incomingData, sizeof(PAYLOAD));
    Serial.print("Bytes received: ");
    Serial.println(len);
    Serial.print("PAYLOAD: ");
    Serial.println(PAYLOAD);
    Serial.println();
    sent_serial(PAYLOAD);
}


class EspNow
{
public:
    void init()
    {
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
    }

    void sent_data(uint8_t *_address, char *_message)
    {

        char _tmp_message[4096];
        strcpy(_tmp_message, _message);

        esp_err_t result = esp_now_send(_address, (uint8_t *)&_tmp_message, sizeof(_tmp_message));

        if (result == ESP_OK)
        {
            Serial.println("Sent with success");
        }
        else
        {
            Serial.println("Error sending the data");
        }
    }
};

// void espnow_init();
