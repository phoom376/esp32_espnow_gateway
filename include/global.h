#include <Arduino.h>
#include <esp_now.h>
#include <esp_wifi.h>

#define SENT_RX_PIN 16
#define SENT_TX_PIN 17

#define RECV_RX_PIN 26
#define RECV_TX_PIN 27

extern char RECV_MESSAGE[4096], SENT_MESSAGE[4096], PAYLOAD[4096];
extern char MESSAGE[4096];
extern uint16_t ID;
extern float SCL_TANK, BCL_TANK, EC, EC_TEMP, PH, PH_TEMP, TEMPERATURE, HUMIDITY;
extern bool EC_SENSOR_INPUT, PH_SENSOR_INPUT, ULTRASONIC_SENSOR_INPUT, MESSAGE_STATUS;
extern uint8_t BOARD_CAST_ADDRESS[];