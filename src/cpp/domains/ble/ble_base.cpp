#include "ble/base.hpp"

using namespace whad::ble;


/********************************
 * BLE message base class
 *******************************/

/**
 * @brief   BLE message base class.
 **/

BleMsg::BleMsg() : NanoPbMsg()
{
}


/**
 * @brief       BLE message base class.
 * 
 * @param[in]   pMessage    NanoPbMsg object containing a ble domain message 
 **/

BleMsg::BleMsg(NanoPbMsg pMessage) : NanoPbMsg(pMessage.getRaw())
{
}


/**
 * @brief   BLE message base class destructor.
 **/

BleMsg::~BleMsg()
{
}


/**
 * @brief       Identify the underlying discovery message.
 *
 * This method can be used when parsing incoming BLE domain message to identify
 * the type of message it contains and process it later.
 * 
 * @return      BLE message type.
 **/

MessageType BleMsg::getType(void)
{
    MessageType msgType = (MessageType)whad_ble_get_message_type(
        this->getMessage()
    );

    /* Return message type. */
    return msgType;
}