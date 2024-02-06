#include <esb/base.hpp>

namespace whad::esb {


/********************************
 * ESB message base class
 *******************************/

/**
 * @brief   ESB message base class.
 **/

EsbMsg::EsbMsg() : NanoPbMsg()
{
}


/**
 * @brief       ESB message base class.
 * 
 * @param[in]   pMessage    NanoPbMsg object containing a discovery domain message 
 **/

EsbMsg::EsbMsg(NanoPbMsg &pMessage) : NanoPbMsg(pMessage.getRaw())
{
}


/**
 * @brief   ESB message base class destructor.
 **/

EsbMsg::~EsbMsg()
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

MessageType EsbMsg::getType(void)
{
    MessageType msgType = (MessageType)whad_esb_get_message_type(
        this->getRaw()
    );

    /* Return message type. */
    return msgType;
}

}