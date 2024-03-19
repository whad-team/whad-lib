#include "unifying/base.hpp"

using namespace whad::unifying;


/********************************
 * Unifying message base class
 *******************************/

/**
 * @brief   Unifying message base class.
 **/

UnifyingMsg::UnifyingMsg() : NanoPbMsg()
{
}


/**
 * @brief       Unifying message base class.
 * 
 * @param[in]   pMessage    NanoPbMsg object containing a ble domain message 
 **/

UnifyingMsg::UnifyingMsg(NanoPbMsg pMessage) : NanoPbMsg(pMessage.getRaw())
{
}


/**
 * @brief   Unifying message base class destructor.
 **/

UnifyingMsg::~UnifyingMsg()
{
}


/**
 * @brief       Identify the underlying unifying message.
 *
 * This method can be used when parsing incoming Unifying domain message to identify
 * the type of message it contains and process it later.
 * 
 * @return      Unifying message type.
 **/

MessageType UnifyingMsg::getType(void)
{
    MessageType msgType = (MessageType)whad_unifying_get_message_type(
        this->getMessage()
    );

    /* Return message type. */
    return msgType;
}