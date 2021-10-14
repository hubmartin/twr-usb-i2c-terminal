// Tower Kit documentation https://tower.hardwario.com/
// SDK API description https://sdk.hardwario.com/
// Forum https://forum.hardwario.com/

#include <application.h>
#include "twr_chester_x0.h"

// LED instance
twr_led_t led;

// Button instance
twr_button_t button;

twr_chester_x0_t x0;

// Button event callback
void button_event_handler(twr_button_t *self, twr_button_event_t event, void *event_param)
{

    // Check event source
    if (event == BC_BUTTON_EVENT_CLICK)
    {
        // Toggle LED pin state
        twr_led_pulse(&led, 100);

    }
}

bool atci_i2c_memory_read(twr_atci_param_t *param)
{
    char str_address[16];
    char str_memory_register[16];
    char str_length[16];

    uint32_t address;
    uint32_t memory_register;
    uint32_t length;

    static uint8_t buffer[512];

    if (!twr_atci_get_string(param, str_address, sizeof(str_address)))
    {
        return false;
    }

    if (!twr_atci_is_comma(param))
    {
        return false;
    }

    if (!twr_atci_get_string(param, str_memory_register, sizeof(str_memory_register)))
    {
        return false;
    }

    if (!twr_atci_is_comma(param))
    {
        return false;
    }

    if (!twr_atci_get_string(param, str_length, sizeof(str_length)))
    {
        return false;
    }

    address = (uint32_t)strtol(str_address, NULL, 0);
    memory_register = (uint32_t)strtol(str_memory_register, NULL, 0);
    length = (uint32_t)strtol(str_length, NULL, 0);

    twr_atci_printf("Addr 0x%02x, reg 0x%02x, len %d\r\n", address, memory_register, length);

    twr_i2c_memory_transfer_t transfer;
    transfer.device_address = address;
    transfer.memory_address = memory_register;
    transfer.buffer = buffer;
    transfer.length = length;

    bool ret = twr_i2c_memory_read(TWR_I2C_I2C0, &transfer);

    if(!ret)
    {
        return false;
    }

    twr_atci_printf("$I2CMR: ");

    for (int i = 0; i < length; i++)
    {
        twr_atci_printf("%02X", buffer[i]);

        if (i != length - 1)
        {
            twr_atci_printf(",");
        }
    }

    twr_atci_printf("\r\n");

    return ret;
}

bool atci_i2c_memory_write(twr_atci_param_t *param)
{

    char str_address[16];
    char str_memory_register[16];
    char str_write_data[16];

    uint32_t address;
    uint32_t memory_register;
    uint8_t write_data;


    if (!twr_atci_get_string(param, str_address, sizeof(str_address)))
    {
        return false;
    }

    if (!twr_atci_is_comma(param))
    {
        return false;
    }

    if (!twr_atci_get_string(param, str_memory_register, sizeof(str_memory_register)))
    {
        return false;
    }

    if (!twr_atci_is_comma(param))
    {
        return false;
    }

    if (!twr_atci_get_string(param, str_write_data, sizeof(str_write_data)))
    {
        return false;
    }

    address = (uint32_t)strtol(str_address, NULL, 0);
    memory_register = (uint32_t)strtol(str_memory_register, NULL, 0);
    write_data = (uint8_t)strtol(str_write_data, NULL, 0);

    //twr_atci_printf("Addr 0x%02x, reg 0x%02x, write 0x%02x\r\n", address, memory_register, write_data);

    twr_i2c_memory_transfer_t transfer;
    transfer.device_address = address;
    transfer.memory_address = memory_register;
    transfer.buffer = &write_data;
    transfer.length = 1;

    bool ret = twr_i2c_memory_write(TWR_I2C_I2C0, &transfer);

    return ret;

}


bool atci_i2c_scan(void)
{

    uint8_t dummy;
    bool flag_comma = false;

    twr_i2c_memory_transfer_t transfer;
    transfer.memory_address = 0;
    transfer.buffer = &dummy;
    transfer.length = 1;

    twr_atci_printf("$SCAN: ");


    for (int i = 0; i < 127; i++)
    {
        transfer.device_address = i;
        bool ret = twr_i2c_memory_read(TWR_I2C_I2C0, &transfer);

        if (ret)
        {
            if (flag_comma)
            {
                twr_atci_printf(",");
            }

            twr_atci_printf("0x%02x", transfer.device_address);
            flag_comma = true;
        }

    }

    twr_atci_printf("\r\n");

    return true;
}

bool atci_gpio_read(void)
{
    twr_adc_init();

    uint16_t analog[4];

    twr_adc_get_value(TWR_ADC_CHANNEL_A2, &analog[0]);
    twr_adc_get_value(TWR_ADC_CHANNEL_A3, &analog[1]);
    twr_adc_get_value(TWR_ADC_CHANNEL_A4, &analog[2]);
    twr_adc_get_value(TWR_ADC_CHANNEL_A5, &analog[3]);

    twr_atci_printf("$ANALOG: %d, %d, %d, %d\r\n", analog[0], analog[1], analog[2], analog[3]);

    return true;
}

// Application initialization function which is called once after boot
void application_init(void)
{
    // Initialize logging
    twr_log_init(TWR_LOG_LEVEL_DUMP, TWR_LOG_TIMESTAMP_ABS);

    // Initialize LED
    twr_led_init(&led, TWR_GPIO_LED, false, 0);
    twr_led_pulse(&led, 2000);

    // Initialize button
    twr_button_init(&button, TWR_GPIO_BUTTON, TWR_GPIO_PULL_DOWN, 0);
    twr_button_set_event_handler(&button, button_event_handler, NULL);

    static const twr_atci_command_t commands[] = {
        { "$MR", NULL, atci_i2c_memory_read, NULL, NULL, "I2C memory read"},
        { "$MW", NULL, atci_i2c_memory_write, NULL, NULL, "I2C memory write"},
        { "$SCAN", atci_i2c_scan, NULL, NULL, NULL, "Scan I2C bus"},
        { "$GR", atci_gpio_read, NULL, NULL, NULL, "GPIO read"},
        //{ "$PING", NULL, atci_i2c_ping, NULL, NULL, "Get/set config parameters"},
        TWR_ATCI_COMMAND_CLAC,
        TWR_ATCI_COMMAND_HELP
    };
    twr_atci_init(commands, TWR_ATCI_COMMANDS_LENGTH(commands));

    // Since we do not use any sensor, we need initialize bus manually
    //twr_i2c_init(TWR_I2C_I2C0, TWR_I2C_SPEED_400_KHZ);

    twr_chester_x0_init(&x0, TWR_I2C_I2C0, 0x20);

}

/*

X0 CH4 +5V

AT$MW="0x20","0x06","0xFE"

CH1 Current load
AT$MW="0x20","0x07","0xBF"
AT$MW="0x20","0x03","0xFF"

CH1 current load + delic
AT$MW="0x20","0x07","0x3F"
AT$MW="0x20","0x03","0xFF"

CH1 divider mereni napeti
AT$MW="0x20","0x07","0x7F"
AT$MW="0x20","0x03","0xFF"


CH1 power +5V
AT$MW="0x20","0x07","0xF7"
AT$MW="0x20","0x03","0xF7"

(TODO zapnout taky dělič pro jistotu)
AT$MW="0x20","0x07","0x77"
AT$MW="0x20","0x03","0xF7"

*/
