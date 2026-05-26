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
 * @param[in]   superframe_id   Specify the identifier of the superframe the link is associated to
 * @param[in]   offset          Offset of the link within the superframe
 * @param[in]   neighbor        Address of the Neighbor associated to the link  
 
 **/

DeleteLink::DeleteLink(uint32_t superframe_id, uint32_t offset, uint32_t neighbor) : Dot15d4Msg()
{
    /* Save superframe identifier.*/
    m_superframe_id = superframe_id;

    /* Save neighbor address. */
    m_neighbor = neighbor;

    /* Save offset. */
    m_offset = offset;
}

/**
 * @brief   Pack parameters into a Dot15d4Msg object
 */

void DeleteLink::pack()
{
    whad_dot15d4_del_link(
        this->getMessage(),
        m_superframe_id,
        m_offset,
        m_neighbor
    );
}


/**
 * @brief   Extract parameters from a Dot15d4Msg
 */

void DeleteLink::unpack()
{
    whad_result_t result;
    
    uint32_t superframe_id;
    uint32_t offset;
    uint16_t neighbor;

    result = whad_dot15d4_del_link_parse(
        this->getMessage(),
        &superframe_id, 
        &offset, 
        &neighbor
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
        m_neighbor = (uint16_t)(neighbor);
        m_offset = offset;
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
 * @brief   Retrieve the neighbor address associated with the deleted link
 * 
 * @retval  Neighbor address (16-bit short format)
 */
 
uint16_t DeleteLink::getNeighbor()
{
    return m_neighbor;
}

/**
 * @brief   Retrieve the channel offset of the link within the superframe
 * 
 * @retval  Channel Offset in Superframe 
 */
uint32_t DeleteLink::getOffset()
{
    return m_offset;
}