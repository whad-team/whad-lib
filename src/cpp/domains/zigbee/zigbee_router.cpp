#include <zigbee/router.hpp>

using namespace whad::zigbee;

/**
 * @brief   Parse a message as a RouterMode message.
 */

RouterMode::RouterMode(ZigbeeMsg &message) : ZigbeeMsg(message)
{
    this->unpack();
}


/**
 * @brief       RouterMode message constructor.
 * 
 * @param[in]   channel         Specify the ZigBee channel to use
 **/

RouterMode::RouterMode(uint32_t channel) : ZigbeeMsg()
{
    /* Save channel. */
    m_channel = channel;
}


/**
 * @brief   Pack parameters into a ZigbeeMsg object
 */

void RouterMode::pack()
{
    whad_zigbee_router_mode(
        this->getMessage(),
        m_channel
    );
}


/**
 * @brief   Extract parameters from a ZigbeeMsg
 */

void RouterMode::unpack()
{
    whad_result_t result;
    uint32_t channel;

    result = whad_zigbee_router_mode_parse(
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

uint32_t RouterMode::getChannel()
{
    return m_channel;
}
