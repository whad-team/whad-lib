#include "dot15d4/base.hpp"

using namespace whad::dot15d4;


/********************************
 * Zigbee message base class
 *******************************/

/**
 * @brief   Dot15d4 message base class.
 **/

Dot15d4Msg::Dot15d4Msg() : NanoPbMsg()
{
}


/**
 * @brief       Dot15d4 message base class.
 * 
 * @param[in]   pMessage    NanoPbMsg object containing a ble domain message 
 **/

Dot15d4Msg::Dot15d4Msg(NanoPbMsg pMessage) : NanoPbMsg(pMessage.getRaw())
{
}


/**
 * @brief   Dot15d4 message base class destructor.
 **/

Dot15d4Msg::~Dot15d4Msg()
{
}


/**
 * @brief       Identify the underlying dot15d4 message.
 *
 * This method can be used when parsing incoming Dot15d4 domain message to identify
 * the type of message it contains and process it later.
 * 
 * @return      Dot15d4 message type.
 **/

MessageType Dot15d4Msg::getType(void)
{
    MessageType msgType = (MessageType)whad_dot15d4_get_message_type(
        this->getMessage()
    );

    /* Return message type. */
    return msgType;
}