#include "generic/base.hpp"

/********************************
 * Generic message base class
 *******************************/

/**
 * @brief   Discovery message base class.
 **/

whad::generic::GenericMsg::GenericMsg() : NanoPbMsg()
{
}


/**
 * @brief       Discovery message base class.
 * 
 * @param[in]   pMessage    NanoPbMsg object containing a discovery domain message 
 **/

whad::generic::GenericMsg::GenericMsg(NanoPbMsg pMessage) : NanoPbMsg(pMessage.getRaw())
{
}


/**
 * @brief   Discovery message base class destructor.
 **/

whad::generic::GenericMsg::~GenericMsg()
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

whad::generic::MessageType whad::generic::GenericMsg::getType(void)
{
    whad::generic::MessageType msgType = (whad::generic::MessageType)whad_generic_get_message_type(
        this->getRaw()
    );

    /* Return message type. */
    return msgType;
}
