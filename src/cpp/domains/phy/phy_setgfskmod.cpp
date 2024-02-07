#include "phy/setgfskmod.hpp"

using namespace whad::phy;

/**
 * @brief   Create a SetGfskMod message from a NanoPbMsg message.
 * 
 * @param[in]   message NanoPbMsg instance
 **/

SetGfskMod::SetGfskMod(PhyMsg &message) : PhyMsg(message), FskMod()
{
    this->unpack();
}


/**
 * @brief       Create a SetGfskMod message with a specific deviation
 * 
 * @param[in]   deviation   Deviation in Hz
 **/

SetGfskMod::SetGfskMod(uint32_t deviation) : PhyMsg(), FskMod(deviation)
{
}


/**
 * @brief   Pack parameters into a PhyMsg.
 */

void SetGfskMod::pack()
{
    whad_phy_set_gfsk_mod(
        this->getMessage(),
        m_deviation
    );
}


/**
 * @brief   Extract parameters from PhyMsg.
 */

void SetGfskMod::unpack()
{
    if (whad_phy_set_gfsk_mod_parse(this->getMessage(), &m_deviation) == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}
