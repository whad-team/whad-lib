#include <zigbee/enddevice.hpp>

using namespace whad::zigbee;

/**
 * @brief   Parse a message as a EndDeviceMode message.
 */

EndDeviceMode::EndDeviceMode(ZigbeeMsg &message) : ZigbeeMsg(message)
{
    this->unpack();
}


/**
 * @brief       EndDeviceMode message constructor.
 * 
 * @param[in]   channel         Specify the ZigBee channel to use
 **/

EndDeviceMode::EndDeviceMode(uint32_t channel) : ZigbeeMsg()
{
    /* Save channel. */
    m_channel = channel;
}


/**
 * @brief   Pack parameters into a ZigbeeMsg object
 */

void EndDeviceMode::pack()
{
    whad_zigbee_end_device_mode(
        this->getMessage(),
        m_channel
    );
}


/**
 * @brief   Extract parameters from a ZigbeeMsg
 */

void EndDeviceMode::unpack()
{
    whad_result_t result;
    uint32_t channel;

    result = whad_zigbee_end_device_mode_parse(
        this->getMessage(),
        &channel
    );

    if (result == WHAD_ERROR)
    {
        /* Error occured during parsing. */
        throw WhadMessageParsingError();
    }
    else
    {
        /* Save parameters. */
        m_channel = channel;
    }
}


/**
 * @brief   Retrieve the zigbee channel to use
 * 
 * @retval  Channel number
 */

uint32_t EndDeviceMode::getChannel()
{
    return m_channel;
}
