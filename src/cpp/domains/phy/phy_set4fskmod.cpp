#include "phy/set4fskmod.hpp"

using namespace whad::phy;


/**
 * @brief   Create a Set4FskMod message from a NanoPbMessage.
 * 
 * @param[in]   message     NanoPb message
 */

Set4FskMod::Set4FskMod(PhyMsg &message) : PhyMsg(message), FskMod()
{
    this->unpack();
}


/**
 * @brief   Create a Set4FskMod message with a specific deviation
 * 
 * @param[in]   deviation   Deviation in Hz
 */

Set4FskMod::Set4FskMod(uint32_t deviation) : PhyMsg(), FskMod(deviation)
{
}


/**
 * @brief   Pack parameters in a PhyMsg.
 */

void Set4FskMod::pack()
{
    whad_phy_set_4fsk_mod(
        this->getMessage(),
        m_deviation
    );  
}


/**
 * @brief   Extract parameters from a PhyMsg.
 */

void Set4FskMod::unpack()
{
    if (whad_phy_set_4fsk_mod_parse(this->getMessage(), &m_deviation) == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}