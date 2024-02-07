#include "phy/sniff.hpp"

using namespace whad::phy;

/**
 * @brief       Create a SniffMode message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

SniffMode::SniffMode(PhyMsg &message) : PhyMsg(message)
{
    this->unpack();
}


/**
 * @brief       Create a SniffMode message.
 * 
 * @param[in]   iqMode  If set to true, will sniff IQ samples otherwise will sniff packets.
 **/

SniffMode::SniffMode(bool iqMode) : PhyMsg()
{
    m_IqModeEnabled = iqMode;
}


/**
 * @brief       Determine if IQ sniffing mode is enabled.
 * 
 * @retval      True if IQ sniffing is enabled, false otherwise.
 **/

bool SniffMode::isIqModeEnabled()
{
    return m_IqModeEnabled;
}


/**
 * @brief   Pack parameters into a PhyMsg.
 */

void SniffMode::pack()
{
    whad_phy_sniff_mode(
        this->getMessage(),
        m_IqModeEnabled
    );
}


/**
 * @brief   Extract parameters from PhyMsg.
 */

void SniffMode::unpack()
{
    if (whad_phy_sniff_mode_parse(this->getMessage(), &m_IqModeEnabled) == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}