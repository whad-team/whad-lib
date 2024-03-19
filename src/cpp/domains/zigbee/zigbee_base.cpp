#include "zigbee/base.hpp"

using namespace whad::zigbee;


/********************************
 * Zigbee message base class
 *******************************/

/**
 * @brief   ZigBee message base class.
 **/

ZigbeeMsg::ZigbeeMsg() : NanoPbMsg()
{
}


/**
 * @brief       ZigBee message base class.
 * 
 * @param[in]   pMessage    NanoPbMsg object containing a ble domain message 
 **/

ZigbeeMsg::ZigbeeMsg(NanoPbMsg pMessage) : NanoPbMsg(pMessage.getRaw())
{
}


/**
 * @brief   ZigBee message base class destructor.
 **/

ZigbeeMsg::~ZigbeeMsg()
{
}


/**
 * @brief       Identify the underlying zigbee message.
 *
 * This method can be used when parsing incoming ZigBee domain message to identify
 * the type of message it contains and process it later.
 * 
 * @return      ZigBee message type.
 **/

MessageType ZigbeeMsg::getType(void)
{
    MessageType msgType = (MessageType)whad_zigbee_get_message_type(
        this->getMessage()
    );

    /* Return message type. */
    return msgType;
}