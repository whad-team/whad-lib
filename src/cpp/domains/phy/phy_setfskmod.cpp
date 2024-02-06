#include "phy/setfskmod.hpp"

using namespace whad::phy;


/** FSK modulation **/

/**
 * @brief   Create a SetFskMod message from a NanoPbMessage.
 * 
 * @param[in]   message     NanoPb message
 */

SetFskMod::SetFskMod(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief   Create a SetFskMod message with a specific deviation
 * 
 * @param[in]   deviation   Deviation in Hz
 */

SetFskMod::SetFskMod(uint32_t deviation) : PhyMsg()
{
    whad_phy_set_fsk_mod(
        this->getRaw(),
        deviation
    );
}


/**
 * @brief   Get the current deviation from a SetFskMod message.
 * 
 * @retval  Deviation in Hz.
 */

uint32_t SetFskMod::getDeviation()
{
    uint32_t deviation = 0;

    /* Parse message structure. */
    whad_phy_set_fsk_mod_parse(
        this->getRaw(),
        &deviation
    );

    return deviation;
}