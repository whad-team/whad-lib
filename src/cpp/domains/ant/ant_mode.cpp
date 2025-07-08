#include <ant/mode.hpp>

using namespace whad::ant;

/**
 * @brief   Constructor, parse a message as a MasterMode message.
 *
 * @param[in]   message     Message to parse
 */

MasterMode::MasterMode(AntMsg &message) : AntMsg(message)
{
    /* Unpack message. */
    this->unpack();
}


/**
 * @brief   Constructor, create a MasterMode
 *
 * @param[in]   channel_number                  ANT channel number to select
 */

MasterMode::MasterMode(uint32_t channel_number) : AntMsg()
{
    /* Copy channel number. */
    this->m_channel_number = channel_number;
}


/**
 * @brief   Retrieve the ANT Channel Number
 *
 * @retval  ANT channel number
 */

uint32_t MasterMode::getChannelNumber(void)
{
    return this->m_channel_number;
}

/**
 * @brief   Pack parameters into an AntMsg.
 **/

void MasterMode::pack()
{
    /* Craft message. */
    whad_ant_master_mode(this->getMessage(), this->m_channel_number);
}


/**
 * @brief   Extract parameters from AntMsg.
 */

void MasterMode::unpack()
{
    uint32_t channel_number;

    /* Parse message. */
    if (whad_ant_master_mode_parse(this->getMessage(), &channel_number) == WHAD_SUCCESS)
    {
        this->m_channel_number = channel_number;
    }
    else
    {
        /* Error. */
        throw WhadMessageParsingError();
    }
}


/**
 * @brief   Constructor, parse a message as a SlaveMode message.
 *
 * @param[in]   message     Message to parse
 */

SlaveMode::SlaveMode(AntMsg &message) : AntMsg(message)
{
    /* Unpack message. */
    this->unpack();
}


/**
 * @brief   Constructor, create a SlaveMode
 *
 * @param[in]   channel_number                  ANT channel number to select
 */

SlaveMode::SlaveMode(uint32_t channel_number) : AntMsg()
{
    /* Copy channel number. */
    this->m_channel_number = channel_number;
}


/**
 * @brief   Retrieve the ANT Channel Number
 *
 * @retval  ANT channel number
 */

uint32_t SlaveMode::getChannelNumber(void)
{
    return this->m_channel_number;
}

/**
 * @brief   Pack parameters into an AntMsg.
 **/

void SlaveMode::pack()
{
    /* Craft message. */
    whad_ant_slave_mode(this->getMessage(), this->m_channel_number);
}


/**
 * @brief   Extract parameters from AntMsg.
 */

void SlaveMode::unpack()
{
    uint32_t channel_number;

    /* Parse message. */
    if (whad_ant_slave_mode_parse(this->getMessage(), &channel_number) == WHAD_SUCCESS)
    {
        this->m_channel_number = channel_number;
    }
    else
    {
        /* Error. */
        throw WhadMessageParsingError();
    }
}