#include <zigbee/mitm.hpp>

using namespace whad::zigbee;

/**
 * @brief   Parse a message as a MitmMode message.
 */

MitmMode::MitmMode(ZigbeeMsg &message) : ZigbeeMsg(message)
{
    this->unpack();
}


/**
 * @brief       MitmMode message constructor.
 * 
 * @param[in]   role         Specify the MitM role
 **/

MitmMode::MitmMode(MitmRole role) : ZigbeeMsg()
{
    /* Save channel. */
    m_role = role;
}


/**
 * @brief   Pack parameters into a ZigbeeMsg object
 */

void MitmMode::pack()
{
    whad_zigbee_mitm_mode(
        this->getMessage(),
        (whad_zigbee_mitm_role_t)m_role
    );
}


/**
 * @brief   Extract parameters from a ZigbeeMsg
 */

void MitmMode::unpack()
{
    whad_result_t result;
    whad_zigbee_mitm_role_t role;

    result = whad_zigbee_mitm_mode_parse(
        this->getMessage(),
        &role
    );

    if (result == WHAD_ERROR)
    {
        /* Error occured during parsing. */
        throw WhadMessageParsingError();
    }
    else
    {
        /* Save parameters. */
        m_role = (MitmRole)role;
    }
}


/**
 * @brief   Retrieve the MitM role
 * 
 * @retval  MitM role
 */

MitmRole MitmMode::getRole()
{
    return m_role;
}
