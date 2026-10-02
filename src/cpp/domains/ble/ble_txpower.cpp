#include <ble/txpower.hpp>

using namespace whad::ble;

/**
 * @brief       SetTxPowerLevel message constructor, parsing an existing message.
 *
 * @param[in]   message     Message to parse.
 */

SetTxPowerLevel::SetTxPowerLevel(BleMsg &message) : BleMsg(message)
{
    unpack();
}


/**
 * @brief       SetTxPowerLevel message constructor.
 *
 * @param[in]   level   Transmit power level
 */
SetTxPowerLevel::SetTxPowerLevel(int32_t level) : BleMsg()
{
    m_level = level;
}

/**
 * @brief   Pack parameters into a BleMsg object.
 */

void SetTxPowerLevel::pack()
{
    whad_ble_set_tx_power_level(
        this->getMessage(),
        m_level
    );
}

/**
 * @brief   Extract parameters from a BleMsg message.
 */

void SetTxPowerLevel::unpack()
{
    int level = 0;
    whad_result_t result;

    result = whad_ble_set_tx_power_level_parse(
        this->getMessage(),
        &level
    );

    if (result == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
    else
    {
        m_level = (int32_t) level;
    }
}


/**
 * @brief       Get the message's TX power level.
 *
 * @retval      TX power level
 */

int32_t SetTxPowerLevel::getLevel()
{
    return m_level;
}
