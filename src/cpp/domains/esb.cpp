#include "cpp/esb.hpp"

using namespace whad::esb;


/**
 * @brief   BD Address default constructor.
 **/

EsbAddress::EsbAddress(void)
{
    memset(this->m_address, 0, 5);
    this->m_size = 0;
}


/**
 * @brief   ESB Address constructor.
 * 
 * @param[in]   pAddress    ESB address byte buffer (5 bytes max)
 * @param[in]   size        Address size in bytes
 **/

EsbAddress::EsbAddress(uint8_t *pAddress, uint8_t size)
{
    if (size <= 5)
    {
        this->m_size = size;
        memcpy(this->m_address, pAddress, size);
    }
}


/**
 * @brief   Get address length.
 * 
 * @retval  int   Address length in bytes
 **/

uint8_t EsbAddress::getLength(void)
{
    return this->m_size;
}


/**
 * @brief   Get address buffer.
 * 
 * @return  Pointer to the BD address byte buffer (6 bytes)
 **/

uint8_t *EsbAddress::getAddressBuf(void)
{
    return this->m_address;
}


/**
 * @brief   Set ESB address.
 * 
 * @param[in]   pAddress    Pointer to a 6-byte BD address buffer
 **/

void EsbAddress::setAddress(uint8_t *pAddress, uint8_t size)
{
    if (pAddress == NULL)
    {
        memset(this->m_address, 0, 5);
        this->m_size = 0;
    }

    if (size <= 5)
    {
        /* Copy BD address. */
        memcpy(this->m_address, pAddress, size);
    }
}


/********************************
 * ESB message base class
 *******************************/

/**
 * @brief   ESB message base class.
 **/

whad::esb::EsbMsg::EsbMsg() : NanoPbMsg()
{
}


/**
 * @brief       ESB message base class.
 * 
 * @param[in]   pMessage    NanoPbMsg object containing a discovery domain message 
 **/

whad::esb::EsbMsg::EsbMsg(NanoPbMsg &pMessage) : NanoPbMsg(pMessage.getRaw())
{
}


/**
 * @brief   ESB message base class destructor.
 **/

whad::esb::EsbMsg::~EsbMsg()
{
}


/**
 * @brief       Identify the underlying discovery message.
 *
 * This method can be used when parsing incoming Discovery domain message to identify
 * the type of message it contains and process it later.
 * 
 * @return      Discovery message type.
 **/

MessageType whad::esb::EsbMsg::getType(void)
{
    MessageType msgType = (whad::esb::MessageType)whad_esb_get_message_type(
        this->getRaw()
    );

    /* Return message type. */
    return msgType;
}


/********************************
 * ESB messages classes
 *******************************/

SetNodeAddress::SetNodeAddress(EsbMsg &message) : EsbMsg(message)
{
}

SetNodeAddress::SetNodeAddress(EsbAddress &address) : EsbMsg()
{
    whad_esb_address_t addr;

    /* Prepare address. */
    addr.size = address.getLength();
    memcpy(addr.address, address.getAddressBuf(), addr.size);

    /* Craft message. */
    whad_esb_set_node_address(this->getRaw(), &addr);
}

EsbAddress& SetNodeAddress::getAddress(void)
{
    whad_esb_address_t addr;

    /* Parse message. */
    if (whad_esb_set_node_address_parse(this->getRaw(), &addr) == WHAD_SUCCESS)
    {
        this->m_address.setAddress(addr.address, addr.size);
    }
    else
        this->m_address.setAddress(NULL, 0);
    
    /* Success. */
    return this->m_address;
}