#include "phy/setqpskmod.hpp"

using namespace whad::phy;

/** QPSK modulation **/


/**
 * @brief   Create a SetQpskMod message from a NanoPbMsg message.
 * 
 * @param[in]   message NanoPbMsg instance
 **/


SetQpskMod::SetQpskMod(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief       Create a SetQpskMod message with a specific offset.
 * 
 * @param[in]   offset  Modulation offset
 **/

SetQpskMod::SetQpskMod(bool offset) : PhyMsg()
{
    whad_phy_set_qpsk_mod(
        this->getRaw(),
        offset
    );
}


/**
 * @brief       Get modulation offset.
 * 
 * @retval      Modulation offset
 **/

bool SetQpskMod::getOffset()
{
    bool offset = false;

    whad_phy_set_qpsk_mod_parse(
        this->getRaw(),
        &offset
    );

    return offset;
}