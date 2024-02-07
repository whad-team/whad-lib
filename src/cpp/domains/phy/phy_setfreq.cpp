#include "phy/setfreq.hpp"

using namespace whad::phy;

/**
 * @brief       Create a SetFreq message from a NanoPbMsg message.
 * 
 * @param[in]   message NanoPbMsg instance
 **/

SetFreq::SetFreq(NanoPbMsg &message) : PhyMsg(message)
{
    this->unpack();
}


/**
 * @brief       Create a SetFreq message with a specific frequency
 * 
 * @param[in]   frequency   Frequency in Hz
 **/

SetFreq::SetFreq(uint32_t frequency) : PhyMsg()
{
    m_freq = frequency;
}


/**
 * @brief       Get the frequency specified in this message
 * 
 * @retval      Frequency in Hz
 **/

uint32_t SetFreq::getFrequency()
{
    return m_freq;
}


/**
 * @brief   Extract parameters from a PhyMsg.
 */

void SetFreq::unpack()
{
    if (whad_phy_set_freq_parse(this->getMessage(), &m_freq) == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}


/**
 * @brief   Pack parameters into a PhyMsg.
 */

void SetFreq::pack()
{
    whad_phy_set_freq(
        this->getMessage(),
        m_freq
    );
}