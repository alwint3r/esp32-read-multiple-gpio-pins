#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

inline bool is_pin_set(uint64_t data, uint64_t pin)
{
    return (data & pin) != 0;
}

void app_main()
{
    gpio_config_t io_config =
    {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_INPUT,
        .pin_bit_mask = GPIO_SEL_0 | GPIO_SEL_4,
    };

    ESP_ERROR_CHECK(gpio_config(&io_config));

    while (1)
    {
        uint64_t io_data = REG_READ(GPIO_IN_REG);
        printf("gpio in: %llu\r\n", io_data);

        printf("is IO0 set? %d\r\n", is_pin_set(io_data, GPIO_SEL_0));
        printf("is IO4 set? %d\r\n", is_pin_set(io_data, GPIO_SEL_4));
        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}