

#include <twr_chester_x0.h>

typedef enum
{
    TWR_CHESTER_X0_ON4 = 0,
    TWR_CHESTER_X0_CL4 = 1,
    TWR_CHESTER_X0_PU4 = 2,
    TWR_CHESTER_X0_ON3 = 3,

    TWR_CHESTER_X0_PD4 = 4,
    TWR_CHESTER_X0_PU3 = 5,
    TWR_CHESTER_X0_CL3 = 6,
    TWR_CHESTER_X0_PD3 = 7,

    TWR_CHESTER_X0_PU2 = 8,
    TWR_CHESTER_X0_CL2 = 9,
    TWR_CHESTER_X0_ON2 = 10,
    TWR_CHESTER_X0_ON1 = 11,

    TWR_CHESTER_X0_PD2 = 12,
    TWR_CHESTER_X0_PU1 = 13,
    TWR_CHESTER_X0_CL1 = 14,
    TWR_CHESTER_X0_PD1 = 15

} _twr_chester_x0_channel_map_t;

typedef enum
{
    TWR_CHESTER_X0_REGISTER_INPUT_PORT_0 = 0x00,
    TWR_CHESTER_X0_REGISTER_INPUT_PORT_1 = 0x01,
    TWR_CHESTER_X0_REGISTER_OUTPUT_PORT_0 = 0x02,
    TWR_CHESTER_X0_REGISTER_OUTPUT_PORT_1 = 0x03,
    TWR_CHESTER_X0_REGISTER_POLARITY_INVERSION_PORT_0 = 0x04,
    TWR_CHESTER_X0_REGISTER_POLARITY_INVERSION_PORT_1 = 0x05,
    TWR_CHESTER_X0_REGISTER_CONFIGURATION_PORT_0 = 0x06,
    TWR_CHESTER_X0_REGISTER_CONFIGURATION_PORT_1 = 0x07,

} _twr_chester_x0_registers_t;

static const uint8_t _lookup[4][4] = {
        {TWR_CHESTER_X0_PU1, TWR_CHESTER_X0_ON1, TWR_CHESTER_X0_CL1, TWR_CHESTER_X0_PD1},
        {TWR_CHESTER_X0_PU2, TWR_CHESTER_X0_ON2, TWR_CHESTER_X0_CL2, TWR_CHESTER_X0_PD2},
        {TWR_CHESTER_X0_PU3, TWR_CHESTER_X0_ON3, TWR_CHESTER_X0_CL3, TWR_CHESTER_X0_PD3},
        {TWR_CHESTER_X0_PU4, TWR_CHESTER_X0_ON4, TWR_CHESTER_X0_CL4, TWR_CHESTER_X0_PD4},
};

void twr_chester_x0_init(twr_chester_x0_t *self, twr_i2c_channel_t i2c_channel, uint8_t i2c_address)
{
    memset(self, 0, sizeof(*self));

    // All inputs on power-up
    twr_i2c_memory_write_8b(self->_i2c_channel, self->_i2c_address, TWR_CHESTER_X0_REGISTER_CONFIGURATION_PORT_0, 0xff);
    twr_i2c_memory_write_8b(self->_i2c_channel, self->_i2c_address, TWR_CHESTER_X0_REGISTER_CONFIGURATION_PORT_1, 0xff);

    twr_i2c_memory_write_8b(self->_i2c_channel, self->_i2c_address, TWR_CHESTER_X0_REGISTER_OUTPUT_PORT_0, 0xff);
    twr_i2c_memory_write_8b(self->_i2c_channel, self->_i2c_address, TWR_CHESTER_X0_REGISTER_OUTPUT_PORT_1, 0xff);

    self->_i2c_channel = i2c_channel;
    self->_i2c_address = i2c_address;

    twr_i2c_init(self->_i2c_channel, TWR_I2C_SPEED_400_KHZ);

}

void twr_chester_x0_channel_configure(twr_chester_x0_t *self, twr_chester_x0_channel_t channel, twr_chester_x0_channel_config_t config)
{

}

/*
void twr_x0_set_event_handler(twr_x0_t *self, void (*event_handler)(twr_button_t *, twr_button_event_t, void *), void *event_param)
{
    self->_event_handler = event_handler;
    self->_event_param = event_param;

    if (event_handler == NULL)
    {
    }
    else
    {
    }
}
*/
