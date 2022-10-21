#include <Arduino.h>
#include <global.h>
#include <sent_recv.h>

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);
typedef struct recv_struct
{
    char _payload[200];
} recv_struct;

class EspNow
{

private:
    esp_now_peer_info_t peerInfo;

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

    void sent_data(uint8_t *_address, recv_struct _message)
    {
        esp_err_t result = esp_now_send(_address, (uint8_t *)&_message, sizeof(_message));

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
