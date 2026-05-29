#include <dot15d4/dellink.hpp>

using namespace whad::dot15d4;

/**
 * @brief   Parse a message as a DeleteLink message.
 */

DeleteLink::DeleteLink(Dot15d4Msg &message) : Dot15d4Msg(message)
{
    this->unpack();
}


/**
 * @brief       DeleteLink message constructor.
 * 
 * @param[in]   superframe_id       Specify the identifier of the superframe the link is associated to
 * @param[in]   time_slot           Time slot of the link to delete
 * @param[in]   channel_offset      Channel sOffset of the link within the superframe
 
 **/

DeleteLink::DeleteLink(uint32_t superframe_id, uint32_t time_slot, uint32_t channel_offset) : Dot15d4Msg()
{
    /* Save superframe identifier.*/
    m_superframe_id = superframe_id;

    /* Save time slot. */
    m_time_slot = time_slot;

    /* Save offset. */
    m_channel_offset = channel_offset;
}

/**
 * @brief   Pack parameters into a Dot15d4Msg object
 */

void DeleteLink::pack()
{
    whad_dot15d4_del_link(
        this->getMessage(),
        m_superframe_id,
        m_time_slot,
        m_channel_offset
    );
}


/**
 * @brief   Extract parameters from a Dot15d4Msg
 */

void DeleteLink::unpack()
{
    whad_result_t result;
    
    uint32_t superframe_id;
    uint32_t time_slot;
    uint32_t channel_offset;

    result = whad_dot15d4_del_link_parse(
        this->getMessage(),
        &superframe_id, 
        &time_slot, 
        &channel_offset
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
        m_time_slot = time_slot;
        m_channel_offset = channel_offset;
    }
}


/**
 * @brief   Retrieve the Superframe identifier associated with the deleted link
 * 
 * @retval  Superframe identifier
 */
uint32_t DeleteLink::getSuperframeId()
{
    return m_superframe_id;
}


/**
 * @brief   Retrieve the time slot associated with the deleted link
 * 
 * @retval  Time slot of the link
 */
 
uint32_t DeleteLink::getTimeSlot()
{
    return m_time_slot;
}

/**
 * @brief   Retrieve the channel offset of the link within the superframe
 * 
 * @retval  Channel Offset in Superframe 
 */
uint32_t DeleteLink::getChannelOffset()
{
    return m_channel_offset;
}