#include <vTask.h>

void serial_com_sent(void *pvParameters);
void serial_com_recv(void *pvParameters);

void vTask_init()
{
    xTaskCreatePinnedToCore(serial_com_sent, "serial_com_sent", 1024 * 2, NULL, tskIDLE_PRIORITY - 5, NULL, 0);
    xTaskCreatePinnedToCore(serial_com_recv, "serial_com_recv", 1024 * 2, NULL, tskIDLE_PRIORITY - 5, NULL, 0);
}

void serial_com_sent(void *pvParameters)
{
    while (true)
    {
        char *t = createTest().c_str();
        sent_serial(t);
        Serial.println("Hello World Sent");
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void serial_com_recv(void *pvParameters)
{
    while (true)
    {
        recv_serial();
        // Serial.println("Hello World Recv");
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

String createTest()
{
    String txt;

    txt += "{";
    txt += "\'id\":";
    txt += 16;
    txt += ",";
    txt += "\"n1\":";
    txt += String(random(0, 100));
    txt += ",";
    txt += "\"n2\":";
    txt += String(random(100, 200));
    txt += "}";
    return txt;
}