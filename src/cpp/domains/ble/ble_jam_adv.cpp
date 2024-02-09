#include <ble/jam_adv.hpp>

using namespace whad::ble;

/**
 * @brief       JamAdv message constructor.
 * 
 **/

JamAdv::JamAdv(BleMsg &message) : BleMsg(message)
{
    this->unpack();
}


/**
 * @brief   Default advertisement jamming message
 */

JamAdv::JamAdv() : BleMsg()
{
    m_channel = 0;
    m_hasChannel = false;
}


/**
 * @brief       JamAdv message constructor.
 * 
 * @param[in]   channel     Channel to jam.
 **/

JamAdv::JamAdv(uint32_t channel) : BleMsg()
{
    m_channel = channel;
    m_hasChannel = true;
}


/**
 * @brief   Pack parameters into a BleMsg
 */

void JamAdv::pack()
{
    if (m_hasChannel)
    {
        whad_ble_jam_adv_channel(this->getMessage(), m_channel);
    }
    else
    {
        whad_ble_jam_adv(this->getMessage());
    }
}


/**
 * @brief   Extract parameters from BleMsg
 */

void JamAdv::unpack()
{
    whad_result_t result;

    /* Determine the message type. */
    switch (this->getType())
    {
        case JamAdvMsg:
        {
            result = WHAD_SUCCESS;
        }
        break;

        case JamAdvChannelMsg:
        {
            result = whad_ble_jam_adv_channel_parse(
                this->getMessage(),
                &m_channel
            );

            if (result == WHAD_ERROR)
            {
                throw WhadMessageParsingError();
            }
        }
        break;

        default:
            throw WhadMessageParsingError();
            break;
    }
}


/**
 * @brief   Determine if message has a channel specified
 * 
 * @retval  True if channel has been specified, false otherwise.
 */

bool JamAdv::hasChannel()
{
    return m_hasChannel;
}


/**
 * @brief   Retrieve the channel set in the message.
 * 
 * @retval  Channel number
 */

uint32_t JamAdv::getChannel()
{
    return m_channel;
}