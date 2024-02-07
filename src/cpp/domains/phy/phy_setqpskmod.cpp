#include "phy/setqpskmod.hpp"

using namespace whad::phy;

/**
 * @brief   Create a SetQpskMod message from a NanoPbMsg message.
 * 
 * @param[in]   message NanoPbMsg instance
 **/


SetQpskMod::SetQpskMod(PhyMsg &message) : PhyMsg(message)
{
    this->unpack();
}


/**
 * @brief       Create a SetQpskMod message with a specific offset.
 * 
 * @param[in]   offset  Modulation offset
 **/

SetQpskMod::SetQpskMod(bool offset) : PhyMsg()
{
    m_offset = offset;
}


/**
 * @brief       Get modulation offset.
 * 
 * @retval      Modulation offset
 **/

bool SetQpskMod::getOffset()
{
    return m_offset;
}


/**
 * @brief   Pack parameters into a PhyMsg.
 */

void SetQpskMod::pack()
{
    whad_phy_set_qpsk_mod(
        this->getMessage(),
        m_offset
    );    
}


/**
 * @brief   Extract parameters from PhyMsg.
 */

void SetQpskMod::unpack()
{
    if (whad_phy_set_qpsk_mod_parse(this->getMessage(), &m_offset) == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}