#include <zigbee/sniff.hpp>

using namespace whad::zigbee;

/**
 * @brief   Parse a message as a SniffMode message.
 */

SniffMode::SniffMode(ZigbeeMsg &message) : ZigbeeMsg(message)
{
    this->unpack();
}


/**
 * @brief       SniffMode message constructor.
 * 
 * @param[in]   channel         Specify the ZigBee channel to sniff
 **/

SniffMode::SniffMode(uint32_t channel) : ZigbeeMsg()
{
    /* Save channel. */
    m_channel = channel;
}


/**
 * @brief   Pack parameters into a ZigbeeMsg object
 */

void SniffMode::pack()
{
    whad_zigbee_sniff(
        this->getMessage(),
        m_channel
    );
}


/**
 * @brief   Extract parameters from a ZigbeeMsg
 */

void SniffMode::unpack()
{
    whad_result_t result;
    uint32_t channel;

    result = whad_zigbee_sniff_parse(
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
 * @brief   Retrieve the zigbee channel to sniff
 * 
 * @retval  Channel number
 */

uint32_t SniffMode::getChannel()
{
    return m_channel;
}
