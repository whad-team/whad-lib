#include "phy/setaskmod.hpp"

using namespace whad::phy;

/**
 * @brief       Create a SetAskMod message based on raw PHY message.
 * 
 * @param[in]   message     Base NanoPb message to use.
 **/

SetAskMod::SetAskMod(PhyMsg &message) : PhyMsg(message)
{
    this->unpack();
}


/**
 * @brief       Create a SetAskMod message.
 * 
 * @param[in]   ook     On/Off keying is enabled if set to true, disabled otherwise.
 **/

SetAskMod::SetAskMod(bool ook) : PhyMsg()
{
    m_isOok = ook;
}


/**
 * @brief       Determine if OnOff keying is enabled or not.
 * 
 * @retval      OOK is enabled if true, disabled otherwise.
 **/

bool SetAskMod::isOok()
{
    return m_isOok;
}


/**
 * @brief   Pack parameters into a PhyMsg.
 */

void SetAskMod::pack()
{
    whad_phy_set_ask_mod(
        this->getMessage(),
        m_isOok
    );
}


/**
 * @brief   Extract parameters from a PhyMsg.
 */

void SetAskMod::unpack()
{
    if (whad_phy_set_ask_mod_parse(this->getMessage(), &m_isOok) == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}