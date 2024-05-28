#include <dot15d4/nrgdetect.hpp>

using namespace whad::dot15d4;

/**
 * @brief   Parse a message as a EnergyDetect message.
 */

EnergyDetect::EnergyDetect(Dot15d4Msg &message) : Dot15d4Msg(message)
{
    this->unpack();
}


/**
 * @brief       EnergyDetect message constructor.
 * 
 * @param[in]   channel         Specify the ZigBee channel to detect
 **/

EnergyDetect::EnergyDetect(uint32_t channel) : Dot15d4Msg()
{
    /* Save channel. */
    m_channel = channel;
}


/**
 * @brief   Pack parameters into a Dot15d4Msg object
 */

void EnergyDetect::pack()
{
    whad_dot15d4_energy_detect(
        this->getMessage(),
        m_channel
    );
}


/**
 * @brief   Extract parameters from a Dot15d4Msg
 */

void EnergyDetect::unpack()
{
    whad_result_t result;
    uint32_t channel;

    result = whad_dot15d4_energy_detect_parse(
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
 * @brief   Retrieve the dot15d4 channel to detect
 * 
 * @retval  Channel number
 */

uint32_t EnergyDetect::getChannel()
{
    return m_channel;
}
