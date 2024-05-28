#include <dot15d4/coord.hpp>

using namespace whad::dot15d4;

/**
 * @brief   Parse a message as a CoordMode message.
 */

CoordMode::CoordMode(Dot15d4Msg &message) : Dot15d4Msg(message)
{
    this->unpack();
}


/**
 * @brief       CoordMode message constructor.
 * 
 * @param[in]   channel         Specify the ZigBee channel to use
 **/

CoordMode::CoordMode(uint32_t channel) : Dot15d4Msg()
{
    /* Save channel. */
    m_channel = channel;
}


/**
 * @brief   Pack parameters into a Dot15d4Msg object
 */

void CoordMode::pack()
{
    whad_dot15d4_coord_mode(
        this->getMessage(),
        m_channel
    );
}


/**
 * @brief   Extract parameters from a Dot15d4Msg
 */

void CoordMode::unpack()
{
    whad_result_t result;
    uint32_t channel;

    result = whad_dot15d4_coord_mode_parse(
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

uint32_t CoordMode::getChannel()
{
    return m_channel;
}
