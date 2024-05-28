#include <dot15d4/mitm.hpp>

using namespace whad::dot15d4;

/**
 * @brief   Parse a message as a MitmMode message.
 */

MitmMode::MitmMode(Dot15d4Msg &message) : Dot15d4Msg(message)
{
    this->unpack();
}


/**
 * @brief       MitmMode message constructor.
 * 
 * @param[in]   role         Specify the MitM role
 **/

MitmMode::MitmMode(MitmRole role) : Dot15d4Msg()
{
    /* Save channel. */
    m_role = role;
}


/**
 * @brief   Pack parameters into a Dot15d4Msg object
 */

void MitmMode::pack()
{
    whad_dot15d4_mitm_mode(
        this->getMessage(),
        (whad_dot15d4_mitm_role_t)m_role
    );
}


/**
 * @brief   Extract parameters from a Dot15d4Msg
 */

void MitmMode::unpack()
{
    whad_result_t result;
    whad_dot15d4_mitm_role_t role;

    result = whad_dot15d4_mitm_mode_parse(
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
