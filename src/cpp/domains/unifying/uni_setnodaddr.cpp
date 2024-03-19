#include <unifying/setnodeaddr.hpp>

using namespace whad::unifying;

/**
 * @brief   Parse a message as a SetNodeAddress message.
 */

SetNodeAddress::SetNodeAddress(UnifyingMsg &message) : UnifyingMsg(message)
{
    this->unpack();
}


/**
 * @brief       SetNodeAddress message constructor.
 * 
 * @param[in]   AddressType     ZigBee device address type (short or extended)
 * @param[in]   address         Specify the device address to use
 **/

SetNodeAddress::SetNodeAddress(UnifyingAddress &address) : UnifyingMsg()
{
    /* Save address type and address. */
    m_address = address;
}


/**
 * @brief   Pack parameters into a UnifyingMsg object
 */

void SetNodeAddress::pack()
{
    whad_unifying_address_t address;

    /* Convert our address into a whad_unfying_address_t struct. */
    address.size = m_address.getLength();
    memcpy(address.address, m_address.getBytes(), address.size);

    whad_unifying_set_node_address(
        this->getMessage(),
        &address
    );
}


/**
 * @brief   Extract parameters from a UnifyingMsg
 */

void SetNodeAddress::unpack()
{
    whad_result_t result;
    whad_unifying_address_t address;
    
    result = whad_unifying_set_node_address_parse(
        this->getMessage(),
        &address
    );

    if (result == WHAD_ERROR)
    {
        /* Error occured during parsing. */
        throw WhadMessageParsingError();
    }
    else
    {
        /* Save parameters. */
        m_address.set((uint8_t *)address.address, address.size);
    }
}


/**
 * @brief   Retrieve the unifying node address
 * 
 * @retval  Node address
 */

UnifyingAddress& SetNodeAddress::getAddress()
{
    return m_address;
}
