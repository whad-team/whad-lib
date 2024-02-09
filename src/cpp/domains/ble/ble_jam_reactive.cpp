#include <ble/jam_reactive.hpp>

using namespace whad::ble;

/**
 * @brief   Parse a BleMsg into a ReactiveJam message
 */

ReactiveJam::ReactiveJam(BleMsg &message) : BleMsg(message)
{
    this->unpack();
}


/**
 * @brief       ReactiveJam message constructor.
 * 
 * @param[in]   channel         Channel to listen on
 * @param[in]   pPattern        Byte buffer containing the byte pattern to match
 * @param[in]   length          Pattern length in bytes
 * @param[in]   position        Start position for pattern search
 **/

ReactiveJam::ReactiveJam(uint32_t channel, uint8_t *pPattern, unsigned int length, uint32_t position) : BleMsg()
{
    m_channel = channel;
    m_patternLength = length;
    if (m_patternLength <= 20)
    {
        memcpy(m_pattern, pPattern, m_patternLength);
    }
    else
    {
        memset(m_pattern, 0, 20);
    }
    m_position = position;
}


/**
 * @brief   Pack parameters into a BleMsg
 */

void ReactiveJam::pack()
{
    whad_ble_reactive_jam(
        this->getMessage(),
        m_channel,
        m_pattern,
        m_patternLength,
        m_position
    );
}


/**
 * @brief   Extract parameters from a BleMsg
 */

void ReactiveJam::unpack()
{
    whad_result_t result;
    whad_ble_reactive_jam_params_t params;

    result = whad_ble_reactive_jam_parse(
        this->getMessage(),
        &params
    );

    if (result == WHAD_ERROR)
    {
        throw WhadMessageParsingError();
    }
    else
    {
        /* Extract parameters. */
        m_patternLength = params.pattern_length;
        if (m_patternLength <= 20)
        {
            memcpy(m_pattern, params.pattern, m_patternLength);
        }
        m_channel = params.channel;
        m_position = params.position;
    }
}

/**
 * @brief   Retrieve the channel number
 * 
 * @retval  Channel number
 */

uint32_t ReactiveJam::getChannel()
{
    return m_channel;
}


/**
 * @brief   Retrieve a pointer to the pattern
 * 
 * @retval  Pointer to the pattern
 */

uint8_t *ReactiveJam::getPattern()
{
    return m_pattern;
}


/**
 * @brief   Retrieve the pattern length
 * 
 * @retval  Pattern length
 */

unsigned int ReactiveJam::getPatternLength()
{
    return m_patternLength;
}


/**
 * @brief   Retrieve the pattern position
 * 
 * @retval  Pattern position (offset) in bytes
 */

uint32_t ReactiveJam::getPosition()
{
    return m_position;
}