#include "phy/setmskmod.hpp"

using namespace whad::phy;

/**
 * @brief       Create a SetMskMod message from a NanoPbMsg message.
 * 
 * @param[in]   message NanoPbMsg instance
 **/

SetMskMod::SetMskMod(PhyMsg &message) : PhyMsg(message), FskMod()
{
    this->unpack();
}


/**
 * @brief       Create a SetMskMod message with a specific deviation.
 * 
 * @param[in]   deviation   Deviation in Hz
 **/

SetMskMod::SetMskMod(uint32_t deviation) : PhyMsg(), FskMod(deviation)
{
}


/**
 * @brief   Pack parameters into a PhyMsg.
 */

void SetMskMod::pack()
{
    whad_phy_set_msk_mod(
        this->getMessage(),
        m_deviation
    );
}


/**
 * @brief   Extract parameters from PhyMsg.
 */

void SetMskMod::unpack()
{
    if (whad_phy_set_msk_mod_parse(this->getMessage(), &m_deviation) == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}