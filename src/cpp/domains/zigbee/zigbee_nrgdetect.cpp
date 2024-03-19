#include <zigbee/nrgdetect.hpp>

using namespace whad::zigbee;

/**
 * @brief   Parse a message as a EnergyDetect message.
 */

EnergyDetect::EnergyDetect(ZigbeeMsg &message) : ZigbeeMsg(message)
{
    this->unpack();
}


/**
 * @brief       EnergyDetect message constructor.
 * 
 * @param[in]   channel         Specify the ZigBee channel to detect
 **/

EnergyDetect::EnergyDetect(uint32_t channel) : ZigbeeMsg()
{
    /* Save channel. */
    m_channel = channel;
}


/**
 * @brief   Pack parameters into a ZigbeeMsg object
 */

void EnergyDetect::pack()
{
    whad_zigbee_energy_detect(
        this->getMessage(),
        m_channel
    );
}


/**
 * @brief   Extract parameters from a ZigbeeMsg
 */

void EnergyDetect::unpack()
{
    whad_result_t result;
    uint32_t channel;

    result = whad_zigbee_energy_detect_parse(
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
 * @brief   Retrieve the zigbee channel to detect
 * 
 * @retval  Channel number
 */

uint32_t EnergyDetect::getChannel()
{
    return m_channel;
}
