#include "phy/setbpskmod.hpp"

using namespace whad::phy;

/**
 * @brief   Create a SetBpskMod message from a NanoPbMsg message.
 * 
 * @param[in]   message NanoPbMsg instance
 **/

SetBpskMod::SetBpskMod(PhyMsg &message) : PhyMsg(message)
{
}


/**
 * @brief   Create a SetBpskMod message.
 **/

SetBpskMod::SetBpskMod()
{
}


/**
 * @brief   Create a SetBpskMod message.
 */

void SetBpskMod::pack()
{
    whad_phy_set_bpsk_mod(
        this->getMessage()
    );
}