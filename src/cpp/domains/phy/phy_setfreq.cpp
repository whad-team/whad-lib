#include "phy/setfreq.hpp"

using namespace whad::phy;

/** Set frequency **/

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
    whad_phy_set_freq(
        this->getRaw(),
        frequency
    );
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

void SetFreq::unpack(void)
{
    whad_phy_set_freq_parse(
        this->getRaw(),
        &m_freq
    );
}