#include <dot15d4/setchm.hpp>

using namespace whad::dot15d4;

/**
 * @brief   Parse a message as a SetChannelMap message.
 */

SetChannelMap::SetChannelMap(Dot15d4Msg &message) : Dot15d4Msg(message)
{
    this->unpack();
}


/**
 * @brief       SetChannelMap message constructor.
 * 
 * @param[in]   channel         Specify the channel map (bitmap of enabled channels)
 **/

SetChannelMap::SetChannelMap(uint32_t channel_map) : Dot15d4Msg()
{
    /* Save channel map. */
    m_channel_map = channel_map;
}


/**
 * @brief   Pack parameters into a Dot15d4Msg object
 */

void SetChannelMap::pack()
{
    whad_dot15d4_set_chm(
        this->getMessage(),
        m_channel_map
    );
}


/**
 * @brief   Extract parameters from a Dot15d4Msg
 */

void SetChannelMap::unpack()
{
    whad_result_t result;
    uint32_t channel_map;

    result = whad_dot15d4_set_chm_parse(
        this->getMessage(),
        &channel_map
    );

    if (result == WHAD_ERROR)
    {
        /* Error occured during parsing. */
        throw WhadMessageParsingError();
    }
    else
    {
        /* Save parameters. */
        m_channel_map = channel_map;
    }
}


/**
 * @brief   Retrieve the dot15d4 channel map
 * 
 * @retval  Channel map
 */

uint32_t SetChannelMap::getChannelMap()
{
    return m_channel_map;
}
