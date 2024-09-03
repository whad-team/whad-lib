#include <unifying/jammed.hpp>

using namespace whad::unifying;

/**
 * @brief   Parse a message as a Jammed message.
 */

Jammed::Jammed(UnifyingMsg &message) : UnifyingMsg(message)
{
    this->unpack();
}


/**
 * @brief       Jammed message constructor.
 * 
 * @param[in]   timestamp       Timestamp at which the jamming has been detected
 **/

Jammed::Jammed(uint32_t timestamp) : UnifyingMsg()
{
    /* Save target address. */
    m_timestamp = timestamp;
}


/**
 * @brief   Pack parameters into a UnifyingMsg object
 */

void Jammed::pack()
{
    whad_unifying_jam(
        this->getMessage(),
        m_timestamp
    );
}


/**
 * @brief   Extract parameters from a UnifyingMsg
 */

void Jammed::unpack()
{
    whad_result_t result;
    uint32_t timestamp;

    result = whad_unifying_jam_parse(
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
 * @retval  Timestamp in seconds
 */

uint32_t Jammed::getTimestamp()
{
    return m_timestamp;
}

