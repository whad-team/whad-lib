#include <zigbee/jammed.hpp>

using namespace whad::zigbee;

/**
 * @brief   Parse a message as a Jammed message.
 */

Jammed::Jammed(ZigbeeMsg &message) : ZigbeeMsg(message)
{
    this->unpack();
}


/**
 * @brief       Jammed message constructor.
 * 
 * @param[in]   timestamp         Specify the timestamp
 **/

Jammed::Jammed(uint32_t timestamp) : ZigbeeMsg()
{
    /* Save timestamp. */
    m_timestamp = timestamp;
}


/**
 * @brief   Pack parameters into a ZigbeeMsg object
 */

void Jammed::pack()
{
    whad_zigbee_jammed(
        this->getMessage(),
        m_timestamp
    );
}


/**
 * @brief   Extract parameters from a ZigbeeMsg
 */

void Jammed::unpack()
{
    whad_result_t result;
    uint32_t timestamp;

    result = whad_zigbee_jammed_parse(
        this->getMessage(),
        &timestamp
    );

    if (result == WHAD_ERROR)
    {
        /* Error occured during parsing. */
        throw WhadMessageParsingError();
    }
    else
    {
        /* Save parameters. */
        m_timestamp = timestamp;
    }
}


/**
 * @brief   Retrieve the timestamp
 * 
 * @retval  Timestamp value (in seconds)
 */

uint32_t Jammed::getTimestamp()
{
    return m_timestamp;
}
