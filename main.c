#include "pico/stdlib.h"
#include "stdio.h"
#include "hardware/flash.h"

#define LED_PIN          PICO_DEFAULT_LED_PIN
#define TOGGLE_TIME      2000
#define PAGE_SIZE        256 
#define NVS_SIZE         4096
#define MSG_ID_WRITE_START   (PICO_FLASH_SIZE_BYTES - NVS_SIZE)
#define MSG_ID_READ_START    (MSG_ID_WRITE_START + XIP_BASE)


void Flash_WriteMsgID(uint32_t msg_id)
{
    flash_range_erase(MSG_ID_WRITE_START,NVS_SIZE);
    flash_range_program(MSG_ID_WRITE_START,(const uint8_t*)msg_id,PAGE_SIZE);
}

uint8_t Flash_ReadMsgID(void)
{   
    uint8_t* id = (uint8_t*)(MSG_ID_READ_START);
    return *id;
}
 
int main() 
{
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    Flash_WriteMsgID(1);
    sleep_ms(500);
    uint8_t id = Flash_ReadMsgID();

    while (true) {
        printf("%d", id);
        gpio_put(LED_PIN, 1);
        sleep_ms(TOGGLE_TIME);
        gpio_put(LED_PIN, 0);
        sleep_ms(TOGGLE_TIME);
    }
}
