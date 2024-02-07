#include <esb/jammed.hpp>

using namespace whad::esb;

/**
 * @brief   Constructor, parses an EsbMsg as a Jammed message.
 *
 * @param[in]   message Message to parse
 */

Jammed::Jammed(EsbMsg &message) : EsbMsg(message)
{
    this->unpack();
}


/**
 * @brief   Constructor, create a new Jammed message
 * 
 * @param[in]   timestamp   Timestamp at which the target has been
 *                          successfully jammed.
 */

Jammed::Jammed(uint32_t timestamp) : EsbMsg()
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
 * Pack parameters into an EsbMsg.
 */

void Jammed::pack()
{
    whad_esb_jammed(
        this->getMessage(),
        m_timestamp
    );
}


/**
 * Extract parameters from an EsbMsg.
 */

void Jammed::unpack()
{
    if (whad_esb_jammed_parse(this->getMessage(), &m_timestamp) == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
}
