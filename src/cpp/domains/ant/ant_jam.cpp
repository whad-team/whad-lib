#include <ant/jam.hpp>

using namespace whad::ant;

/**
 * @brief   Constructor, parse a message as a Jam message.
 *
 * @param[in]   message     Message to parse
 */

Jam::Jam(AntMsg &message) : AntMsg(message)
{
    /* Unpack message. */
    this->unpack();
}


/**
 * @brief   Constructor, create a Jam
 *
 * @param[in]   rf_channel         ANT RF channel to set
 */

Jam::Jam(uint32_t rf_channel) : AntMsg()
{
    /* Copy RF channel. */
    this->m_rf_channel = rf_channel;
}


/**
 * @brief   Retrieve the ANT RF channel
 *
 * @retval  ANT RF channel
 */

uint32_t Jam::getRFChannel(void)
{
    return this->m_rf_channel;
}


/**
 * @brief   Pack parameters into an AntMsg.
 **/

void Jam::pack()
{
    /* Craft message. */
    whad_ant_jam(this->getMessage(), this->m_rf_channel);
}


/**
 * @brief   Extract parameters from AntMsg.
 */

void Jam::unpack()
{
    uint32_t rf_channel;

    /* Parse message. */
    if (whad_ant_jam_parse(this->getMessage(), &rf_channel) == WHAD_SUCCESS)
    {
        this->m_rf_channel = rf_channel;
    }
    else
    {
        /* Error. */
        throw WhadMessageParsingError();
    }
}