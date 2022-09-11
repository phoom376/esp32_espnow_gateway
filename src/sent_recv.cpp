#include <sent_recv.h>
#include <espnow.h>

HardwareSerial RECV(1);
HardwareSerial SENT(2);
EspNow en;

typedef struct recv_struct
{
    char payload[4096];
} recv_struct;

recv_struct recv_message;

void sent_recv_init()
{
    SENT.begin(115200, SERIAL_8N1, SENT_TX_PIN, SENT_RX_PIN);
    RECV.begin(115200, SERIAL_8N1, RECV_TX_PIN, RECV_RX_PIN);
}

void sent_serial(char *_payload)
{

    SENT.print(_payload);
    Serial.print("SENT SERIAL :");
    Serial.println(_payload);
    SENT.flush();
    Serial.flush();
}

void recv_serial()
{
    while (RECV.available())
    {
        strcpy(RECV_MESSAGE, RECV.readString().c_str());

        en.sent_data(BOARD_CAST_ADDRESS, RECV_MESSAGE);
    }
}