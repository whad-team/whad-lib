#include <dot15d4/addlink.hpp>

using namespace whad::dot15d4;

/**
 * @brief   Parse a message as a AddLink message.
 */

AddLink::AddLink(Dot15d4Msg &message) : Dot15d4Msg(message)
{
    this->unpack();
}


/**
 * @brief       AddLink message constructor.
 * 
 * @param[in]   superframe_id   Specify the identifier of the superframe the link must be associated to
 * @param[in]   src             Address of the Source associated to the link
 * @param[in]   time_slot       Time slot associated to the link
 * @param[in]   channel_offset  Channel Offset of the link within the superframe
 * @param[in]   neighbor        Address of the Neighbor associated to the link  
 * @param[in]   options         Options of the associated link  
 * @param[in]   type            Type of the associated link  
 
 **/

AddLink::AddLink(uint32_t superframe_id, uint16_t src, uint32_t time_slot, uint32_t channel_offset, uint32_t neighbor, LinkOptions options, LinkType type) : Dot15d4Msg()
{
    /* Save superframe identifier.*/
    m_superframe_id = superframe_id;

    /* Save source address. */
    m_source = src;

    /* Save neighbor address. */
    m_neighbor = neighbor;

    /* Save offset. */
    m_channel_offset = channel_offset;

    /* Save join slot. */
    m_time_slot = time_slot;


    /* Save link options. */
    m_options = options;

    /* Save link type. */
    m_type = type;
}

/**
 * @brief   Pack parameters into a Dot15d4Msg object
 */

void AddLink::pack()
{
    
    /* Craft add link parameters. */
    whad_dot15d4_add_link_params_t params;

    params.superframe_id = m_superframe_id;
    params.src = m_source;
    params.time_slot = m_time_slot;
    params.channel_offset = m_channel_offset;
    params.neighbor = m_neighbor;
    params.options = (whad_dot15d4_link_options_t)m_options;
    params.type = (whad_dot15d4_link_type_t)m_type;

    whad_dot15d4_add_link(
        this->getMessage(),
        params
    );
}


/**
 * @brief   Extract parameters from a Dot15d4Msg
 */

void AddLink::unpack()
{
    whad_result_t result;
    whad_dot15d4_add_link_params_t params;

    result = whad_dot15d4_add_link_parse(
        this->getMessage(),
        &params
    );

    if (result == WHAD_ERROR)
    {
        /* Error occured during parsing. */
        throw WhadMessageParsingError();
    }
    else
    {
        /* Save parameters. */
        m_superframe_id = params.superframe_id;
        m_source = (uint16_t)(params.src);
        m_neighbor = (uint16_t)(params.neighbor);
        m_type = (LinkType)params.type;
        m_options = (LinkOptions)params.options;
        m_time_slot = params.time_slot;
        m_channel_offset = params.channel_offset;
    }
}


/**
 * @brief   Retrieve the Superframe identifier associated with the added link
 * 
 * @retval  Superframe identifier
 */
uint32_t AddLink::getSuperframeId()
{
    return m_superframe_id;
}


/**
 * @brief   Retrieve the source address associated with the added link
 * 
 * @retval  Source address (16-bit short format)
 */
 
uint16_t AddLink::getSource()
{
    return m_source;
}

/**
 * @brief   Retrieve the slot of added link within the superframe
 * 
 * @retval  Time Slot
 */
uint32_t AddLink::getTimeSlot()
{
    return m_time_slot;
}

/**
 * @brief   Retrieve the channel offset of the link within the superframe
 * 
 * @retval  Channel Offset in Superframe 
 */
uint32_t AddLink::getChannelOffset()
{
    return m_channel_offset;
}

/**
 * @brief   Retrieve the neighbor address associated with the added link
 * 
 * @retval  Neighbor address (16-bit short format)
 */
uint16_t AddLink::getNeighbor()
{
    return m_neighbor;
}

/**
 * @brief   Retrieve the options of the added link
 * 
 * @retval  Link options
 */
LinkOptions AddLink::getLinkOptions()
{
    return m_options;
}


/**
 * @brief   Retrieve the type of the added link
 * 
 * @retval  Link type
 */
LinkType AddLink::getLinkType()
{
    return m_type;
}
