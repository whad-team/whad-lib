#include <dot15d4/sniff.hpp>

using namespace whad::dot15d4;

/**
 * @brief   Parse a message as a SniffMode message.
 */

SniffMode::SniffMode(Dot15d4Msg &message) : Dot15d4Msg(message)
{
    this->unpack();
}


/**
 * @brief       SniffMode message constructor.
 * 
 * @param[in]   channel         Specify the ZigBee channel to sniff
 **/

SniffMode::SniffMode(uint32_t channel) : Dot15d4Msg()
{
    /* Save channel. */
    m_channel = channel;
}


/**
 * @brief   Pack parameters into a Dot15d4Msg object
 */

void SniffMode::pack()
{
    whad_dot15d4_sniff(
        this->getMessage(),
        m_channel
    );
}


/**
 * @brief   Extract parameters from a Dot15d4Msg
 */

void SniffMode::unpack()
{
    whad_result_t result;
    uint32_t channel;

    result = whad_dot15d4_sniff_parse(
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
 * @brief   Retrieve the dot15d4 channel to sniff
 * 
 * @retval  Channel number
 */

uint32_t SniffMode::getChannel()
{
    return m_channel;
}
