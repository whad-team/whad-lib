#include "phy/setgfskmod.hpp"

using namespace whad::phy;


/** GFSK modulation **/

/**
 * @brief   Create a SetGfskMod message from a NanoPbMsg message.
 * 
 * @param[in]   message NanoPbMsg instance
 **/

SetGfskMod::SetGfskMod(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a SetGfskMod message with a specific deviation
 * 
 * @param[in]   deviation   Deviation in Hz
 **/

SetGfskMod::SetGfskMod(uint32_t deviation) : PhyMsg()
{
    whad_phy_set_gfsk_mod(
        this->getRaw(),
        deviation
    );
}


/**
 * @brief       Get the deviation
 * 
 * @retval      GFSK deviation in Hz
 **/

uint32_t SetGfskMod::getDeviation()
{
    uint32_t deviation = 0;

    /* Parse message structure. */
    whad_phy_set_gfsk_mod_parse(
        this->getRaw(),
        &deviation
    );

    return deviation;
}