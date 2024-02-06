#include "phy/setmskmod.hpp"

using namespace whad::phy;

/** MSK modulation **/


/**
 * @brief       Create a SetMskMod message from a NanoPbMsg message.
 * 
 * @param[in]   message NanoPbMsg instance
 **/

SetMskMod::SetMskMod(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a SetMskMod message with a specific deviation.
 * 
 * @param[in]   deviation   Deviation in Hz
 **/

SetMskMod::SetMskMod(uint32_t deviation) : PhyMsg()
{
    whad_phy_set_msk_mod(
        this->getRaw(),
        deviation
    );
}


/**
 * @brief       Get current deviation.
 * 
 * @retval      Deviation in Hz
 **/

uint32_t SetMskMod::getDeviation()
{
    uint32_t deviation = 0;

    /* Parse message structure. */
    whad_phy_set_msk_mod_parse(
        this->getRaw(),
        &deviation
    );

    return deviation;
}
