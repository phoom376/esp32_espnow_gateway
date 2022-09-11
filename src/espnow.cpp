#include <espnow.h>

typedef struct struct_message
{
    char message[200];
    int id;
    bool status;
} struct_message;

struct_message message;

void espnow_init()
{

    // if (esp_now_init() != ESP_OK)
    // {
    //     Serial.println("Error initializing ESP-NOW");
    // }

    // esp_now_register_send_cb(OnDataSent);
    // esp_now_register_recv_cb(OnDataRecv);

    // memcpy(peerInfo.peer_addr, BOARD_CAST_ADDRESS, 6);
    // peerInfo.channel = 0;
    // peerInfo.encrypt = false;

    // if (esp_now_add_peer(&peerInfo) != ESP_OK)
    // {
    //     Serial.println("Failed to add peer");
    // }
}

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
