#ifndef _TWR_CHESTER_X0_H
#define _TWR_CHESTER_X0_H

#include <twr_gpio.h>
#include <twr_i2c.h>

//! @addtogroup twr_x0 twr_x0
//! @brief Driver for CHESTER-X0
//! @{

//! @brief CHESTER-X0 instance

typedef struct twr_chester_x0_t twr_chester_x0_t;


//! @brief I/O channels

typedef enum
{
    //! @brief GPIO channel P0, A0, TXD0
    TWR_CHESTER_X0_CHANNEL1 = 0,

    //! @brief GPIO channel P1, A1, RXD0
    TWR_CHESTER_X0_CHANNEL2 = 1,

    //! @brief GPIO channel P2, A2, TXD1
    TWR_CHESTER_X0_CHANNEL3 = 2,

    //! @brief GPIO channel P3, A3, RXD1
    TWR_CHESTER_X0_CHANNEL4 = 3,

} twr_chester_x0_channel_t;

typedef enum
{
    //! @brief GPIO channel P0, A0, TXD0
    TWR_CHESTER_X0_CHANNEL_CONFIG_PULLUP = 0x01,

    //! @brief GPIO channel P1, A1, RXD0
    TWR_CHESTER_X0_CHANNEL_CONFIG_POWER = 0x02,

    //! @brief GPIO channel P2, A2, TXD1
    TWR_CHESTER_X0_CHANNEL_CONFIG_4_20_MA = 0x04,

    //! @brief GPIO channel P3, A3, RXD1
    TWR_CHESTER_X0_CHANNEL_CONFIG_DIVIDER = 0x08,

} twr_chester_x0_channel_config_t;

//! @cond

struct twr_chester_x0_t
{
    twr_i2c_channel_t _i2c_channel;
    uint8_t _i2c_address;

    twr_chester_x0_channel_config_t _channel[4];

    //void (*_event_handler)(twr_x0_t *, twr_button_event_t, void *);
    //void *_event_param;

};

//! @endcond

//! @brief Initialize CHESTER-X0
//! @param[in] self Instance
//! @param[in] gpio_channel GPIO channel button is connected to
//! @param[in] gpio_pull GPIO pull-up/pull-down setting
//! @param[in] idle_state GPIO pin idle state (when button is not pressed)

void twr_chester_x0_init(twr_chester_x0_t *self, twr_i2c_channel_t i2c_channel, uint8_t i2c_address);

//! @brief Set callback function
//! @param[in] self Instance
//! @param[in] event_handler Function address
//! @param[in] event_param Optional event parameter (can be NULL)

//void twr_chester_x0_set_event_handler(twr_x0_t *self, void (*event_handler)(twr_button_t *, twr_button_event_t, void *), void *event_param);


//! @}

#endif // _TWR_CHESTER_X0_H
