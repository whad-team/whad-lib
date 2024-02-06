#include "phy/settxpower.hpp"

using namespace whad::phy;

/** Set Tx power **/

/**
 * @brief       Create a SetTxPower message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

SetTxPower::SetTxPower(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a SetTxPower message with a specific power level.
 * 
 * @param[in]   power   Power level to use
 **/

SetTxPower::SetTxPower(TxPower power) : PhyMsg()
{
    whad_phy_set_tx_power(
        this->getRaw(),
        (whad_phy_txpower_t)power
    );
}


/**
 * @brief       Get the specified power level
 * 
 * @retval      Power level specified in this message
 **/

TxPower SetTxPower::getPower()
{
    whad_phy_txpower_t power;

    whad_phy_set_tx_power_parse(
        this->getRaw(),
        &power
    );

    return (TxPower)power;
}