#include <dot15d4/enddevice.hpp>

using namespace whad::dot15d4;

/**
 * @brief   Parse a message as a EndDeviceMode message.
 */

EndDeviceMode::EndDeviceMode(Dot15d4Msg &message) : Dot15d4Msg(message)
{
    this->unpack();
}


/**
 * @brief       EndDeviceMode message constructor.
 * 
 * @param[in]   channel         Specify the ZigBee channel to use
 **/

EndDeviceMode::EndDeviceMode(uint32_t channel) : Dot15d4Msg()
{
    /* Save channel. */
    m_channel = channel;
}


/**
 * @brief   Pack parameters into a Dot15d4Msg object
 */

void EndDeviceMode::pack()
{
    whad_dot15d4_end_device_mode(
        this->getMessage(),
        m_channel
    );
}


/**
 * @brief   Extract parameters from a Dot15d4Msg
 */

void EndDeviceMode::unpack()
{
    whad_result_t result;
    uint32_t channel;

    result = whad_dot15d4_end_device_mode_parse(
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
 * @brief   Retrieve the dot15d4 channel to use
 * 
 * @retval  Channel number
 */

uint32_t EndDeviceMode::getChannel()
{
    return m_channel;
}
