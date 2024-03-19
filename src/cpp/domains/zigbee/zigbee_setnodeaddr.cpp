#include <zigbee/setnodeaddr.hpp>

using namespace whad::zigbee;

/**
 * @brief   Parse a message as a SetNodeAddress message.
 */

SetNodeAddress::SetNodeAddress(ZigbeeMsg &message) : ZigbeeMsg(message)
{
    this->unpack();
}


/**
 * @brief       SetNodeAddress message constructor.
 * 
 * @param[in]   AddressType     ZigBee device address type (short or extended)
 * @param[in]   address         Specify the device address to use
 **/

SetNodeAddress::SetNodeAddress(AddressType addrType, uint64_t address) : ZigbeeMsg()
{
    /* Save address type and address. */
    m_addrType = addrType;
    m_address = address;
}


/**
 * @brief   Pack parameters into a ZigbeeMsg object
 */

void SetNodeAddress::pack()
{
    whad_zigbee_address_t address_info;

    /* Construct the address info structure. */
    address_info.type = (whad_zigbee_addr_type_t)m_addrType;
    address_info.address = m_address;

    whad_zigbee_set_node_address(
        this->getMessage(),
        &address_info
    );
}


/**
 * @brief   Extract parameters from a ZigbeeMsg
 */

void SetNodeAddress::unpack()
{
    whad_result_t result;
    whad_zigbee_address_t address_info;

    result = whad_zigbee_set_node_address_parse(
        this->getMessage(),
        &address_info
    );

    if (result == WHAD_ERROR)
    {
        /* Error occured during parsing. */
        throw WhadMessageParsingError();
    }
    else
    {
        /* Save parameters. */
        m_addrType = (AddressType)address_info.type;
        m_address = address_info.address;
    }
}


/**
 * @brief   Retrieve the zigbee node address
 * 
 * @retval  Node address
 */

uint64_t SetNodeAddress::getAddress()
{
    return m_address;
}


/**
 * @brief   Retrieve the zigbee node address type
 * 
 * @retval  Node address type
 */

AddressType SetNodeAddress::getAddressType()
{
    return m_addrType;
}
