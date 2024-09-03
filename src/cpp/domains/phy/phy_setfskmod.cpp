#include "phy/setfskmod.hpp"

using namespace whad::phy;


/** FSK modulation **/

/**
 * @brief   Create a SetFskMod message from a NanoPbMsg.
 * 
 * @param[in]   message     NanoPb message
 */

SetFskMod::SetFskMod(PhyMsg &message) : PhyMsg(message), FskMod()
{
    this->unpack();
}


/**
 * @brief   Create a SetFskMod message with a specific deviation
 * 
 * @param[in]   deviation   Deviation in Hz
 */

SetFskMod::SetFskMod(uint32_t deviation) : PhyMsg(), FskMod(deviation)
{
}


/**
 * @brief   Pack parameters into a PhyMsg.
 */

void SetFskMod::pack()
{
    whad_phy_set_fsk_mod(
        this->getMessage(),
        m_deviation
    );  
}


/**
 * @brief   Extract parameters from PhyMsg.
 */

void SetFskMod::unpack()
{
    if (whad_phy_set_fsk_mod_parse(this->getMessage(), &m_deviation) == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}