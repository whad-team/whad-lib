#include "phy/setbpskmod.hpp"

using namespace whad::phy;

/** BPSK modulation **/


/**
 * @brief   Create a SetBpskMod message from a NanoPbMsg message.
 * 
 * @param[in]   message NanoPbMsg instance
 **/

SetBpskMod::SetBpskMod(NanoPbMsg &message) : PhyMsg(message)
{
}


/**
 * @brief   Create a SetBpskMod message.
 **/

SetBpskMod::SetBpskMod()
{
}