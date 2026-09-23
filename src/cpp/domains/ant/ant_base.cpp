#include <ant/base.hpp>

namespace whad::ant {


/********************************
 * ANT message base class
 *******************************/

/**
 * @brief   ANT message base class.
 **/

AntMsg::AntMsg() : NanoPbMsg()
{
}


/**
 * @brief       ANT message base class.
 * 
 * @param[in]   pMessage    NanoPbMsg object containing a discovery domain message 
 **/

AntMsg::AntMsg(NanoPbMsg &pMessage) : NanoPbMsg(pMessage.getRaw())
{
}


/**
 * @brief   ANT message base class destructor.
 **/

AntMsg::~AntMsg()
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

MessageType AntMsg::getType(void)
{
    MessageType msgType = (MessageType)whad_ant_get_message_type(
        this->getRaw()
    );

    /* Return message type. */
    return msgType;
}

}