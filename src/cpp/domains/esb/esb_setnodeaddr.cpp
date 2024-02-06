#include <esb/setnodeaddr.hpp>

using namespace whad::esb;

SetNodeAddress::SetNodeAddress(EsbMsg &message) : EsbMsg(message)
{
    /* Unpack message. */
    this->unpack();
}

SetNodeAddress::SetNodeAddress(EsbAddress &address) : EsbMsg()
{
    /* Copy address. */
    m_address.setAddress(address.getAddressBuf(), address.getLength());
}

EsbAddress& SetNodeAddress::getAddress(void)
{
    return this->m_address;
}

/**
 * @brief   Takes the object properties and fill the corresponding WHAD message.
 **/

void SetNodeAddress::pack()
{
    whad_esb_address_t addr;

    /* Prepare address. */
    addr.size = m_address.getLength();
    memcpy(addr.address, m_address.getAddressBuf(), addr.size);

    /* Craft message. */
    whad_esb_set_node_address(this->getMessage(), &addr);
}

void SetNodeAddress::unpack()
{
    whad_esb_address_t addr;

    /* Parse message. */
    if (whad_esb_set_node_address_parse(this->getRaw(), &addr) == WHAD_SUCCESS)
    {
        this->m_address.setAddress(addr.address, addr.size);
    }
    else
    {
        /* Error. */
        throw WhadMessageParsingError();
    }
}
