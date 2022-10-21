#include <espnow.h>
#include <iostream>
#include <sstream>

typedef struct struct_message
{
    char _payload[250];
} struct_message;

String mac_regis[30];

struct_message message;
String getValue(String data, char separator, int index);
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    Serial.print("\r\nLast Packet Send Status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    memcpy(&message, incomingData, sizeof(message));
    // stpcpy(PAYLOAD, message._payload);
    Serial.print("Bytes received: ");
    Serial.println(len);
    Serial.print("PAYLOAD: ");
    Serial.println(message._payload);
    Serial.println();

    char _tmp_payload[250];

    stpcpy(_tmp_payload, message._payload);

    DynamicJsonDocument doc(250);

    DeserializationError err = deserializeJson(doc, _tmp_payload);

    if (err)
    {
        Serial.println("Receive failed");
    }

    mac_regis[10] = "E8:DB:84:E0:E7:E5";

    sent_serial(message._payload);

    String mac_add = doc["mac_address"];

    Serial.print("MAC : ");
    Serial.println(mac_add);
}

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = {0, -1};
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++)
    {
        if (data.charAt(i) == separator || i == maxIndex)
        {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i + 1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}