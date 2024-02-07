#include "phy/settxpower.hpp"

using namespace whad::phy;

/**
 * @brief       Create a SetTxPower message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

SetTxPower::SetTxPower(PhyMsg &message) : PhyMsg(message)
{
    this->unpack();
}


/**
 * @brief       Create a SetTxPower message with a specific power level.
 * 
 * @param[in]   power   Power level to use
 **/

SetTxPower::SetTxPower(TxPower power) : PhyMsg()
{
    m_power = power;
}


/**
 * @brief       Get the specified power level
 * 
 * @retval      Power level specified in this message
 **/

TxPower SetTxPower::getPower()
{
    return m_power;
}


/**
 * @brief   Pack parameters into a PhyMsg.
 */

void SetTxPower::pack()
{
    whad_phy_set_tx_power(
        this->getMessage(),
        (whad_phy_txpower_t)m_power
    );
}


/**
 * @brief   Extract parameters from PhyMsg.
 */

void SetTxPower::unpack()
{
    if (whad_phy_set_tx_power_parse(this->getMessage(), (whad_phy_txpower_t *)&m_power) == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    } 
}