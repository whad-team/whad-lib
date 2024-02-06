#include "phy/set4fskmod.hpp"

using namespace whad::phy;

/** 4FSK modulation **/

/**
 * @brief   Create a Set4FskMod message from a NanoPbMessage.
 * 
 * @param[in]   message     NanoPb message
 */

Set4FskMod::Set4FskMod(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief   Create a Set4FskMod message with a specific deviation
 * 
 * @param[in]   deviation   Deviation in Hz
 */

Set4FskMod::Set4FskMod(uint32_t deviation) : PhyMsg()
{
    whad_phy_set_4fsk_mod(
        this->getRaw(),
        deviation
    );
}


/**
 * @brief   Get the current deviation from a Set4FskMod message.
 * 
 * @retval  Deviation in Hz.
 */

uint32_t Set4FskMod::getDeviation()
{
    uint32_t deviation = 0;

    /* Parse message structure. */
    whad_phy_set_4fsk_mod_parse(
        this->getRaw(),
        &deviation
    );

    return deviation;
}
