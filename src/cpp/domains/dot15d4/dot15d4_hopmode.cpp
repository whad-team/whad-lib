#include <dot15d4/hopmode.hpp>

using namespace whad::dot15d4;

/**
 * @brief   Parse a message as a CoordMode message.
 */

HopMode::HopMode(Dot15d4Msg &message) : Dot15d4Msg(message)
{
    this->unpack();
}


/**
 * @brief       CoordMode message constructor.
 * 
 * @param[in]   channel         Specify the ZigBee channel to use
 **/

HopMode::HopMode(bool hopping) : Dot15d4Msg()
{
    /* Save the mode. */
    m_hopping = hopping;
}


/**
 * @brief   Pack parameters into a Dot15d4Msg object
 */

void HopMode::pack()
{
    whad_dot15d4_coord_mode(
        this->getMessage(),
        m_hopping
    );
}


/**
 * @brief   Extract parameters from a Dot15d4Msg
 */

void HopMode::unpack()
{
    whad_result_t result;
    bool hopping = false;

    result = whad_dot15d4_enable_hopping(
        this->getMessage(),
        &hopping
    );

    if (result == WHAD_ERROR)
    {
        /* Error occured during parsing. */
        throw WhadMessageParsingError();
    }
    else
    {
        /* Save parameters. */
        m_hopping = hopping;
    }
}


/**
 * @brief   Retrieve the hopping mode
 * 
 * @retval  bool indicating if frequency hopping is used
 */

bool HopMode::getHopMode()
{
    return m_hopping;
}


/**
 * @brief Set/unset frequency hopping
 */

void HopMode::setHopMode(bool hopping){
    m_hopping = hopping;
}