#include <ant/jammed.hpp>

using namespace whad::ant;

/**
 * @brief   Constructor, parses an AntMsg as a Jammed message.
 *
 * @param[in]   message Message to parse
 */

Jammed::Jammed(AntMsg &message) : AntMsg(message)
{
    this->unpack();
}


/**
 * @brief   Constructor, create a new Jammed message
 * 
 * @param[in]   timestamp   Timestamp at which the target has been
 *                          successfully jammed.
 */

Jammed::Jammed(uint32_t timestamp) : AntMsg()
{
    m_timestamp = timestamp;
}


/**
 * @brief   Retrieve the corresponding timestamp.
 * 
 * @retval  Timestamp in milliseconds
*/
uint32_t Jammed::getTimestamp()
{
    return m_timestamp;
}


/**
 * Pack parameters into an AntMsg.
 */

void Jammed::pack()
{
    whad_ant_jammed(
        this->getMessage(),
        m_timestamp
    );
}


/**
 * Extract parameters from an AntMsg.
 */

void Jammed::unpack()
{
    if (whad_ant_jammed_parse(this->getMessage(), &m_timestamp) == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}
