#include <dot15d4/deletesuperframe.hpp>

using namespace whad::dot15d4;

/**
 * @brief   Parse a message as a UpdateSuperframe message.
 */

DeleteSuperframe::DeleteSuperframe(Dot15d4Msg &message) : Dot15d4Msg(message)
{
    this->unpack();
}


/**
 * @brief       DeleteSuperframe message constructor.
 * 
 * @param[in]   superframe_id       Specify the identifier of the superframe
 **/

DeleteSuperframe::DeleteSuperframe(uint32_t superframe_id) : Dot15d4Msg()
{
    /* Save superframe identifier.*/
    m_superframe_id = superframe_id;
}

/**
 * @brief   Pack parameters into a Dot15d4Msg object
 */

void DeleteSuperframe::pack()
{
    whad_dot15d4_del_superframe(
        this->getMessage(),
        m_superframe_id
    );
}


/**
 * @brief   Extract parameters from a Dot15d4Msg
 */

void DeleteSuperframe::unpack()
{
    whad_result_t result;
    
    uint32_t superframe_id;

    result = whad_dot15d4_del_superframe_parse(
        this->getMessage(),
        &superframe_id
    );

    if (result == WHAD_ERROR)
    {
        /* Error occured during parsing. */
        throw WhadMessageParsingError();
    }
    else
    {
        /* Save parameters. */
        m_superframe_id = superframe_id;
    }
}


/**
 * @brief   Retrieve the Superframe identifier
 * 
 * @retval  Superframe identifier
 */
uint32_t DeleteSuperframe::getSuperframeId()
{
    return m_superframe_id;
}