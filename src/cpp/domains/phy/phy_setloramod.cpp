#include "phy/setloramod.hpp"

using namespace whad::phy;

/** LoRa modulation **/


/**
 * @brief       Create a SetLoraMod message from a NanoPbMsg message.
 * 
 * @param[in]   message NanoPbMsg instance
 **/

SetLoraMod::SetLoraMod(NanoPbMsg &message) : PhyMsg(message)
{
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
    whad_phy_set_lora_mod(
        this->getRaw(),
        bandwidth,
        (whad_phy_lora_sf_t)sf,
        (whad_phy_lora_cr_t)cr,
        preambleLength,
        enableCrc, explicitMode, invertIq
    );
}


/**
 * @brief       Parse the current message and extract its parameters.
 * 
 * @retval      True if parsing has been correctly performed, false otherwise.
 **/

bool SetLoraMod::parse()
{
    if (whad_phy_set_lora_mod_parse(this->getRaw(), &this->m_params) == WHAD_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}


/**
 * @brief       Get the message bandwidth modulation parameter
 * 
 * @retval      Bandwidth in Hz.
 **/

uint32_t SetLoraMod::getBandwidth()
{
    if (this->parse())
    {
        return this->m_params.bandwidth;
    }
    
    /* Error. */
    return 0;
}


/**
 * @brief       Get the message preamble length parameter.
 * 
 * @retval      Preamble length in number of symbols.
 **/

uint32_t SetLoraMod::getPreambleLength()
{
    if (this->parse())
    {
        return this->m_params.preamble_length;
    }
    
    /* Error. */
    return 0;
}


/**
 * @brief       Get the message spreading factor parameter.
 * 
 * @retval      Spreading factor
 **/

LoRaSpreadingFactor SetLoraMod::getSpreadingFactor()
{
    if (this->parse())
    {
        return (LoRaSpreadingFactor)this->m_params.sf;
    }

    /* Error. */
    return LoraSfError;
}


/**
 * @brief       Get the message coding rate parameter.
 * 
 * @retval      Coding rate
 **/

LoRaCodingRate SetLoraMod::getCodingRate()
{
    if (this->parse())
    {
        return (LoRaCodingRate)this->m_params.cr;
    }

    /* Error. */
    return LoraCrError; 
}


/**
 * @brief       Determine if CRC is enabled.
 * 
 * @retval      True if CRC should be enabled, false otherwise.
 **/

bool SetLoraMod::isCrcEnabled()
{
    if (this->parse())
    {
        return this->m_params.enable_crc;
    }

    /* Error. */
    return false;
}


/**
 * @brief       Determine if explicit mode is enabled.
 * 
 * @retval      True if explicit mode should be enabled, false otherwise.
 **/

bool SetLoraMod::isExplicitMode()
{
    if (this->parse())
    {
        return this->m_params.explicit_mode;
    }

    /* Error. */
    return false;
}


/**
 * @brief       Determine if IQ inversion is enabled.
 * 
 * @retval      True if IQ inversion should be enabled, false otherwise.
 **/

bool SetLoraMod::isIqInverted()
{
    if (this->parse())
    {
        return this->m_params.invert_iq;
    }

    /* Error. */
    return false;
}


