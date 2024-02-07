#include "phy/setloramod.hpp"

using namespace whad::phy;

/**
 * @brief       Create a SetLoraMod message from a NanoPbMsg message.
 * 
 * @param[in]   message PhyMsg instance
 **/

SetLoraMod::SetLoraMod(PhyMsg &message) : PhyMsg(message)
{
    this->unpack();
}


/**
 * @brief       Create a SetLoraMod message with specific parameters.
 * 
 * @param[in]   bandwidth       Modulation bandwidth in Hz
 * @param[in]   sf              Spreading factor
 * @param[in]   cr              Coding rate
 * @param[in]   enableCrc       If true, CRC will be enabled and checked by the hardware
 * @param[in]   preambleLength  Length of preamble, in number of symbols
 * @param[in]   explicitMode    If true, set explicit mode
 * @param[in]   invertIq        If true, invert I/Q (used in downstream channels)
 **/

SetLoraMod::SetLoraMod(uint32_t bandwidth, LoRaSpreadingFactor sf,
                               LoRaCodingRate cr, uint32_t preambleLength,
                               bool enableCrc, bool explicitMode, bool invertIq) : PhyMsg()
{
    m_bandwidth = bandwidth;
    m_sf = sf;
    m_cr = cr;
    m_preambleLength = preambleLength;
    m_enableCrc = enableCrc;
    m_explicitMode = explicitMode;
    m_invertIq = invertIq;
}


/**
 * @brief       Get the message bandwidth modulation parameter
 * 
 * @retval      Bandwidth in Hz.
 **/

uint32_t SetLoraMod::getBandwidth()
{
    return m_bandwidth;
}


/**
 * @brief       Get the message preamble length parameter.
 * 
 * @retval      Preamble length in number of symbols.
 **/

uint32_t SetLoraMod::getPreambleLength()
{
    return m_preambleLength;
}


/**
 * @brief       Get the message spreading factor parameter.
 * 
 * @retval      Spreading factor
 **/

LoRaSpreadingFactor SetLoraMod::getSpreadingFactor()
{
    return m_sf;
}


/**
 * @brief       Get the message coding rate parameter.
 * 
 * @retval      Coding rate
 **/

LoRaCodingRate SetLoraMod::getCodingRate()
{
    return m_cr;
}


/**
 * @brief       Determine if CRC is enabled.
 * 
 * @retval      True if CRC should be enabled, false otherwise.
 **/

bool SetLoraMod::isCrcEnabled()
{
    return m_enableCrc;
}


/**
 * @brief       Determine if explicit mode is enabled.
 * 
 * @retval      True if explicit mode should be enabled, false otherwise.
 **/

bool SetLoraMod::isExplicitMode()
{
    return m_explicitMode;
}


/**
 * @brief       Determine if IQ inversion is enabled.
 * 
 * @retval      True if IQ inversion should be enabled, false otherwise.
 **/

bool SetLoraMod::isIqInverted()
{
    return m_invertIq;
}


/**
 * @brief   Pack parameters into a PhyMsg.
 */

void SetLoraMod::pack()
{
    whad_phy_set_lora_mod(
        this->getMessage(),
        m_bandwidth,
        (whad_phy_lora_sf_t)m_sf,
        (whad_phy_lora_cr_t)m_cr,
        m_preambleLength,
        m_enableCrc, m_explicitMode, m_invertIq
    );
}


/**
 * @brief   Extract parameters from PhyMsg.
 */

void SetLoraMod::unpack()
{
    whad_phy_lora_params_t params;

    if (whad_phy_set_lora_mod_parse(this->getMessage(), &params) == WHAD_SUCCESS)
    {
        m_bandwidth = params.bandwidth;
        m_sf = (LoRaSpreadingFactor)params.sf;
        m_cr = (LoRaCodingRate)params.cr;
        m_preambleLength = params.preamble_length;
        m_enableCrc = params.enable_crc;
        m_explicitMode = params.explicit_mode;
        m_invertIq = params.invert_iq;
    }
    else
    {
        throw WhadMessageParsingError();
    } 
}
