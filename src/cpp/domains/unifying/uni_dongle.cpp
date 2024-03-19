#include <unifying/dongle.hpp>

using namespace whad::unifying;

/**
 * @brief   Parse a message as a DongleMode message.
 */

DongleMode::DongleMode(UnifyingMsg &message) : UnifyingMsg(message)
{
    this->unpack();
}


/**
 * @brief       DongleMode message constructor.
 * 
 * @param[in]   AddressType     Unifying device address
 * @param[in]   address         Specify the device address to use
 **/

DongleMode::DongleMode(uint32_t channel) : UnifyingMsg()
{
    /* Save target address. */
    m_channel = channel;
}


/**
 * @brief   Pack parameters into a UnifyingMsg object
 */

void DongleMode::pack()
{
    whad_unifying_dongle_mode(
        this->getMessage(),
        m_channel
    );
}


/**
 * @brief   Extract parameters from a UnifyingMsg
 */

void DongleMode::unpack()
{
    whad_result_t result;
    uint32_t channel;

    result = whad_unifying_dongle_mode_parse(
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
 * @brief   Retrieve the channel to jam
 * 
 * @retval  Channel number
 */

uint32_t DongleMode::getChannel()
{
    return m_channel;
}

