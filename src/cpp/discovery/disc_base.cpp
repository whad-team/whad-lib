#include <discovery/discovery.hpp>

/********************************
 * Discovery message base class
 *******************************/

/**
 * @brief   Discovery message base class.
 **/

whad::discovery::DiscoveryMsg::DiscoveryMsg() : NanoPbMsg()
{
}


/**
 * @brief       Discovery message base class.
 * 
 * @param[in]   pMessage    NanoPbMsg object containing a discovery domain message 
 **/

whad::discovery::DiscoveryMsg::DiscoveryMsg(NanoPbMsg &pMessage) : NanoPbMsg(pMessage.getRaw())
{
}


/**
 * @brief   Discovery message base class destructor.
 **/

whad::discovery::DiscoveryMsg::~DiscoveryMsg()
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

whad::discovery::MessageType whad::discovery::DiscoveryMsg::getType(void)
{
    MessageType msgType = (whad::discovery::MessageType)whad_discovery_get_message_type(
        this->getMessage()
    );

    /* Return message type. */
    return msgType;
}

