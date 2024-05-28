#include <dot15d4/jammed.hpp>

using namespace whad::dot15d4;

/**
 * @brief   Parse a message as a Jammed message.
 */

Jammed::Jammed(Dot15d4Msg &message) : Dot15d4Msg(message)
{
    this->unpack();
}


/**
 * @brief       Jammed message constructor.
 * 
 * @param[in]   timestamp         Specify the timestamp
 **/

Jammed::Jammed(uint32_t timestamp) : Dot15d4Msg()
{
    /* Save timestamp. */
    m_timestamp = timestamp;
}


/**
 * @brief   Pack parameters into a Dot15d4Msg object
 */

void Jammed::pack()
{
    whad_dot15d4_jammed(
        this->getMessage(),
        m_timestamp
    );
}


/**
 * @brief   Extract parameters from a Dot15d4Msg
 */

void Jammed::unpack()
{
    whad_result_t result;
    uint32_t timestamp;

    result = whad_dot15d4_jammed_parse(
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
