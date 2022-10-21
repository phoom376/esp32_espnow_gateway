#include <sent_recv.h>
#include <espnow.h>

// HardwareSerial RECV(2);
// HardwareSerial SENT(1);
HardwareSerial SENT_RECV(1);

EspNow en_sent;

typedef struct _recv_struct
{
    char _payload[200];
} _recv_struct;

recv_struct _recv_message;

void sent_recv_init()
{
    SENT_RECV.begin(115200, SERIAL_8N1, SENT_RECV_RX_PIN, SENT_RECV_TX_PIN);
}

void sent_serial(char *recv)
{
    DynamicJsonDocument sent(250);

    DeserializationError err = deserializeJson(sent, recv);

    // String txt = String(_payload);
    // SENT_RECV.println(txt);
    serializeJson(sent, SENT_RECV);
    SENT_RECV.println();
    Serial.print("SENT SERIAL :");
    serializeJson(sent, Serial);
}

void recv_serial()
{
    while (SENT_RECV.available())
    {
        strcpy(_recv_message._payload, SENT_RECV.readString().c_str());

        en_sent.sent_data(BOARD_CAST_ADDRESS, _recv_message);
    }
}